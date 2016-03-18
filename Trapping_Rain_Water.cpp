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
		minHeight = min(height[left], height[right]);           //记录最小的高度
		if (height[left] == minHeight)                          //比较height[left+1]是否高于height[left],即height[left+1]是否高于minHeight
		{
			while (++left < right && height[left] < minHeight)  //说明left处可以存水(minHeight-height[left])个单位
				result += minHeight - height[left];
		}
		else
		{
			while (left < --right && height[right] < minHeight) //说明right处可以存水(minHeight - height[right])个单位
				result += minHeight - height[right];
		}
	}

	return result;
}

int  main()
{

	return 0;
}