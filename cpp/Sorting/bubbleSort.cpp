// C++ program for optimized implementation of Bubble sort
#include <bits/stdc++.h>
using namespace std;

// An optimized version of Bubble Sort
void bubbleSort(vector<int>& v) {
 
    int n = v.size();

    for (int i = 0; i < n - 1; i++) {

        // Creating a flag to denote the case wwhen array
        // is sorted and doesnt cause any swap
        bool flag = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (v[j] > v[j + 1]) {
                swap(v[j], v[j + 1]);
              
                  // Setting flag true when swap happened
                flag = true;
            }
        }
      
          // Checking if the flag is set or not
        if (!flag)
            break;
    }
}

int main() {
    vector<int> v = {5, 1, 4, 2, 8};

    bubbleSort(v);

    for (auto i : v)
        cout << i << " ";
    return 0;
}