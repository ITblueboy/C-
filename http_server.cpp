#include<stdio.h>
#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/stat.h>
#include<sys/sendfile.h>
#include<signal.h>
#include<execinfo.h>
#include<pthread.h>

using namespace std;
typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;
#define SIZE (10*1024)

struct HttpRequest
{
  char first_line[SIZE];
  char* method;
  char* url;
  char* url_path;
  char* query_string;
  int content_length;
};
int ReadLine(int sock, char buf[], size_t max_size)
{
  //按行从 socket 读取数据
  //换行符可能有：\n ,\r, \r\n;
  //1， 循环从 socket中读取字符，一次读一个，
  char ch = '\0';
  size_t index = 0;
  while(index < (max_size-1))
  {
    ssize_t read_size = recv(sock, &ch, 1, 0);
    if(read_size <= 0)
    {
      cout<<"读取数据失败,可能收到非法报文"<<endl;
      return 1;
    }

  //2， 判定字符，如果是\r,
  if(ch == '\r')
  {
  //  (a):尝试从缓冲区读取下一个字符，如若下一个是 \n ,情况当做\n(换行符)处理;
  recv(sock, &ch, 1, MSG_PEEK);//（参数MSG_PEEK,表示读的同时不删缓冲区）
  if(ch == '\n')// 是 \r\n的情况
    recv(sock, &ch, 1, 0);//把下一个字符\n从缓冲区中读走
  //  (b):如果下一个字符是其他字符，就把 \r 修改成 \n；
  else 
    ch = '\n';
  }
  //3， 如果是当前字符是 \n ,退出循环，函数结束
  if(ch == '\n')
    break;
  //4, 当前字符是其他字符，放到buf中
  buf[index++] = ch;
  }
  buf[index] = 0;
  return 0;
}

ssize_t Split(char first_line[], const char* split_char, char* output[])
{
  int index = 0;
  char* tmp = NULL;
  char* p = strtok_r(first_line, split_char,&tmp);
  while(p)
  {
    output[index++] = p;
    p = strtok_r(NULL," ", &tmp);//循环调用的时候第一个参数为NULL，(根据上次切分的结果继续切分)
  }
  return index;
}
// GET / HTTP/1.1
int ParseFirstLine(char first_line[], char** methd_ptr, char** url_ptr)
{
  char* tokens[100] = {NULL};
  ssize_t n = Split(first_line, " ", tokens);//按照空格切分字符串,将分隔符替换成了 \0；
  if(n != 3)
  {
    cout<<"首行格式不对"<<n<<endl;
    return 1;
  }
  // TODO 验证tokens[2] 是否包含 HTTP 这样的关键字
  *methd_ptr = tokens[0];
  *url_ptr = tokens[1];
  return 0;
}

int ParseQueryString(char url[], char** url_path_ptr, char** query_string_ptr)
{
  char* p = url;
  *url_path_ptr = url;
  for(;*p!='\0'; ++p)
  {
    if(*p == '?')//找到‘？'说明url中有query_string
    {
      *p = '\0';
      *query_string_ptr = p+1;//指向query_string
      return 0;
    }
  }
 //走到此处，说明没有找到'?';没有query_string
 *query_string_ptr = NULL;
 return 0;
}

int HandlerHeader(int new_sock, int* content_length_ptr)
{
  char buf[SIZE] = {0};
  while(1)
  {
    if(ReadLine(new_sock, buf, sizeof(buf)))
    {
      cout<<"读取一行失败"<< endl; 
      return 1;
    }
    if(strcmp(buf,"\0") == 0)
    {
      return 0;
    }
    // Content_Length: 10
    const char* str = "Content-Length: ";
    if(strncmp(buf, str, strlen(str)) == 0)
    {
      *content_length_ptr = atoi(buf+strlen(str));
      //return 0;
      //此处不应该renturn;原因：1，找到了 content_length 的值
      //2，把接收缓冲区中收到的的数据都读出去，也就是从缓冲区中删除，避免粘包问题
    }
  }
}

