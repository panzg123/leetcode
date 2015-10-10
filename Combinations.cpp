class Solution {
public:
	/*
	Combinations 
	�ݹ飬ʱ�临�Ӷ� O(n!)���ռ临�Ӷ� O(n)
	*/
	vector<vector<int>> combine(int n, int k)
	{
		vector<vector<int>> result;
		if (n < k) return result;
		vector<int> path;
		combine_help(result, n, 1, 0, path,k);
		return result;
	}
	/*
	result:�洢���
	n:��С
	k����ʼλ��
	length:��ѡ������ݸ���
	path:ѡ��ļ�¼
	target��Ŀ��ѡ�����
	*/
	void combine_help(vector<vector<int>> &result,int n,int k,int length,vector<int> &path,int target)
	{
		if (k<=n+1 && length == target)
		{
			result.push_back(path);
			return;
		}
		if (k>n) return;
		//ѡ
		path.push_back(k);
		combine_help(result, n, k + 1, length + 1, path, target);
		path.pop_back();
		//��ѡ
		combine_help(result, n, k + 1, length, path, target);
	}
};