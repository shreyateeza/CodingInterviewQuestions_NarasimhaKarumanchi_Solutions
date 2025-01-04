#include <bits/stdc++.h>
using namespace std;

// A Dequeue (Double ended queue) based method for printing 
// maximum element of all subarrays of size k
void printKMax(const vector<int>& a, int k) {
  
    // Create a Double Ended Queue, Qi that will store indexes
    // of array elements. The queue will store indexes of 
    // useful elements in every window and it will maintain 
    // decreasing order of values from front to rear in Qi, 
    // i.e., a[Qi.front[]] to a[Qi.rear()] are sorted in 
    // decreasing order
    deque<int> Qi(k);

    // Process first k (or first window) elements of array
    int i;
    for (i = 0; i < k; ++i) {
      
        // For every element, the previous smaller elements 
        // are useless so remove them from Qi
        while (!Qi.empty() && a[i] >= a[Qi.back()]) {
          
            // Remove from rear
            Qi.pop_back();
        }
        // Add new element at rear of queue
        Qi.push_back(i);
    }

    // Process rest of the elements, i.e., from a[k] to a[n-1]
    for (; i < a.size(); ++i) {
      
        // The element at the front of the queue is the largest 
        // element of previous window, so print it
        cout << a[Qi.front()] << " ";

        // Remove the elements which are out of this window
        while (!Qi.empty() && Qi.front() <= i - k) {
          
            // Remove from front of queue
            Qi.pop_front();
        }

        // Remove all elements smaller than the currently being 
        // added element (remove useless elements)
        while (!Qi.empty() && a[i] >= a[Qi.back()]) {
            Qi.pop_back();
        }

        // Add current element at the rear of Qi
        Qi.push_back(i);
    }

    // Print the maximum element of last window
    cout << a[Qi.front()];
}

// Driver's code
int main() {
    vector<int> a = {12, 1, 78, 90, 57, 89, 56};
    int k = 3;

    // Function call
    printKMax(a, k);
    return 0;
}