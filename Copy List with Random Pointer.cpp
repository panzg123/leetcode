/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;     
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
class Solution {
public:
	/*Copy List with Random Pointer 使用unordered_map,时间复杂度、空间复杂度都为O(N)*/
    RandomListNode *copyRandomList(RandomListNode *head) {
        unordered_map<RandomListNode*, RandomListNode*> result;
			RandomListNode* m_head = head;
			while (m_head != nullptr)
			{
				RandomListNode * node = new RandomListNode(m_head->label);
				result[m_head] = node;
				m_head = m_head->next;
			}
			m_head = head;
			while (m_head)
			{
				if (m_head->next != nullptr)
					result[m_head]->next = result[m_head->next];
				if (m_head->random != nullptr)
					result[m_head]->random = result[m_head->random];
				m_head = m_head->next;
			}
			return result[head];
    }
};