class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> number_stack;
		int a, b, res;
		for (size_t i = 0; i < tokens.size(); i++)
		{
			string temp = tokens[i];
			if (temp.size() == 1 && (temp == "+" || temp == "-" || temp == "/" || temp == "*"))
			{
				a = number_stack.top();
				number_stack.pop();
				b = number_stack.top();
				number_stack.pop();
				if (temp == "+") res = a + b;
				else if(temp == "-") res = b - a;
				else if (temp == "/") res = b/a;
				else res = a*b;
				number_stack.push(res);

			}
			else
			{
				number_stack.push(atoi(temp.c_str()));
			}
		}
		return number_stack.top();
    }
};