//
// Created by panzg123 on 2020/11/29.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <stack>
#include <queue>
#include <climits>
#include "zg_tool.hpp"
using namespace std;

struct ListNode{
    int val;
    struct ListNode *next;
    explicit ListNode(int x) : val(x), next(NULL) {
    }
};

//Definition for binary tree
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    explicit TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution{
public:
    #define MAX 100000
    /* father[x]表示x的父节点 */
    int father[MAX];
    /* rank[x]表示x的秩 */
    int rank[MAX];

    // 初始化
    void Make_Set(int n)
    {
        for (int i = 1; i < n; ++i)
        {
            father[i] = i;
            rank[i] = 0;
        }
    }

    // 查找
    int Find_Set(int x)
    {
        if (x != father[x])
            return Find_Set(father[x]);
        return x;
    }

    /* 按秩合并x,y所在的集合 */
    void Union(int x, int y)
    {
        x = Find_Set(x);
        y = Find_Set(y);
        if (x == y) return;
        if (rank[x] > rank[y])
        {
            father[y] = x;
        }
        else
        {
            if (rank[x] == rank[y])
            {
                rank[y]++;
            }
            father[x] = y;
        }
    }

    //f(i) 表示从i到n-1，即从i字符到末尾得最小分割数
    //data[i][j] 表示i到j是否为回文
    int minCut(string s){
        vector<int> f;
        for (int i = 0; i < s.size(); ++i) {
            f.push_back(s.size()-i-1);
        }
        f.push_back(-1); //f(n)=-1
        vector<vector<bool>> data(s.size()+1, vector<bool>(s.size()+1, false));
        for (int i = s.size()-1; i >= 0; --i) {
            for (int j = i; j < s.size(); ++j) {
                if ( s[i] == s[j] && (j - i < 2 || data[i+1][j-1])){
                    data[i][j] = true;
                    f[i] = min(f[i], f[j+1] + 1);
                }
            }
        }
        return f[0];
    }

    // 647. 回文子串
    int countSubstrings(string s) {
        vector<vector<bool>> data(s.size()+1, vector<bool>(s.size()+1, false));
        for (int i = s.size()-1; i >= 0; --i) {
            for (int j = i; j < s.size(); ++j) {
                if ( s[i] == s[j] && (j - i < 2 || data[i+1][j-1])){
                    data[i][j] = true;
                }
            }
        }
        //计数
        int cnt = 0;
        for (auto row : data) {
            for (auto item : row) {
                if (item){
                    ++cnt;
                }
            }
        }
        return cnt;
    }
    // 1328. 破坏回文串
    string breakPalindrome(string palindrome) {
        if(palindrome.empty() || palindrome.size() == 1){
            return "";
        }
        bool bReplace = false;
        for (int i = 0; i < palindrome.size(); ++i) {
            if ( palindrome[i] != 'a' && !(palindrome.size()%2 == 1 && i == palindrome.size()/2)){
                palindrome[i] = 'a';
                bReplace = true;
                break;
            }
        }
        if (!bReplace){
            palindrome[palindrome.size()-1] = 'b';
        }
        return palindrome;
    }
    //1177. 构建回文串检测
    vector<bool> canMakePaliQueries(string s, vector<vector<int>>& queries) {
        
    }

    //1202 交换字符串中的元素
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        int len = s.size();
        if(len <= 0)
            return "";
        Make_Set(len);
        for (auto item1 : pairs) {
            if(item1.size() == 2) {
                Union(item1[0], item1[1]);
            }
        }
        //同一个集合中的元素排序
        map<int, set<int>> charSet;
        for (int i = 0; i < len; ++i) {
            auto idx = Find_Set(i);
            charSet[idx].insert(i);
        }

        //排序下
        vector<char> vecTmp;
        for(auto item : charSet) {
            for (auto item2 : item.second) {
                vecTmp.push_back(s[item2]);
            }
            //排序下
            sort(vecTmp.begin(), vecTmp.end());
            int idx = 0;
            for (auto item2 : item.second) {
                s[item2] = vecTmp[idx++];
            }
            vecTmp.clear();
        }
        return s;
    }

    //474 一和零 dp[i][j]表示容量i和j的最大子集个数
    int findMaxForm(vector<string>& strs, int m, int n) {
        int len = strs.size();
        vector<vector<vector<int>>> dp(len+1, vector<vector<int>>(m+1, vector<int>(n+1,0)));
        for(int k = 1; k <= len; ++k)
        {
            int one = 0, zero = 0;
            for (auto c : strs[k-1]) {
                if (c == '0') {
                    ++zero;
                } else{
                    ++one;
                }
            }
            for (int i = 0; i <= m; ++i) {
                for (int j = 0; j <= n; ++j) {
                    if (i>= zero && j>= one){
                        dp[k][i][j] = max(dp[k-1][i][j], dp[k-1][i-zero][j-one] + 1);
                    } else{
                        dp[k][i][j] = dp[k-1][i][j];
                    }
                }
            }
        }
        return dp[len][m][n];
    }

    //684 冗余链接
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        Make_Set(1000);
        for (auto item : edges) {
            if(item.size() != 2)
                continue;
            if (Find_Set(item[0]) == Find_Set(item[1]))
                return item;
            Union(item[0], item[1]);
        }
        auto ret = vector<int>(2,0);
        return ret;
    }

    //978. 最长湍流子数组
    int maxTurbulenceSize(vector<int>& arr) {
        //先判断场景1
        vector<int> flag(arr.size(),1);
        for (int i = 0; i < arr.size()-1; ++i) {
            if(i%2 == 1 && arr[i] > arr[i+1]) {
                flag[i+1] = flag[i] + 1;
            } else if (i%2 == 0 && arr[i] < arr[i+1]){
                flag[i+1] = flag[i] + 1;
            }
        }
        int maxlen1 = *max_element(flag.begin(), flag.end());
        fill(flag.begin(), flag.end(), 1);
        for (int i = 0; i < arr.size()-1; ++i) {
            if(i%2 == 1 && arr[i] < arr[i+1]) {
                flag[i+1] = flag[i] + 1;
            } else if (i%2 == 0 && arr[i] > arr[i+1]){
                flag[i+1] = flag[i] + 1;
            }
        }
        int maxlen2 = *max_element(flag.begin(), flag.end());
        return max(maxlen1, maxlen2);
    }
    //优化后的代码
    int maxTurbulenceSizeV2(vector<int>& arr){
        int up = 1, down = 1;//up表示前一个节点为上升趋势的最大值，down表示前一个节点下降趋势
        int max_len = 1;
        for (int i = 1; i < arr.size(); ++i) {
            if (arr[i] > arr[i-1]) {
                up = down + 1;
                down = 1;
            } else if (arr[i] < arr[i-1]) {
                down = up + 1;
                up = 1;
            } else {
                up = down = 1;
            }
            max_len = max(max_len, max(up, down));
        }
        return max_len;
    }

    //1018 可被 5 整除的二进制前缀
    vector<bool> prefixesDivBy5(vector<int>& A) {
        int val = 0;
        vector<bool> ret;
        for (auto i : A) {
            val = 2*val + i;
            if (val%5 == 0) {
                ret.push_back(true);
            } else {
                ret.push_back(false);
                val = val%5;
            }
        }
        return ret;
    }
    //1232 缀点成线
    static bool PointCmp(vector<int>& a, vector<int>& b){
        if(a.size() != 2 || b.size() != 2)
            return true;
        if(a[0] == b[0]) {
            return a[1] < b[1];
        }
        return a[0] < b[0];
    }
    bool checkStraightLine(vector<vector<int>>& coordinates) {
        if(coordinates.size() == 1 || coordinates.size() == 2)
            return true;
        std::sort(coordinates.begin(), coordinates.end(), PointCmp);
        for (int i = 2; i < coordinates.size(); ++i) {
            int wid1 = coordinates[i-1][0] - coordinates[i-2][0];
            int high1 = coordinates[i-1][1] - coordinates[i-2][1];
            int wid2 = coordinates[i][0] - coordinates[i-1][0];
            int high2 = coordinates[i][1] - coordinates[i-1][1];
            if (high1*wid2 != high2*wid1)
                return false;
        }
        return true;
    }
    //338. 比特位计数
    int countOne(int x) {
        int cnt = 0;
        while ( x>0 ) {
            x &= (x-1);
            ++cnt;
        }
        return cnt;
    }
    vector<int> countBits(int num) {
        vector<int> data(num+1);
        for (int i = 0; i <= num; ++i) {
            data[i] = countOne(i);
        }
        return data;
    }
    //503. 下一个更大元素 II -- 普通解法
    vector<int> nextGreaterElements(vector<int>& nums) {
        vector<int> max_list(nums.size(),-1);
        for (int i = 0; i < nums.size(); ++i) {
            bool has_find = false;
            for (int j = i; j < nums.size() + i; ++j) {
                if (nums[j%nums.size()] > nums[i]) {
                    max_list[i] = nums[j%nums.size()];
                    has_find = true;
                    break;
                }
            }
            if(!has_find) max_list[i] = -1;
        }
        return max_list;
    }
    // 279. 完全平方数
    int numSquares(int n) {
        vector<int> dp(n+1,1);
        for(auto i = 0; i < dp.size(); ++i) {
            dp[i] = i;
        }
        for (int i = 1; i <= 100 && i*i < dp.size(); ++i) {
            dp[i*i] = 1;
        }
        for(int i = 1; i <= n; ++i) {
            for (int j = 1; j*j < i; ++j) {
                dp[i] = min(dp[i], dp[i-j*j] + 1);
            }
        }
        return dp[n];
    }
};

int main() {
    Solution sol;
    auto ret = sol.numSquares(13);
    cout << ret << endl;
}