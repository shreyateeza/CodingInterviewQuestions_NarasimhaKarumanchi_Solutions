#include<bits/stdc++.h>
using namespace std;

int findRepeatingElementArray(int arr[], int n){
   int minRetIndex = -1;
   set<int> visitedElements;
   for (int i = n - 1; i >= 0; i--){
      if (visitedElements.find(arr[i]) != visitedElements.end()) minRetIndex = i;
      else visitedElements.insert(arr[i]);
   }
   if (minRetIndex != -1) return arr[minRetIndex];
   return -1;
}

int main(){
   int arr[] = {4, 1, 8, 9, 7, 2, 1, 6, 4};
   int n = sizeof(arr) / sizeof(arr[0]);
   cout<<"The element with repeated occurence is "<<findRepeatingElementArray(arr, n);
}