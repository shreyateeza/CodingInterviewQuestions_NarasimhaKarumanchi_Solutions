#include <iostream>
#include <vector>
using namespace std;

// Function to insert a new value into the min-heap
void insertMinHeap(vector<int>& heap, int value) {
    // Step 1: Add the new value at the end
    heap.push_back(value);
    int i = heap.size() - 1;

    // Step 2: Bubble up to maintain min-heap property
    while (i != 0 && heap[(i - 1) / 2] > heap[i]) {
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
    vector<int> heap = {10, 20, 30, 40, 60, 70}; // Already a min-heap

    cout << "Initial min-heap:\n";
    printHeap(heap);

    insertMinHeap(heap, 15);

    cout << "After inserting 15:\n";
    printHeap(heap);

    return 0;
}