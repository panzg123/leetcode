class Solution {
public:
	//ʱ�临�Ӷ� O(n)���ռ临�Ӷ� O(n)
    int longestValidParentheses(string s) {
    	int result = 0,tmpTop = 0;                  //�ֱ��¼�����ջ��Ԫ�ص��±�
    	stack<int> cStack;
    
    	for (int i = 0; i < s.size(); ++i)
    	{
    		if (s[i] == '(')                       //�����'(',���Ž�ջ
    		{
    			cStack.push(i);
    		}
    		else if (cStack.empty())               //�����')'��ջΪ�գ���¼�µ�ջ��λ��ΪtmpTop=i+1
    		{
    			tmpTop = i + 1;
    		}
    		else
    		{
    			cStack.pop();                     //�����')'��ջ��Ϊ�գ�����ջ��Ԫ��
    			if (cStack.empty())               //�����ʱջΪ�գ���ʱ����Ч�ַ�����Ϊi-topTmp+1
    				result = max(result, i - tmpTop + 1);
    			else                              //�����ʱջ��Ϊ�գ���ջ��Ԫ�غ�������ŶԿ϶���ƥ��ģ������Ч�ַ�����Ϊi-cStack.top()
    				result = max(result, i - cStack.top());
    		}
    	}
    	return result;
    }
};