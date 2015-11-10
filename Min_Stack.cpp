/*Min Stack*/
class MinStack {
public:
			//int1记录当前节点的值，int2记录到当前节点的最小值
			stack<pair<int, int>> st;
			void push(int x) 
			{
				int min_value;
				if (st.empty())
					min_value = x;
				else
					min_value = st.top().second < x ? st.top().second : x;
				pair<int, int> p(x, min_value);
				st.push(p);
			}

			void pop()
			{
				st.pop();
			}

			int top() 
			{
				return st.top().first;
			}

			int getMin()
			{
				return st.top().second;
			}
};