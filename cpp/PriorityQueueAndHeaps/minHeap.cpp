#include <iostream>
#include <vector>

void heapify(std::vector<int>& arr, int n, int i) {
    int smallest = i;       // Initialize smallest as root
    int left = 2 * i + 1;   // left child
    int right = 2 * i + 2;  // right child

    // If left child is smaller than root
    if (left < n && arr[left] < arr[smallest])
        smallest = left;

    // If right child is smaller than smallest so far
    if (right < n && arr[right] < arr[smallest])
        smallest = right;

    // If smallest is not root
    if (smallest != i) {
        std::swap(arr[i], arr[smallest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, smallest);
    }
}

void buildMinHeap(std::vector<int>& arr) {
    int n = arr.size();

    // Start from last non-leaf node and heapify each node
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
}

int main() {
    std::vector<int> arr = {3, 5, 1, 10, 2};

    buildMinHeap(arr);

    std::cout << "Min heap: ";
    for (int val : arr) {
        std::cout << val << " ";
    }
    return 0;
}