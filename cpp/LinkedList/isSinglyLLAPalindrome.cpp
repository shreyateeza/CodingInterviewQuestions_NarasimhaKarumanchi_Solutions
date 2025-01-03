/* This is the ListNode class definition

class ListNode {
public:
	int data;
	ListNode* next;

	ListNode(int data) {
		this->data = data;
		this->next = NULL;
	}
};
*/

bool isPalindrome(ListNode* list) {
    // add your logic here
	int len = 0;
	ListNode *temp = list;
	while(temp != NULL){
		len++;
		temp = temp->next;
	}
	if(!list) return true;
	stack<int> st;
	ListNode *slow = list, *fast = list;
	while(fast->next!=NULL && fast->next->next!=NULL){
		st.push(slow->data);
		slow = slow->next;
		fast = fast->next->next;
	}
	st.push(slow->data);
	if(len%2 == 0) slow = slow->next;
	while(slow!=NULL){
		if(st.top()!=slow->data) return false;
		st.pop();
		slow = slow->next;
	}
	return true;
}