#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <list>
#include <stack>
#include <queue>
#include <climits>
#include "zg_tool.hpp"
using namespace std;

struct ListNode{
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(NULL) {
    }
};

//Definition for binary tree
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


bool vector_sort_cmp(vector<int>& left_vec, vector<int>& right_vec){
    if(left_vec.size() != 2 || right_vec.size() != 2) return true;
    if(left_vec.front() < right_vec.front()) return true;
    else if(left_vec.front() > right_vec.front()) return false;
    else return left_vec.back() > right_vec.back();
}

class Solution{

public:
    //不含重复字符的最长字串
    //思路：用map记录下字符到索引的映射，判断该字符是否已经出现了----其实不用管这个字符是否存在，直接用一个变量记录字串起始位置即可
    int lengthOfLongestSubstring(string s) {
        //cout << s << endl;
        if(s.empty()) return 0;
        unordered_map<char,int> mapIdx;
        int maxLen = 1;
        int lastIdx = 0;
        for (size_t i = 0; i < s.size(); i++){
            if(mapIdx.count(s[i])){//如果这个字符已经存在了，则更新最大值
                cout << "idx=" << i << ",char=" << s[i] << ",mapIdx=" << mapIdx[s[i]] << ".lastIdx=" << lastIdx << endl;
                if(mapIdx[s[i]] >= lastIdx){  //更新lastidx并清除数据
                    //需要清除lastIdx到mapIdx[s[i]]之前的元素
                    int idxlow = lastIdx;
                    int idxhight = mapIdx[s[i]];
                    lastIdx = mapIdx[s[i]] + 1;
                    for (size_t j = idxlow; j <= idxhight; j++){
                        cout << "erase j , j = " << j << ", s[j]=" << s[j] << endl;
                        if(mapIdx[s[j]] <= idxhight){
                            mapIdx.erase(s[j]);
                        }
                    }
                }
                //lastIdx = max(lastIdx, mapIdx[s[i]] + 1);
                maxLen = max((int)i - lastIdx, maxLen);
                cout << "update maxLen, i=" << i << ",char=" << s[i] << ",maxLen=" << maxLen << ",lastIdx=" << lastIdx << endl;
            }
            else{ //这个字符不存在
                maxLen = max( (int)i - lastIdx + 1, maxLen);
                cout << "not exist maxLen, i=" << i << ",char=" << s[i] << ",maxLen=" << maxLen << ",lastIdx=" << lastIdx << endl;
            }
            mapIdx[s[i]] = i;
        }
        return maxLen;
    }

    //不含重复字符的最长字串---优化版
    //思路：用map记录下字符到索引的映射，判断该字符是否已经出现了----其实不用管这个字符是否存在，直接用一个变量记录字串起始位置即可
    int lengthOfLongestSubstringV2(string s) {
        if(s.empty()) return 0;
        int maxLen = 0, start = 0;
        map<char,int> last;

        for (int i = 0; i < s.size(); i++){
            //如果有重复点，则直接计算最大值
            if(last.count(s[i]) && last[s[i]] >= start){
                maxLen = max(maxLen, i - start);
                start = last[s[i]] + 1;
                //cout << "i=" << i << ",start=" << start << ",maxLen=" << maxLen << endl;
            }
            last[s[i]] = i;
        }
        return max(maxLen, (int)s.size() - start);
    }

    //字符串的排列
    //给定两个字符串 s1 和 s2，写一个函数来判断 s2 是否包含 s1 的排列。换句话说，第一个字符串的排列之一是第二个字符串的子串。
    //思路：hash+滑动窗口
    bool checkInclusion(string s1, string s2) {
        if(s1.empty() || s2.empty() || s1.size() > s2.size()) return false;
        //先统计s2的字符数据
        unordered_map<char,int> s1data, s2data;
        for(int i = 0; i< s1.size(); ++i){
            ++s1data[s1[i]];
            ++s2data[s2[i]];
        }

        //先比较一次首部
        if(checkInclusionHelper(s1data, s2data)) return true;
        //然后去比较每一个窗口
        for(int i = 1; i<= s2.size() - s1.size(); ++i){
            --s2data[s2[i-1]];
            if(s2data[s2[i-1]] == 0) s2data.erase(s2[i-1]);
            ++s2data[s2[i+s1.size()-1]];
            if(checkInclusionHelper(s1data, s2data)) return true;
        }
        return false;
    }

    bool checkInclusionHelper(unordered_map<char,int>& mapleft, unordered_map<char,int>& mapright){
        if(mapleft.size() != mapright.size())
            return false;
        for(auto item : mapleft){
            if(mapright.count(item.first) == 0 || mapright[item.first] != item.second){
                return false;
            }
        }
        return true;
    }