//--------------------------------------------404页面------------------------
int Handler404(int new_sock)//构造错误处理页面（遵守HTTP响应格式）
{
  //首行部分
  const char* first_line = "HTTP/1.1 404 Not Found\n";
  send(new_sock, first_line, strlen(first_line),0);
  //空行
  const char* blank_line = "\n";
  //body部分
  const char* body = "<head><meta http-equiv=\"Content-Type\" content=\"text/html;charset=utf-8\"></head>"
                     "<h1>页面被喵星人吃掉了!!!</h1>";
  char content_length[SIZE] = {0};
  sprintf(content_length, "Content-Length: %lu\n", strlen(body));

  send(new_sock, first_line, strlen(first_line), 0);
  send(new_sock, content_length, strlen(content_length), 0);
  send(new_sock, blank_line, strlen(blank_line), 0);
  send(new_sock, body, strlen(body), 0);
  return 0;
}
//----------------------------------------------------------------------------------
//-------------------------------------------处理静态页面----------------------------
//----------------------------------------------------------------------------------
int IsDir(const char* filename)//判断路径是否是目录
{
  struct stat st;
  int ret = stat(filename, &st);
  if(ret < 0)//不是目录
  {
    return 0;
  }
  if(S_ISDIR(st.st_mode))
  {
    return 1;
  }
  return 0;
}
//通常url:http://www.baidu.com/index.html
//服务器看到的路径，很多情况下是 /index.html
//此处，我们处理第二种情况
void HandeFiletPath(const char* url_path, char file_path[])
{
  // ./wwwroot 定义http服务器的根目录
  sprintf(file_path, "./wwwroot%s",url_path);
  //如果url_path中没有路径,默认是根目录
  //url后面写了路径，但是路径是根目录; 如果url_path中对应的路径是一个目录，
  //就尝试访问该目录下的index.html文件（index.html作为一个默认的入口文件）
  
  //如果 url_path 最后一个字符是 /，说明访问的是一个目录
  if(url_path[strlen(url_path)-1] == '/')
  {
    strcat(file_path, "index.html");
  }
  //如果url_path最后一个字符不是 / ,但是访问的仍然是一个目录
  //此时核心问题就是如何识别出当前的路径是一个目录
  if(IsDir(file_path))
  {
    strcat(file_path, "/index.html");
  }
  return;
}

ssize_t GetFileSize(const char* file_path)//计算文件大小函数
{
  struct stat st;
  int ret = stat(file_path, &st);
  if(ret < 0)
    return 0;
  return st.st_size;
}
int WriteStaticFile(int new_sock, const char* file_path)
{
  //1，打开文件;失败：返回404；
  
  int fd = open(file_path, O_RDONLY);
  if(fd < 0)
  {
    perror("open");
    return 404;
  }
  //2，构造HTTP响应报文
  const char* first_line = "HTTP/1.1 200 OK\n";
  const char* blank_line = "\n";
  //header可以省，但最好自己写上
  //浏览器会帮助我们自动识别Conten-Type
  //没有写Content-Length是因为后面立刻关闭了socket,浏览器就能识别应该读到哪里就结束
  send(new_sock, first_line, strlen(first_line), 0);
  send(new_sock, blank_line, strlen(blank_line), 0);
  //3，读文件并且写到 socket 中
  //char ch = '\0';
  //while(read(new_sock, &ch, 1) > 0)
  //  send(new_sock, &ch, 1, 0);
  ssize_t file_size = GetFileSize(file_path);//计算文件大小
  sendfile(new_sock, fd, NULL, file_size);
  //4，关闭文件
  close(fd);
  return 200;
}
int Handler_StaticFile(int new_sock, const HttpRequest* req)
{
  //根据解析出来的url_path, 获取到对应的真实文件路径
  //例如：在url中的path是 /image/101.jpg
  //转换后在磁盘上的路径就是： ./wwwrooot/image/101.jpg
  char file_path[SIZE] = {0};
  HandeFiletPath(req->url_path, file_path);
  //打开文件，把文件中内容读取出来,并写入 socket 
  int err_code = WriteStaticFile(new_sock, file_path);//生成一个静态文件
  return err_code;
}
//----------------------------------------------------------------------------------
//----------------------------------------------处理动态页面-------------------------
//-----------------------------------------------------------------------------------
int HandlerCGI_father(int new_sock, int father_read, int father_write, const HttpRequest* req)
{
  // 3，父进程的工作：（a）:如果是post请求,把body 部分的数据读出来写进管道，剩下的动态生成页面的过程都交给子进程
 if(strcasecmp(req->method, "POST") == 0) 
 {
   //根据body的长度决定度多少字节
   int i = 0;
   char ch = '\0';
   for(; i < req->content_length; ++i)
   {
     read(father_write, &ch, 1);
     write(father_write, &ch, 1);
   }
  
 }
  //                  （b）:构造HTTP响应首行，header,空行
  const char* first_line = "HTTP/1.1 200 ok\n";
  //此处u为了简单，暂时i不管 header。
  const char* blank_line = "\n";
  send(new_sock, first_line, strlen(first_line), 0);
  send(new_sock, blank_line, strlen(blank_line), 0);
  //                  （c）:从管道中读取数据(子进程动态生成的页面)，把数据写道socket中
  char ch = '\0';//不用sendfile 是因为数据长度不容易确定
  while(read(father_read, &ch, 1) > 0)
    write(new_sock, &ch, 1);
  //                  （d）:进程等待，回收子进程；
  //如果使用进程等待，最好用waitpid()，保证当前线陈回收的是自己的子进程，
  //便捷的方法：忽略子进程(在main函数中加代码： signal(SIGCHLD, SIG_IGN))
  
  return 200;
}

