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
	/*Intersection of Two Linked Lists，找两个链表的交点 用Map空间复杂度高*/
		ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
		{
			unordered_map<ListNode*, int> m_map;
			ListNode *head_a = headA, *head_b = headB;
			while (head_a)
			{
				m_map[head_a] = 1;
				head_a = head_a->next;
			}
			while (head_b)
			{
				auto res = m_map.find(head_b);
				if (res != m_map.end())
					return head_b;
				else
					m_map[head_b] = 1;
				head_b = head_b->next;
			}
			return nullptr;
		}
		/*方法2，时间复杂度O(N)，空间复杂度O(1)*/
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
            ListNode *head_a = headA, *head_b = headB;
			int lengthA = 0, lengthB = 0;
			while (head_a)
			{
				lengthA++;
				head_a = head_a->next;
			}
			while (head_b)
			{
				lengthB++;
				head_b = head_b->next;
			}
			int diff = abs(lengthA - lengthB); //计算两个链表的长短之差
			int flag = lengthA < lengthB ? 1 : 0;
			while (diff--)
			{
				if (flag)
					headB = headB->next;
				else
					headA = headA->next;
			}
			while (headA && headB)
			{
				if (headA == headB)
					return headA;
				else
				{
					headA = headA->next;
					headB = headB->next;
				}
			}
			return nullptr;
    }
};