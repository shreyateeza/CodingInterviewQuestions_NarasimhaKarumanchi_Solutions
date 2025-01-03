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

void removeLoop(ListNode* list) {
    // add your logic here
	if(!list || !list->next) return;
	ListNode *slow = list->next, *fast = list->next->next, *prev = list->next;
	while(fast!=NULL && fast->next!=NULL){
		if(slow == fast){
			slow = list;
			break;
		}
		slow = slow->next;
		prev = fast->next;
		fast = fast->next->next;
	}
	if(fast == NULL || fast->next == NULL) return;
	while(slow != fast){
		prev = fast;
		slow = slow->next;
		fast =fast->next;
	}
	prev->next = NULL;
	return;
}