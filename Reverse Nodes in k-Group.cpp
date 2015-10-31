		/*Reverse Nodes in k-Group 使用栈进行保存*/
		ListNode* reverseKGroup(ListNode* head, int k)
		{
			stack<ListNode*> stack_node;
			int flag = 0; //判断是否是整个链表的第一个节点
			ListNode * last_node=nullptr;  //记录最后一个节点
			ListNode * my_head = nullptr; //记录首节点，进行返回
			ListNode * temp = nullptr; //临时节点
			int count = 0; //计数器，入栈一个count++
			while (head)
			{
				//压入k个节点
				while (head && count<k)
				{
					stack_node.push(head);
					head = head->next;
					count++;
				}
				//如果个数足够
				if (count == k)
				{
					for (int i = 0; i < k;i++)
					{
						temp = stack_node.top();
						if (!flag) //第一个节点，需要赋值给my_head
						{
							flag = 1;
							my_head = temp;
						}
						if (last_node !=nullptr)  //链到尾部
						{
							last_node->next = temp;
						}
						last_node = temp;
						stack_node.pop();
					}
					last_node->next = nullptr;
					count = 0;
				}
				//尾部个数不够
				else
				{
					for(int i = 0; i < count; i++)
					{
						temp = stack_node.top();
						stack_node.pop();
					}
					if (!flag) //第一个节点，需要赋值给my_head
					{
						flag = 1;
						my_head = temp;
					}
					if (last_node != nullptr)  //链到尾部
					{
						last_node->next = temp;
					}
				}
			}
			return my_head;
		}