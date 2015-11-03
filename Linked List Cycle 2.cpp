	/*Linked List Cycle 2，找环的起点，经典快慢指针问题*/
		ListNode *detectCycle(ListNode *head)
		{
			if (!head) return 0;

			ListNode *fast = head, *slow = head;
			if (fast->next && fast->next->next)
			{
				do
				{
					fast = fast->next->next;
					slow = slow->next;
				} while (fast != slow && fast->next && fast->next->next);

				// the point is when two pointers meet, the distance from the position 
				// to the entry is equal to the distance from head to the entry

				if (fast == slow)
				{
					for (fast = head; fast != slow; fast = fast->next, slow = slow->next);
					return fast;
				}
			}
			return 0;
		}