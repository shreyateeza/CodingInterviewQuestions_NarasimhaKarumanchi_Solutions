#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> heap = {3, 5, 1, 10, 2};

    // Convert to max-heap
    make_heap(heap.begin(), heap.end());

    cout << "Max-heap: ";
    for (int val : heap) {
        cout << val << " ";
    }
    cout << endl;

    // Push a new element
    heap.push_back(7);
    push_heap(heap.begin(), heap.end());

    cout << "After push_heap(7): ";
    for (int val : heap) {
        cout << val << " ";
    }
    cout << endl;

    // Pop the max element
    pop_heap(heap.begin(), heap.end());
    int maxVal = heap.back();
    heap.pop_back();

    cout << "After pop_heap(): ";
    for (int val : heap) {
        cout << val << " ";
    }
    cout << "\nPopped max value: " << maxVal << endl;

    return 0;
}

/*
MIN HEAP
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> heap = {3, 5, 1, 10, 2};

    // Convert to min-heap using greater<int>
    make_heap(heap.begin(), heap.end(), greater<int>());

    cout << "Min-heap: ";
    for (int val : heap) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}