    //翻转字符串里的单词
    string reverseWords(string s) {
        //先移除字符串中多余的空格
        cout << "begin, s=" << s << endl;
        auto it = s.begin();
        while(*it == ' '){
            it = s.erase(it);
        }
        cout << "after shoubu deal, s=[" << s << "]\n";
        for (size_t i = 1; i < s.size();)
        {
            if(s[i] == ' ' && s[i] == s[i-1]){
                s.erase(i,1);
            }else{
                ++i;
            }
        }
        cout << "after zhongjian deal, s=[" << s << "]\n";
        //处理末尾的空格
        if(s.empty()) return s;
        if(s.back() == ' ') s.pop_back();
        cout << "after weibu deal, s=[" << s << "]\n";

        //先整个逆序下
        reverseWordsHelper(s, 0, s.size()-1);
        cout << "after total revers, s=[" << s << "]\n";

        //部分逆序
        int left = 0;
        int right = 0;
        while(right < s.size()){
            if(s[right] == ' '){
                reverseWordsHelper(s, left, right - 1);
                left = right+1;
            }
            ++right;
        }
        if(left != right) reverseWordsHelper(s, left, right - 1);
        return s;
    }
    void reverseWordsHelper(string& s, int left, int right){
        while(left < right){
            char c = s[left];
            s[left] = s[right];
            s[right] = c;
            ++left;
            --right;
        }
    }

    //简化路径
    string simplifyPath(string path)
	{
		vector<string> dirs; // 当做栈
		for (auto i = path.begin(); i != path.end();)
		{
			++i;
			auto j = find(i, path.end(), '/');
			auto dir = string(i, j);
            cout << "dir=" << dir << endl;
			if (!dir.empty() && dir != ".")
			{
				// 当有连续 '///' 时， dir 为空
				if (dir == "..")
				{
					if (!dirs.empty())
						dirs.pop_back();  /*pop_back位删除最后一个元素*/
				}
				else
					dirs.push_back(dir);
			}
			i = j;
		}
		//stringstream 用来构造格式化字符串
		stringstream out;
		if (dirs.empty())
		{
			out << "/";
		}
		else
		{
			for (auto dir : dirs)
				out << '/' << dir;
		}
		return out.str();
	}

    //复原IP地址--dfs搜索，每个ip端最多可255
    vector<string> restoreIpAddresses(string s) {
        vector<string> result;
        string ip;
        restoreIpAddressesHelper(s, 0, 0, ip, result);
        return result;
    }
    void restoreIpAddressesHelper(string& s, int pos, int step, string ip, vector<string>& result){
        if(pos == s.size() && step == 4){
            ip.pop_back();
            result.push_back(ip);
        }

        //可以优化空间，剪枝;(1)剩下的位数不够 （2）剩下的位数太多
        if( (s.size() - pos) <  (4 - step) || (s.size() - pos) > (4-step)*3) return;        

        int num = 0;
        for(int i = pos; i < pos + 3 && i < s.size(); ++i){
            num = num*10 + (s[i] - '0');
            if(num <= 255){ //可以继续dfs
                ip.push_back(s[i]);
                restoreIpAddressesHelper(s, i + 1, step + 1, ip + '.', result);
            }
            //0只能单独存在
            if(num == 0){
                break;
            }
        }
    }

    //最大岛屿面积--dfs搜索，已访问，则grid重置为-1
    int maxAreaOfIsland(vector<vector<int>>& grid) {

        if(grid.empty()) return 0;
        int maxArea = 0;
        int row = grid.size();
        int col = grid.front().size();
        for (size_t i = 0; i < row; i++)
        {
            for (size_t j = 0; j < col; j++)
            {
                int curArea = 0;
                if(grid[i][j] == 1){
                    maxAreaOfIslandDfs(grid, i, j, curArea, maxArea);
                    maxArea = max(curArea, maxArea);
                }
            }
        }
        return maxArea;
    }
    void maxAreaOfIslandDfs(vector<vector<int>>& grid, int rowPos, int colPos, int& curArea, int& maxArea){
        if(grid[rowPos][colPos] != 1){
            return;
        }
        ++curArea;
        grid[rowPos][colPos] = -1;
        //cout << "row=" << rowPos << "\tcol=" << colPos << "\tcurArea=" << curArea << "\tmaxArea=" << maxArea << endl;

        //上
        if(rowPos > 0 && grid[rowPos - 1][colPos] == 1){
            maxAreaOfIslandDfs(grid, rowPos - 1, colPos, curArea, maxArea);
        }

        //下
        if(rowPos + 1 < grid.size() && grid[rowPos + 1][colPos] == 1){
            maxAreaOfIslandDfs(grid, rowPos + 1, colPos, curArea, maxArea);
        }

        //左
        if(colPos - 1 >= 0 && grid[rowPos][colPos - 1] == 1) {
            maxAreaOfIslandDfs(grid, rowPos, colPos - 1, curArea, maxArea);
        }

        //右
        if(colPos + 1 < grid.front().size() && grid[rowPos][colPos +1]){
            maxAreaOfIslandDfs(grid, rowPos, colPos + 1, curArea, maxArea);
        }
    }

