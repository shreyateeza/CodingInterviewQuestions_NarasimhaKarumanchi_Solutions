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

ListNode* getStartingNodeOfLoop(ListNode* list){
	// add your logic here
	if(!list->next) return NULL;
	ListNode *slow = list->next, *fast = list->next->next;
	while(fast!=NULL && fast->next!=NULL){
		if(slow==fast){
			slow = list;
			break;
		}
		slow = slow->next;
		fast = fast->next->next;
	}
	if(!fast || !fast->next) return NULL;
	while(slow != fast){
		slow = slow->next;
		fast = fast->next;
	}
	return slow;
}