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
    /*Merge k Sorted Lists 两两合并超时,用优先队列*/
    struct k_sort_compare
    {
        bool operator()(const ListNode* l, const ListNode* r)
        {
            return l->val > r->val;
        }
    };
    ListNode* mergeKLists(vector<ListNode*>& lists)
    {
        if (lists.size() == 0) return NULL;

        ListNode * head = NULL;
        ListNode * ptr = NULL;
		//清除空链表
        vector<int> null_index;
        for (int i = 0; i<lists.size(); i++)
            {
                if (lists[i] == NULL) null_index.push_back(i);
            }
        cout << null_index.size() << endl;
        for (int i = null_index.size() - 1; i<null_index.size(); i--)
            {
                lists.erase(lists.begin() + null_index[i]);
            }
		//优先队列
        priority_queue<ListNode*, vector<ListNode*>, k_sort_compare> pq;
        for (int i = 0; i<lists.size(); i++)
            {
                pq.push(lists[i]);
            }
        while (pq.size() > 0)
            {
                ListNode * m = pq.top();
                pq.pop();
				//插入链表的下一个元素
                if (m->next != NULL) pq.push(m->next);
                m->next = NULL;
                if (head == NULL)
                    {
                        head = m;
                        ptr = head;
                    }
                else
                    {
                        ptr->next = m;
                        ptr = ptr->next;
                    }

            }
        return head;
    }
};