int HandlerCGI_child(int child_read, int child_write, const HttpRequest* req)
{
  // 4，子进程的工作：
  // （a）:设置环境变量（REQUEST_METHOD, QUERY_STRING, CONTENT_LENGTH）;
  // 【说明】：如果把上面几个信息通过管道告诉替换之后的程序，也是可行的；但是此处要遵守 CGI标准，所以必须使用环境变量传递以上信息
  // 【注意！】：设置环境变量的步骤不能由父进程进行，虽然子进程可以继承父进程的环境变量，但是同一时刻存在多个请求时，
  //             每个请求都在尝试修改父进程的环境变量，产生类似线程安全的问题，导致子进程不能正确获取这些信息
  char method_env[SIZE] = {0};
  sprintf(method_env, "REQUEST_METHOD=%s",req->method);
  putenv(method_env);
  if(strcasecmp(req->method, "GET") == 0)
  {
    //设置QUERY_STRING
    char query_string_env[SIZE] = {0};
    sprintf(query_string_env, "QUERY_STRING=%s", req->query_string);
    putenv(query_string_env);
  }
  else //是post方法
  {
    //设置CONTENT_LENGTH
    char content_length_env[SIZE] = {0};
    sprintf(content_length_env, "CONTENT_LENGTH=%d", req->content_length);
    putenv(content_length_env);
  }
  // （b）:把标准输入和标准输出重定向到管道上，此时的 CGI 程序读写标准输入输出相当于读写管道
  dup2(child_read, 0);
  dup2(child_write, 1);
  // （c）:子进程进行程序替换（需要找到是哪个 CGI 可执行程序，然后再使用exec函数进行替换)
  // 假设url_path是：/cgi-bin/test   ;说明对应的CGI程序路径就是 ./wwwroot/cgi-bin/test 
  char file_path[SIZE] = {0};
  HandeFiletPath(req->url_path, file_path);
  execl(file_path, file_path, NULL);//第一个参数表示可执行程序的路径；第二个参数argv[0];第三个参数：命令行参数结束
  //（d）:替换失败的错误处理(替换失败，子进程就没有存在必要了子进程就退出)
  exit(0);
  
}
int Handler_CGI(int new_sock, const HttpRequest* req)//------动态页面----
{
  int err_code = 200;
  // 1，创建一对匿名管道
  int fd1[2],fd2[2];
  pipe(fd1);pipe(fd2);
  int father_read = fd1[0];
  int child_write = fd1[1];
  int father_write = fd2[1];
  int child_read = fd2[0];
  // 2，创建子进程
  pid_t ret = fork();
  if(ret > 0)//father
  {
    close(child_read);//不用的文件描述符暂时先关闭;（也是为了保证父进程从管道读数据的时候，read能够不阻塞）
    close(child_write);
    HandlerCGI_father(new_sock, father_read, father_write, req);
  }
  else if(ret == 0)//child
  {
    close(father_read);
    close(father_write);
    HandlerCGI_child(child_read, child_write, req);
  }
  else 
  {
    perror("fork");
    err_code = 404;
    goto END;
  }
END:
  close(father_read);
  close(father_write);
  close(child_read);
  close(child_write);
  return err_code;
}


