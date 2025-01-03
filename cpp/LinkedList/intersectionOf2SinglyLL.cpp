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
ListNode *findIntersectionNode(ListNode *A, ListNode *B, int difference){
	while(difference>0){
		A = A->next;
		difference--;
	}
	while(A!=NULL && B!=NULL){
		if(A == B) return A;
		A = A->next;
		B = B->next;
	}
	return NULL;
}


ListNode* getIntersectionNode(ListNode *A, ListNode *B) {
    // add your logic here
	int NA = 0, NB = 0;
	ListNode *a = A, *b = B;
	while(a != NULL){
		NA++;
		a = a->next;
	}
	while(b != NULL){
		NB++;
		b = b->next;
	}
	if(NA > NB) return findIntersectionNode(A, B, NA-NB);
	else return findIntersectionNode(B, A, NB-NA);
}