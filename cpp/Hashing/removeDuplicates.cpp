#include <bits/stdc++.h>

using namespace std;

class removeDuplicate {

  public:

    void duplicate(int arr[], int n) {
      int mark[n] = {
        1
      };
      for (int i = 0; i < n; i++) {

        if (mark[i] == 1) {

          for (int j = i + 1; j < n; j++) {

            if (arr[i] == arr[j]) {

              mark[j] = 0;
            }
          }
        }
      }

      for (int i = 0; i < n; i++) {
        if (mark[i] == 0) {
          cout << arr[i] << ",";
        }
      }
    }

};

int main() {

  int arr[] = {4, 3, 9, 2, 4, 1, 10, 89, 34} ;
  int n = 9;

  removeDuplicate d1;
  d1.duplicate(arr, n);

  return 0;
}