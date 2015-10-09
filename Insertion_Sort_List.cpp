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
    ListNode *insertionSortList(ListNode *head)
    {
        ListNode dummy(INT_MIN);
        //dummy.next = head;
        for (ListNode *cur = head; cur != nullptr;)
            {
                auto pos = findInsertPos(&dummy, cur->val);
                ListNode *tmp = cur->next;
                cur->next = pos->next;
                pos->next = cur;
                cur = tmp;
            }
        return dummy.next;
    }
    ListNode* findInsertPos(ListNode *head, int x)
    {
        ListNode *pre = nullptr;
        for (ListNode *cur = head; cur != nullptr && cur->val <= x;
                pre = cur, cur = cur->next)
            ;
        return pre;
    }
};