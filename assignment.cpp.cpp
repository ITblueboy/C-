class Solution {
public:
	bool Find(int target, vector<vector<int> > array) {
		int row = (int)array[0].size();
		int col = (int)array.size();
		if (col != 0 && row != 0)
		{
			if (target<array[0][0] || target>array[col - 1][row - 1])
			{
				return false;
			}
			int i = 0;
			int j = row - 1;
			while (i<col&&j >= 0)
			{
				if (array[i][j] == target)
				{
					return true;
				}
				else if (array[i][j]>target)
				{
					j--;
				}
				else
				{
					i++;
				}
			}
		}
		return false;
	}
};