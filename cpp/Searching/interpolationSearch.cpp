// C++ program to implement interpolation search by using iteration approach
#include<bits/stdc++.h>
using namespace std;

int interpolationSearch(int arr[], int n, int x){
	// Find indexes of two corners
	int low = 0, high = n-1;
	// Since array is sorted, an element present in array must be in range defined by corner
	while (low <= high && x >= arr[low] && x <= arr[high]){
		if (low == high)
		if (arr[low] == x) return low;
		// Probing the position with keeping uniform distribution in mind.
		int position = low + (((double)(high - low) / (arr[high] - arr[low])) * (x - arr[low]));

		// Condition of target found
		if (arr[position] == x) return position;
		// If x is larger, x is in upper part
		if (arr[position] < x) low = position + 1;
		// If x is smaller, x is in the lower part
		else high = position - 1;
	}
	return -1;
}

// Main function
int main(){
	// Array of items on whighch search will be conducted.
	int arr[] = {10, 12, 13, 16, 18, 19, 20, 21, 22, 23, 24, 33, 35, 42, 47};
	int n = sizeof(arr)/sizeof(arr[0]);
	int x = 18; // Element to be searched
	int index = interpolationSearch(arr, n, x);
	// If element was found
	if (index != -1) cout << "Element found at index " << index;
	else cout << "Element not found.";
	return 0;
}
