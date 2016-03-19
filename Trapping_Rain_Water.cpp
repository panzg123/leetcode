#include <iostream>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <vector>
#include <set>
#include <string>
#include <stack>

using namespace std;

int trap(vector<int>& height) {
	int left = 0, right = height.size() - 1;
	int minHeight = 0, result = 0;

	while (left < right)
	{
		minHeight = min(height[left], height[right]);           //��¼��С�ĸ߶�
		if (height[left] == minHeight)                          //�Ƚ�height[left+1]�Ƿ����height[left],��height[left+1]�Ƿ����minHeight
		{
			while (++left < right && height[left] < minHeight)  //˵��left�����Դ�ˮ(minHeight-height[left])����λ
				result += minHeight - height[left];
		}
		else
		{
			while (left < --right && height[right] < minHeight) //˵��right�����Դ�ˮ(minHeight - height[right])����λ
				result += minHeight - height[right];
		}
	}

	return result;
}

int  main()
{

	return 0;
}