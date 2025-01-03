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
ListNode *sortedHead;

void insertionSortUtil(ListNode *head){
	if(sortedHead==NULL || sortedHead->data >= head->data){
		head->next = sortedHead;
		sortedHead = head;
		return;
	}
	ListNode *currentNode = sortedHead;
	while(currentNode->next!= NULL && currentNode->next->data < head->data){
		currentNode = currentNode->next;
	}
	head->next = currentNode->next;
	currentNode->next = head;
	return;
}


ListNode* insertionSort(ListNode* head) {
	// add your logic here
	sortedHead = NULL;
	ListNode *currentNode = head;
	while(currentNode != NULL){
		ListNode *nextNode = currentNode->next;
		insertionSortUtil(currentNode);
		currentNode = nextNode;
	}
	return sortedHead;	
}