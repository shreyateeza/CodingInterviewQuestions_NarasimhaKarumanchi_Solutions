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

ListNode* addTwoNumbers(ListNode* firstList, ListNode* secondList) {
	// add your logic here
	ListNode *result = new ListNode(-1);
	ListNode *dummy = result;
	int sum = 0, carry = 0;
	while(firstList && secondList){
		sum = firstList->data + secondList->data + carry;
		if(sum>9){
			sum = sum%10;
			carry = 1;
		}
		else carry = 0;
		
		result->next = new ListNode(sum);
		result = result->next;
		firstList = firstList->next;
		secondList = secondList->next;
	}
	while(firstList){
		sum = firstList->data + carry;
		if(sum>9){
			sum = sum%10;
			carry = 1;
		}
		else carry = 0;
		result->next = new ListNode(sum);
		result = result->next;
		firstList = firstList->next;
	}
	while(secondList){
		sum = secondList->data + carry;
		if(sum>9){
			sum = sum%10;
			carry = 1;
		}
		else carry = 0;
		result->next = new ListNode(sum);
		result = result->next;
		secondList = secondList->next;
	}
	if(carry == 1){
		result->next = new ListNode(carry);
	}
	return dummy->next;
}