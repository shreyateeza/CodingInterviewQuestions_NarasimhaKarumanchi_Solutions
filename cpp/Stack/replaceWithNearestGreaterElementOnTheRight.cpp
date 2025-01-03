#include <iostream>
#include <set>
#include <vector>

using namespace std;

void solve(vector<int>& arr)
{
	set<int> s;
	for (int i = arr.size() - 1; i >= 0;
		i--) { // traversing the array backwards
		s.insert(arr[i]); // inserting the element into set
		auto it
			= s.upper_bound(arr[i]); // finding upper bound
		if (it == s.end())
			arr[i] = -1; // if upper_bound does not exist
						// then -1
		else
			arr[i] = *it; // if upper_bound exists, lets
						// take it
	}
}

void printArray(vector<int>& arr)
{
	for (int i : arr)
		cout << i << " ";
	cout << "\n";
}

int main()
{
	vector<int> arr = { 8, 58, 71, 18, 31, 32, 63, 92,
						43, 3, 91, 93, 25, 80, 28 };
	printArray(arr);
	solve(arr);
	printArray(arr);
	return 0;
}
