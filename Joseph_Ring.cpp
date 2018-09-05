#include<iostream>
#include<stdio.h>
#include<Windows.h>
using namespace std;

typedef int ListType;
typedef struct ListNode
{
	ListType val;
	struct ListNode* next;
}ListNode;

ListNode* ListCreate(int num)
{
	if (num <= 0)
	{
		return NULL;
	}
	ListNode* cur = (ListNode*)malloc(sizeof(ListNode));
	cur->val = 1;
	cur->next = NULL;
	ListNode* head = cur;
	for (int i = 2; i <= num; i++)
	{
		ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));
		new_node->val = i;
		new_node->next = NULL;
		cur->next = new_node;
		cur = new_node;
	}
	cur->next = head;
	return head;
}

void ListPop(ListNode* head,int number,int length)
{
	if (number <= 0)
	{
		cout << "number invalid" << endl;
		return;
	}
	int sum = 1;
	ListNode* cur = head;
	while (sum<=length)
	{
		int i = 1;
		if (cur->next == cur)
		{
			printf("第%d个出列的节点为 ", sum);
			cout << cur->val << endl;
			return;
		}
		while (i < number)
		{
			cur = cur->next;
			i++;
		}
		ListNode* delete_node = cur->next;
		printf("第%d个出列的节点为 ", sum);
		cout << delete_node->val << endl;
		cur->next = delete_node->next;
		free(delete_node);
		sum++;
	}
	return;
}

int main()
{
	int n = 9;
	int m = 5;
	ListNode* new_list = ListCreate(n);
	ListPop(new_list, m,n);
	system("pause");
	return 0;
}