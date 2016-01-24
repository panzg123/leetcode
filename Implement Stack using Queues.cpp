class Stack
{
public:
    queue<int> q;
    queue<int> q_swap;

    // Push element x onto stack.
    void push(int x)
    {
        if (q.empty())
            q.push(x);
        else
        {
            while (!q.empty())
            {
                auto temp = q.front();
                q_swap.push(temp);
                q.pop();
            }
            q.push(x);
            while (!q_swap.empty())
            {
                auto tmp = q_swap.front();
                q.push(tmp);
                q_swap.pop();
            }
        }
    }

    // Removes the element on top of the stack.
    void pop()
    {
        q.pop();
    }

    // Get the top element.
    int top()
    {
        return q.front();
    }

    // Return whether the stack is empty.
    bool empty()
    {
        return q.empty();
    }
};