    //最长连续子序列
    int findLengthOfLCIS(vector<int>& nums) {
        if(nums.empty()) return 0;
        int start = 0;
        int maxlen = 1;
        for (size_t i = 1; i < nums.size(); i++)
        {
            if(nums[i] <= nums[i-1]){
                maxlen = max(maxlen, (int)i - start);
                cout << i << "\t" << start << "\t" << maxlen << endl;
                start = i;
            }
        }
        maxlen = max(maxlen, (int)nums.size() - start);
        return maxlen;
    }

    //未排序数组的最长连续序列--dfs遍历
    int longestConsecutive(vector<int>& nums) {
        if(nums.empty()) return 0;
        map<int,int> mapflag;
        for(auto item : nums){
            ++mapflag[item];
        }
        
        int maxlen = 1;
        for(auto item : nums){
            if(mapflag[item] == 0 ){
                continue; //已访问过，跳过
            }
            //dfs访问-向下访问
            int low = item - 1;
            int len = 1;
            while(mapflag.count(low)){
                ++len;
                mapflag[low] = 0;
                --low;
            }
            //dfs向上访问
            int hight = item + 1;
            while(mapflag.count(hight)){
                ++len;
                mapflag[hight] = 0;
                ++hight;
            }
            maxlen = max(maxlen, len);
        }
        return maxlen;
    }

    //下一个排列--简单方法--还有个dfs生成法
    string getPermutation(int n, int k) {
        string nums;
        for(int i = 1; i <= n ;++i){
            nums.push_back(i + '0');
        }
        while(k-- > 1){
            next_permutation(nums.begin(), nums.end());
        }
        return nums;
    }


    //朋友圈--类似于孤岛问题，dfs
    int findCircleNum(vector<vector<int>>& M) {
        if(M.empty()) return 0;
        int circleNum = 0;
        int row = M.size();
        int col = M.front().size();

        for (size_t i = 0; i < row; i++)
        {
            for (size_t j = 0; j < col; j++)
            {
                if(M[i][j] == 1){
                    ++circleNum;
                    findCircleNumDfs(M, i, j);
                }
            }
        }
        return circleNum;
    }

    void findCircleNumDfs(vector<vector<int>>& grid, int rowPos, int colPos){
        if(grid[rowPos][colPos] != 1) return;
        grid[rowPos][colPos] = -1;
        grid[colPos][rowPos] = -1;
        //dfs遍历 row=colPos
        int col = grid.front().size();
        for(int i = 0; i < col; ++i){
            if(grid[colPos][i] == 1){
                findCircleNumDfs(grid, colPos, i);
            }
        }
    }

    //给出一个区间的集合，请合并所有重叠的区间
    static bool vectorSort(vector<int>& vecleft, vector<int>& vecright){
        return vecleft.front() < vecright.front();
    }
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> result;
        if(intervals.empty()) return result;
        //先排个序试下
        sort(intervals.begin(), intervals.end(), vectorSort);
        for(auto item : intervals){
            cout << ZgTool::tostr(item) << endl;
        }
        result.push_back(intervals.front());
        for (size_t i = 1; i < intervals.size(); i++)
        {
            //看result末尾元素是否能和i元素合并
            vector<int>& backitem = result.back();
            if(backitem.front() <= intervals[i].front() && backitem.back() >= intervals[i].front() && backitem.back() <= intervals[i].back()){ //可以合并
                backitem.back() = intervals[i].back();
            }else if(backitem.front() <= intervals[i].front() && backitem.back() < intervals[i].front()){ //只能继续添加了
                result.push_back(intervals[i]);
            }else{
                //还有种情况，就是区间1包含区间2，不添加到result中去
            }
        }
        
