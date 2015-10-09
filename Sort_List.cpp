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
    ListNode* sortList(ListNode* head)
    {
        if (head == nullptr || head->next == nullptr) return head;
        ListNode *fast = head, *slow = head;
        while (fast->next != nullptr && fast->next->next != nullptr)
            {
                fast = fast->next->next;
                slow = slow->next;
            }
        //断开
        ListNode *temp = slow;
        slow = slow->next;
        temp->next = nullptr;
		//前后半段分别排序
        ListNode *l1 = sortList(head);
        ListNode *l2 = sortList(slow);
        return mergeTwoLists(l1, l2);
    }
    ListNode* mergeTwoLists(ListNode* l1, ListNode *l2)
    {
        if (l1 == nullptr) return l2;
        if (l2 == nullptr) return l1;
        ListNode head(-1);
        ListNode *p = &head;
        while (l1 != nullptr && l2 != nullptr)
            {
                if (l1->val < l2->val)
                    {
                        p->next = l1;
                        l1 = l1->next;
                    }
                else
                    {
                        p->next = l2;
                        l2 = l2->next;
                    }
                p = p->next;
            }
        p->next = l1 == nullptr ? l2 : l1;
        return head.next;
    }
};