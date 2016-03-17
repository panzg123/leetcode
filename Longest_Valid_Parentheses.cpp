class Solution {
public:
	//时间复杂度 O(n)，空间复杂度 O(n)
    int longestValidParentheses(string s) {
    	int result = 0,tmpTop = 0;                  //分别记录结果和栈顶元素的下标
    	stack<int> cStack;
    
    	for (int i = 0; i < s.size(); ++i)
    	{
    		if (s[i] == '(')                       //如果是'(',符号进栈
    		{
    			cStack.push(i);
    		}
    		else if (cStack.empty())               //如果是')'且栈为空，记录新的栈顶位置为tmpTop=i+1
    		{
    			tmpTop = i + 1;
    		}
    		else
    		{
    			cStack.pop();                     //如果是')'且栈不为空，弹出栈顶元素
    			if (cStack.empty())               //如果此时栈为空，此时的有效字符长度为i-topTmp+1
    				result = max(result, i - tmpTop + 1);
    			else                              //如果此时栈不为空，则栈顶元素后面的括号对肯定是匹配的，因此有效字符长度为i-cStack.top()
    				result = max(result, i - cStack.top());
    		}
    	}
    	return result;
    }
};