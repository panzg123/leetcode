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
	/*Linked List Cycle,判断链表是否有环,经典快慢指针问题*/
    bool hasCycle(ListNode *head) {
            ListNode* fast = head;
			ListNode* slow = head;
			while (fast)
			{
				if (fast->next)
					fast = fast->next->next;
				else
					return false;
				slow = slow->next;
				if (fast == slow)
					return true;
			}
			return false;
    }
};