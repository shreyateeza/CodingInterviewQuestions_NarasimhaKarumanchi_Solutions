// C++ program for shuffling desk of cards.
#include <bits/stdc++.h>
using namespace std;

// Function which shuffle and print the array
void shuffle(int card[], int n)
{
	// Initialize seed randomly
	srand(time(0));

	for (int i=0; i<n ;i++)
	{
		// Random for remaining positions.
		int r = i + (rand() % (52 -i));

		swap(card[i], card[r]);
	}
}

// Driver code
int main()
{
	// Array from 0 to 51
	int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8,
			9, 10, 11, 12, 13, 14, 15,
			16, 17, 18, 19, 20, 21, 22,
			23, 24, 25, 26, 27, 28, 29,
			30, 31, 32, 33, 34, 35, 36,
			37, 38, 39, 40, 41, 42, 43,
			44, 45, 46, 47, 48, 49, 50,
			51};

	shuffle(a, 52);

	// Printing all shuffled elements of cards
	for (int i=0; i<52; i++)
		cout << a[i] << " ";
	cout << endl;

	return 0;
}
