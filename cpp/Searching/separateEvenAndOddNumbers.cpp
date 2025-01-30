#include <bits/stdc++.h>
using namespace std;

// Function to segregate even and odd numbers
void segregate(vector<int>& arr) {
    int low = 0, high = arr.size() - 1;
    // Iterate while high >= low
    while (low <= high) {
        // Check if arr[low] is odd
        if (arr[low] % 2 != 0) {
            if (arr[high] % 2 == 0) {
                // Swap arr[low] and arr[high]
                swap(arr[low], arr[high]);
                low++;
                high--;
            } 
            else {
                high--;
            }
        } 
        else {
            low++;
        }
    }
}

// Driver Code
int main() {
    vector<int> arr = {1, 2, 3, 4, 5, 6};
    segregate(arr);
    for (int x : arr) cout << x << " ";
    return 0;
}