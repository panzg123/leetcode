/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution
{
public:
    /*逆转链表，用栈,时间复杂度O(N)，空间复杂度O(N)*/
    ListNode* reverseList(ListNode* head)
    {
        if (head == nullptr)
            return head;
        stack<ListNode*> node_stack;
        while (head)
        {
            node_stack.push(head);
            head = head->next;
        }
        ListNode *myhead = node_stack.top();
        head = myhead;
        node_stack.pop();
        while (!node_stack.empty())
        {
            ListNode * node = node_stack.top();
            node_stack.pop();
            head->next = node;
            head = head->next;
        }
        head->next = nullptr;
        return myhead;
    }
    /*逆转链表，遍历，时间复杂度O(N)，空间复杂度O(1)*/
    ListNode* reverseList(ListNode* head)
    {
        ListNode *pos = nullptr,*cur = nullptr;
        if (head && head->next)
        {
            pos = head->next->next;
            cur = head->next;
            head->next->next = head;
            head->next = nullptr;
            head = cur;
            cur = pos;
        }
        else
            return head;
        while (head && cur)
        {
            pos = cur->next;
            cur->next = head;
            head = cur;
            cur = pos;

        }
        return head;
    }
};