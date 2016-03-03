//Palindrome Linked List,https://leetcode.com/problems/palindrome-linked-list/
//直接用栈可水过，但是空间复杂度为O(N)
bool isPalindrome(ListNode* head)
{
    stack<ListNode*> s;
    ListNode *cur = head;
    while (cur)
    {
        s.push(cur);
        cur = cur->next;
    }
    cur = head;
    while (cur)
    {
        if (cur->val != s.top()->val)
            return false;
        cur = cur->next;
        s.pop();
    }
    return true;
}
//Palindrome Linked List,首先找到链表的中间节点，将前半部分链表逆置，两个指针向后依次比较,空间复杂度为O(1)
bool isPalindrome_v2(ListNode* head)
{
    int count_length = 0;
    ListNode* cur = head;
    ListNode* reverse_head;
    int low_step = 0;
    //计算整个链表长度
    while (cur)
    {
        count_length++;
        cur = cur->next;
    }

    //获取后半部分的首指针
    cur = head;
    int i = 0;
    int len = (count_length % 2) == 0 ? count_length / 2 : count_length / 2 + 1;
    while (i< len)
    {
        i++;
        cur = cur->next;
    }

    //翻转长度为count_length/2的链表
    reverse_head = reverse_list_by_length(head, count_length/2);

    //前后两端比较
    while (cur!=nullptr && reverse_head != nullptr)
    {
        if(cur->val != reverse_head->val)
            return false;
        cur = cur->next;
        reverse_head = reverse_head->next;
    }
    return true;
}

//根据长度来翻转链表
ListNode* reverse_list_by_length(ListNode* head, int length)
{
    ListNode *pre = nullptr;
    ListNode *next = nullptr;
    int step = 0;
    while (step < length)
    {
        next = head->next;
        head->next = pre;
        pre = head;
        head = next;
        step++;
    }
    return pre;
}