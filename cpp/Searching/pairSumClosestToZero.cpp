#include <bits/stdc++.h>
using namespace std;

// Function to return the sum of the pair 
// with sum closest to 0
int closestPairSum(vector<int>& arr) {
  
    sort(arr.begin(), arr.end());    
    
    int n = arr.size();
    
    // Variable to store the closest sum
    int res = INT_MAX;

    // Iterate over the array
    for (int i = 0; i < n; i++) {
      
        // Consider current element as first 
        // element of the pair and find the
        // other element using binary search
        int x = arr[i];
        
        int left = i + 1, right = n - 1;

        while (left <= right) {
            int mid = (left + right) / 2;

            int curr = arr[mid] + x;

            // If exact pair is found
            if (curr == 0) {
                return 0; 
            }

            // Update res if the current pair is closer
            if (abs(curr) < abs(res)) {
                res = curr;
            }

            // If current is smaller than 0,
            // go to right side. Else on the
            // left side.
            if (curr < 0) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }

    return res;
}

// Driver program to test the above function
int main() {
    vector<int> arr = {-10, -3, 0, 5, 9, 20};
    int res = closestPairSum(arr);
    cout << "The closest sum to 0 is " << res << endl;
    return 0;
}