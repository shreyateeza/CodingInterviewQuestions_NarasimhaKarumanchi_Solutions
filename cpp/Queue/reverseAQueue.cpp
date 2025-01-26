// C++ implementation of the above approach
#include <bits/stdc++.h>
using namespace std;

// Function to return the reversed queue
queue<int> reverse(queue<int> q){
	// Size of queue
	int s = q.size();

	// Second queue
	queue<int> ans;

	for (int i = 0; i < s; i++) {
		// Get the last element to the front of queue
		for (int j = 0; j < q.size() - 1; j++) {
			int x = q.front();
			q.pop();
			q.push(x);
		}
		// Get the last element and add it to the new queue
		ans.push(q.front());
		q.pop();
	}
	return ans;
}

// Driver Code
int main(){
	queue<int> q;

	// Insert elements
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);
	q.push(5);

	q = reverse(q);

	// Print the queue
	while (!q.empty()) {
		cout << q.front() << " ";
		q.pop();
	}
	return 0;
}
