#include <iostream>
#include <vector>
using namespace std;

// Function to insert a new value into the max-heap
void insertMaxHeap(vector<int>& heap, int value) {
    // Step 1: Add the new value at the end
    heap.push_back(value);
    int i = heap.size() - 1;

    // Step 2: Bubble up to maintain max-heap property
    while (i != 0 && heap[(i - 1) / 2] < heap[i]) {
        swap(heap[i], heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Utility function to print the heap
void printHeap(const vector<int>& heap) {
    for (int val : heap)
        cout << val << " ";
    cout << endl;
}

int main() {
    vector<int> heap = {70, 60, 40, 30, 20, 10}; // Already a max-heap

    cout << "Initial max-heap:\n";
    printHeap(heap);

    insertMaxHeap(heap, 65);

    cout << "After inserting 65:\n";
    printHeap(heap);

    return 0;
}