        //合并后的结果
        cout << "after merge" << endl;
        for(auto item : result){
            cout << ZgTool::tostr(item) << endl;
        }
        return result;
    }

    //左右分别扫描两次
    int trap(vector<int>& height) {
           vector<int> left(height.size(),0);
           vector<int> right(height.size(),0);
           for(int i = 1; i < height.size(); ++i){
               left[i] = max(left[i-1],height[i-1]);
           }
           for(int i = height.size() - 2; i >= 0; --i){
               right[i] = max(right[i+1], height[i+1]);
           }
           
           //计算面积
           int sum = 0;
           for (size_t i = 0; i < height.size(); i++)
           {
               if(left[i] > height[i] && right[i] > height[i])
               {
                   sum += (min(right[i], left[i]) - height[i]);
               }
           }
           return sum;  
    }

    //层序锯齿状遍历
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        bool fromleft = true;
        vector<vector<int>> ret;
        if( root == nullptr) return ret;
        stack<TreeNode*> stackNode;
        stack<TreeNode*> lineTmp;
        stackNode.push(root);
        vector<int> vecLine;
        while(!stackNode.empty()){
            TreeNode* topNode = stackNode.top();
            vecLine.push_back(topNode->val);
            if(fromleft){
                if(topNode->left != nullptr)
                    lineTmp.push(topNode->left);
                if(topNode->right != nullptr)
                    lineTmp.push(topNode->right);
            }else{
                if(topNode->right != nullptr)
                    lineTmp.push(topNode->right);
                if(topNode->left != nullptr)
                    lineTmp.push(topNode->left);
            }
            stackNode.pop();
            if(stackNode.empty()){
                ret.push_back(vecLine);
                lineTmp.swap(stackNode);
                fromleft = !fromleft;
                cout << "fromleft=" << fromleft << ",vecline=" << ZgTool::tostr(vecLine) << endl;
                vecLine.clear();
            }
        }
        return ret;
    }

    //最大正方形面积
    int maximalSquare(vector<vector<int>>& matrix) {
        if(matrix.empty()) return 0;
        int row = matrix.size();
        int col = matrix.front().size();
        int max_val = 0; //最大矩形直径
        vector<int> height(col, 0);
        for(int i = 0; i < row; ++i){
            for(int j =0; j< col;++j){
                if(matrix[i][j] == 1){
                    height[j] += 1;
                }else{
                    height[j] = 0;
                }
            }

            //求最大矩形
            vector<int> vectmp = height;
            vectmp.push_back(0);
            stack<int> stacktmp;
            for(int j =0; j < vectmp.size();){
                if(stacktmp.empty() || vectmp[j] >= vectmp[stacktmp.top()]){
                    stacktmp.push(j++);
                }else{
                    int top = vectmp[stacktmp.top()];
                    stacktmp.pop();
                    int len = stacktmp.empty() ? j :  j- stacktmp.top() - 1; //长度
                    max_val = max(max_val, min(top, len));  //取端的边，则为正方形
                }
            }
        }
        return max_val*max_val; //返回的是矩形面积
    }

    //最大正方形面积---动态规划方法
    int maximalSquareV2(vector<vector<int>>& matrix) {
        if (matrix.size() == 0 || matrix[0].size() == 0) {
            return 0;
        }
        int maxSide = 0;
        int rows = matrix.size(), columns = matrix[0].size();
        vector<vector<int>> dp(rows, vector<int>(columns));
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                if (matrix[i][j] == 1) {
                    if (i == 0 || j == 0) {
                        dp[i][j] = 1;
                    } else {
                        dp[i][j] = min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
                    }
                    maxSide = max(maxSide, dp[i][j]);
                }
            }
        }
        int maxSquare = maxSide * maxSide;
        return maxSquare;
    }

    //柱状图中的最大矩形--常规解法，先求每个点的左右边界，复杂度O(N*N）
    int largestRectangleArea(vector<int>& heights) {
        vector<int> left(heights.size(), 0 );  //左边界，该节点左边的点都小于height[i]
        vector<int> right(heights.size(), 0 ); //右边界，该节点右边的点都大于height[i]
        for(int i = 0; i< heights.size(); ++i){
            left[i] = i;
            int j  = i-1;
            while(heights[j] >= heights[i] && j >= 0){
                left[i] = left[j];
                j  = left[j] - 1;
            }
        }
        for(int i = heights.size() - 1; i >= 0; --i){
            right[i] = i;
            int j = i + 1;
            while(heights[j] >= heights[i] && j < heights.size()){
                right[i] = right[j];
                j = right[j] + 1;
            }
        }

        //计算面积咯
        int sum = 0;
        for(int i = 0; i < heights.size(); ++i){
            sum = max ( sum, (right[i] - left[i] + 1)*heights[i]);
        }
        return sum;
    }

    //柱状图中的最大矩形--递增栈，复杂度O(N)
    //参考：https://leetcode-cn.com/problems/largest-rectangle-in-hEistogram/solution/84-by-ikaruga/
    //如果当前元素大于栈顶元素，则持续压入，否则弹出栈顶元素，计算以栈顶元素为高的左右矩形面积，左边界为当前栈顶元素，右边界为当前元素
    int largestRectangleAreaV2(vector<int>& heights) {
        if(heights.empty()) return 0;
        heights.push_back(0);
        stack<int> stackdata;
        int area = 0;
        for (int i = 0; i < heights.size();)
        {
            if(stackdata.empty() || heights[i] >= heights[stackdata.top()]){ //保持栈内的数据递增
                stackdata.push(i++);
            }else{
                int top = heights[stackdata.top()];
                stackdata.pop();
                area = max( area, stackdata.empty() ? top * i : (i - stackdata.top() - 1) * top);
            }
        }
        return area;
    }

    //三角形最小路径和
    //TODO 可以优化，path改为一维数组，第二个for循环从大到小，循环利用数组
    int minimumTotal(vector<vector<int>>& triangle) {
        vector<vector<int>> path;
        if(triangle.empty()) return 0;
        path.push_back(triangle.front());
        for (int i = 1; i < triangle.size(); i++){
            auto row = triangle[i];
            if(row.empty()) return 0;
            vector<int> path_row(row.size(),0);
            path.push_back(path_row);
            path[i][0] = path[i-1][0] + row[0]; //每行第一个节点的都只有一条路径
            for(int j = 1; j < row.size() - 1; ++j){
                path[i][j] = min(path[i-1][j-1], path[i-1][j]) + row[j];
            }
            path[i][row.size()-1] = path[i-1][row.size()-2] + row[row.size()-1];
        }
        //找到最后一个行的数据
        return *min_element(path.back().begin(), path.back().end());
    }

    //俄罗斯套娃信封问题
    //贪心的思路，先排序，尽量取小的-这个贪心算法是错误的
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        sort(envelopes.begin(), envelopes.end(), vector_sort_cmp);
        //贪心
        int cnt = 0;
        int first = 0, last = 0;
        for(auto item : envelopes){
            if(item.front() > first && item.back() > last){
                ++cnt;
                first = item.front();
                last = item.back();
            }
        }
        return cnt;
    }

    //将套娃问题转换为LIS问题
    //思路：构造数组，长度优先；相同长度，按照宽度从大到小排序
    //问题升级：三维套娃
    int maxEmaxEnvelopesV2(vector<vector<int>>& envelopes) {
        sort(envelopes.begin(), envelopes.end(), vector_sort_cmp);
        vector<int> datas;
        for(auto item : envelopes){
            datas.push_back(item.back());
        }
        return lengthOfLIS(datas);
    }

    //最小递增子序列，复杂度N*LogN
    //贪心算法，新建一个len+1数组d[i]表示长度i结尾的最小元素
    //二维数组DP算法，复杂度O(N*N)
    int lengthOfLIS(vector<int>& nums) {
        if(nums.empty()) return 0;
        vector<int> d(nums.size() + 1);
        int max_len = 1;
        d[max_len] = nums.front();
        for(int i = 1; i < nums.size(); ++i){
            if(nums[i] > d[max_len])
                d[++max_len] = nums[i];
            else{ //找到第一个比nums[i]大的元素，然后替换
                int pos = 1, left = 1, right = max_len;
                while(left <= right){
                    int mid = left + (right - left)/2;
                    if(d[mid] >= nums[i]){
                        pos = mid;
                        right = mid - 1;
                    }else{
                        left = mid + 1;
                    }
                }
                d[pos] = nums[i];
            }
        }
        //cout << ZgTool::tostr(d) << endl;
        return max_len;
    }
};



int main(){

    TreeNode node1(3);
    TreeNode node2(9);
    TreeNode node3(20);
    TreeNode node4(15);
    TreeNode node5(7);
    node1.left = &node2;
    node1.right = &node3;
    node3.left = &node4;
    node3.right = &node5;
    Solution sol;
    vector<vector<int>> data = {{5,6},
                                {4,6},
                                {6,7},
                                {2,3}};
    vector<int> nums = {0,8,4,12,2};
    auto ret = sol.maxEmaxEnvelopesV2(data);
    cout << ret << endl;
    return 0;
}