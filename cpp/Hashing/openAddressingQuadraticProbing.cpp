// C++ implementation of the Quadratic Probing
#include <bits/stdc++.h>
using namespace std;

// Function to print an array
void printArray(int arr[], int n)
{
    // Iterating and printing the array
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
}

// Function to implement the quadratic probing
void hashing(int table[], int tsize, int arr[], int n)
{
    // Iterating through the array
    for (int i = 0; i < n; i++) {
      
        // Computing the hash value
        int hv = arr[i] % tsize;

        // Insert in the table if there is no collision
        if (table[hv] == -1)
            table[hv] = arr[i];
        else {
            // If there is a collision iterating through all possible quadratic values
            for (int j = 1; j <= tsize; j++) {
                // Computing the new hash value
                int t = (hv + j * j) % tsize;
                if (table[t] == -1) {
                    // Break the loop after inserting the value in the table
                    table[t] = arr[i];
                    break;
                }
            }
        }
    }
    printArray(table, tsize);
}

// Driver code
int main(){
    int arr[] = { 50, 700, 76, 85, 92, 73, 101 };
    int n = sizeof(arr)/sizeof(arr[0]);

    // Size of the hash table
    int tsize = 11;
    int hash_table[tsize];

    // Initializing the hash table
    for (int i = 0; i < tsize; i++) {
        hash_table[i] = -1;
    }

    // Function call
    hashing(hash_table, tsize, arr, n);
    return 0;
}