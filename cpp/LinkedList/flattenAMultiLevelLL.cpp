/* This is the ListNode class definition

class ListNode {
public:
	int data;
	ListNode* next;
	ListNode* random;

	ListNode(int data) {
		this->data = data;
		this->next = NULL;
		this->random = NULL;
	}
};
*/
ListNode* mergeTheLinkedLists(ListNode *list1, ListNode *list2){
	if(!list1 && !list2) return NULL;
	if(!list1) return list2;
	if(!list2){
		ListNode *result = list1;
		result->next = mergeTheLinkedLists(list1->random, NULL);
		result->random = NULL;
		return result;
	}
	ListNode *result;
	if(list1->data < list2->data){
		result = list1;
		result->next = mergeTheLinkedLists(list1->random, list2);
	}
	else{
		result = list2;
		result->next = mergeTheLinkedLists(list1, list2->next);
	}
	result->random = NULL;
	return result;
}


ListNode* flattenTheLinkedList(ListNode* root) {
	// add your logic here
	if(!root) return root;
	return mergeTheLinkedLists(root, flattenTheLinkedList(root->next));
	
}