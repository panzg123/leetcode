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
    ListNode* oddEvenList(ListNode* head) {
            if (head == nullptr)
				return head;
			ListNode* insert_pos = head;
			ListNode* del_pos = head->next;
			while (del_pos && del_pos->next)
			{
				ListNode *temp_del = del_pos->next->next;
				//delete the node
				ListNode *node_del = del_pos->next;
				del_pos->next = del_pos->next->next;
				//insert
				node_del->next = insert_pos->next;
				insert_pos->next = node_del;
				//update the pos
				insert_pos = insert_pos->next;
				del_pos = temp_del;
			}
			return head;
    }
};