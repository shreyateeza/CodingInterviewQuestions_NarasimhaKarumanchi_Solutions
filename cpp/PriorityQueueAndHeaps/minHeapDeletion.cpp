#include <iostream>
#include <vector>

void heapify(std::vector<int>& heap, int i, int n) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && heap[left] < heap[smallest])
        smallest = left;
    if (right < n && heap[right] < heap[smallest])
        smallest = right;

    if (smallest != i) {
        std::swap(heap[i], heap[smallest]);
        heapify(heap, smallest, n);
    }
}

void deleteMin(std::vector<int>& heap) {
    int n = heap.size();
    if (n == 0) return;

    // Replace root with last element
    heap[0] = heap[n - 1];
    heap.pop_back();

    // Restore heap property
    heapify(heap, 0, heap.size());
}

void buildMinHeap(std::vector<int>& heap) {
    int n = heap.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(heap, i, n);
}

int main() {
    std::vector<int> heap = {3, 5, 1, 10, 2};

    buildMinHeap(heap);

    std::cout << "Min-heap before deletion: ";
    for (int val : heap) std::cout << val << " ";
    std::cout << std::endl;

    deleteMin(heap);

    std::cout << "Min-heap after deletion: ";
    for (int val : heap) std::cout << val << " ";
    std::cout << std::endl;

    return 0;
}