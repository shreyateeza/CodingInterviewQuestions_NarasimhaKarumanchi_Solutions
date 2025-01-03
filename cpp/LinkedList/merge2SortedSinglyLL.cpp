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

ListNode* mergeTwoSortedList (ListNode* firstList, ListNode* secondList) {
    // add your logic here
	ListNode *result = new ListNode(-1);
	ListNode *dummy = result;
	while(firstList && secondList){
		if(firstList->data < secondList->data){
			result->next = new ListNode(firstList->data);
			firstList = firstList->next;
		}
		else{
			result->next = new ListNode(secondList->data);
			secondList = secondList->next;
		}
		result = result->next;
	}
	if(firstList){
		result->next = firstList;
	}
	if(secondList){
		result->next = secondList;
	}
	return dummy->next;
}