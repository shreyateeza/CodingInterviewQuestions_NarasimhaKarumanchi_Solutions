// C++ Program to demonstrate how to implement the quick sort algorithm
#include <bits/stdc++.h>
using namespace std;

int partition(vector<int> &nums, int low, int high) {
    // Selecting last element as the pivot
    int pivot = nums[high];
    // Index of elemment just before the last element
    // It is used for swapping
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than or equal to pivot
        if (nums[j] <= pivot) {
            i++;
            swap(nums[i], nums[j]);
        }
    }
    // Put pivot to its position
    swap(nums[i + 1], nums[high]);
    // Return the point of partition
    return (i + 1);
}

void quickSort(vector<int> &nums, int low, int high) {
    // Base case: This part will be executed till the starting index low is lesser than the ending index high
    if (low < high) {
        // pi is Partitioning Index, arr[p] is now at right place
        int pi = partition(nums, low, high);
        // Separately sort elements before and after the Partition Index pi
        quickSort(nums, low, pi - 1);
        quickSort(nums, pi + 1, high);
    }
}

int main() {
    vector<int> nums = {10, 7, 8, 9, 1, 5};
    int n = nums.size();
    // Calling quicksort for the vector vec
    quickSort(nums, 0, n - 1);
    for (auto i : nums) {
        cout << i << " ";
    }
    return 0;
}