void HandlerRequest(int new_sock)//真正完成请求处理过程函数
{
  //1.读取请求并解析
 //（a）,从Http请求中读出首行
 int err_code = 200;
  HttpRequest req;
  memset(&req, 0, sizeof(req));//对req初始化
 if(ReadLine(new_sock, req.first_line, sizeof(req.first_line)-1))
 {
   cout<<"ReadLine first_line failed"<<endl;
   err_code = 404;
  goto END;
 }
  printf("first_line = %s\n",req.first_line);
  //（b）,解析首行，获取方法，URL，版本号（不用）
 if(ParseFirstLine(req.first_line, &req.method, &req.url))
  {
    cout<<"解析首行失败"<<endl;
    err_code = 404;
    goto END;
  }
  //（c）对URL进行解析，找到其中的url_path,query_string
  if(ParseQueryString(req.url,&req.url_path, &req.query_string))
  {
    cout<<"解析URL失败"<<endl;
    err_code = 404;
    goto END;
  }
  //（d），读取并解析header部分，（此处为了简单，只保留content_length,其他header内容直接丢弃）
  if(HandlerHeader(new_sock, &req.content_length))
  {
    cout<<"解析Header失败"<<endl;
    err_code = 404;
    goto END;
  }

  //2.根绝请求的详细情况执行静态页面逻辑还是动态逻辑
  //（a）,是get请求：并且没有query_string----------静态页面
  //（b）,是get请求：有query_String------动态页面,根据query_string参数来动态计算生成页面
  //（c）,是post请求，都是动态页面
  if(strcmp(req.method, "GET") == 0 && req.query_string == NULL)
  {
   err_code = Handler_StaticFile(new_sock, &req);//生成静态页面

  }
  else if(strcmp(req.method, "GET") == 0 && req.query_string != NULL)
  {
    //cgi
   err_code =  Handler_CGI(new_sock,&req);
  }
  else if(strcmp(req.method, "POST") == 0)
  {
   err_code =  Handler_CGI(new_sock, &req);
  }
  else 
  {
    cout<<"方法不支持"<<endl;
    err_code = 404;
    goto END;
  }
END:
  if(err_code != 200)
  {
    Handler404(new_sock);
  }
  //此处考虑短连接，每次客户端给服务器发送请求之前，都新建一个socket进行连接
  //对于短连接来说，如果响应完了，就可以关闭new_sock;
  //此处由于服务器主动断开连接，就会进入TIME_WAIT状态，由于服务器短时间内处理了大量的连接，导致服务器上出现大量的TIME_WAIT;
  //需要设置setsockopt REUSEADDR重用TIME_WAIT状态的连接
  
  close(new_sock);
}
void* ThreadEntry(void* arg)//线程处理函数
{
  int new_sock = (int64_t)arg;
  HandlerRequest(new_sock);
  return NULL;
}

void HttpServerStart(const char* ip, short port)
{
  //1.创建tcp sockert
  int listen_sock = socket(AF_INET, SOCK_STREAM, 0);
  if(listen_sock < 0)
  {
    perror("socket");
    return ;
  }
  //设置 REUSEADDR，处理后面短连接主动关闭 socket 的问题
  int opt = 1;
  setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));//端口复用
  //2,绑定端口号
  sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr =inet_addr(ip);
  addr.sin_port = htons(port);
  if(bind(listen_sock, (sockaddr*)&addr, sizeof(addr)) < 0)
  {
    perror("bind");
    return;
  }
  //3监听
  int ret = listen(listen_sock, 5);
  if(ret < 0)
  {
    perror("listen");
    return;
  }
  
  cout<<"start httpservre OK!"<<endl;

  //4.循环处理客户端连接
  while(1)
  {
    sockaddr_in client;
    socklen_t len = sizeof(client);
    
    int64_t new_sock = accept(listen_sock, (sockaddr*)&client, &len);
    if(new_sock < 0)
    {
      perror("accept");
      continue;
    }
    cout<<"获得新连接："<<"ip="<<inet_ntoa(client.sin_addr)<<"port="<<client.sin_port<<endl;
    // 采用多线程方式处理多个连接的并行处理
    pthread_t tid;
    pthread_create(&tid, NULL, ThreadEntry,(void*)new_sock);
    pthread_detach(tid);
  }
    
 }

int main(int argc, char* argv[])
{
  if(argc != 3)
  {
    cout<<"Usage: ./http_server [ip] [portr]"<<endl;
    return 1;
  }
  signal(SIGCHLD, SIG_IGN);
  HttpServerStart(argv[1],atoi(argv[2]));
  return 0;
}
