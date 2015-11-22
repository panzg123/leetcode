/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
            ListNode m_head(-1);
			m_head.next = head;
			ListNode *prev = &m_head;
			ListNode *cur = head;
			while (cur)
			{
				if (cur->val == val)
				{
					prev->next = cur->next;
					cur = prev->next;
				}
				else
				{
					prev = cur;
					cur = cur->next;
				}
			}
			return m_head.next;
    }
};