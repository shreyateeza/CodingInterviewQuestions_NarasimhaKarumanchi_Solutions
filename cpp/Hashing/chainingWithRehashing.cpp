#include <bits/stdc++.h>
using namespace std;

struct Hash {
    int BUCKET; // No. of buckets
    int numOfElements; // To track the number of elements

    // Vector of vectors to store the chains
    vector<vector<int>> table;

    // Inserts a key into hash table
    void insertItem(int key) {
      
         // If load factor exceeds 0.5, rehash
        while (getLoadFactor() > 0.5) {
            rehashing();
        }
        int index = hashFunction(key);
        table[index].push_back(key);
        numOfElements++;
    }

    // Deletes a key from hash table
    void deleteItem(int key);

    // Hash function to map values to key
    int hashFunction(int x) {
        return (x % BUCKET);
    }

    // Display the hash table
    void displayHash();

    // Constructor to initialize bucket count and table
    Hash(int b) {
        this->BUCKET = b;
        this->numOfElements = 0;
        table.resize(BUCKET); 
    }

    // Function to calculate the current load factor
    float getLoadFactor() {
        return (float)numOfElements / BUCKET;
    }

    // Rehashing function to double the capacity and re-insert elements
    void rehashing() {
        int oldBucket = BUCKET;
        BUCKET = 2 * BUCKET; // Double the number of buckets
        vector<vector<int>> oldTable = table; // Store current table

        table.clear();
        table.resize(BUCKET); // Resize the new table with double capacity
        numOfElements = 0; // Reset the element count

        // Re-insert old values into the new table
        for (int i = 0; i < oldBucket; i++) {
            for (int key : oldTable[i]) {
                insertItem(key); // Insert keys into the new table
            }
        }
    }
};

// Function to delete a key from the hash table
void Hash::deleteItem(int key) {
    int index = hashFunction(key);

    // Find and remove the key from the table[index] vector
    auto it = find(table[index].begin(), table[index].end(), key);
    if (it != table[index].end()) {
        table[index].erase(it); // Erase the key if found
        numOfElements--;
    }
}

// Function to display the hash table
void Hash::displayHash() {
    for (int i = 0; i < BUCKET; i++) {
        cout << i;
        for (int x : table[i]) {
            cout << " --> " << x;
        }
        cout << endl;
    }
}

// Driver program
int main() {
    // Vector that contains keys to be mapped
    vector<int> a = {15, 11, 27, 8, 12};

    // Insert the keys into the hash table
    Hash h(7); // 7 is the number of buckets in the hash table
    for (int key : a)
        h.insertItem(key);

    // Delete 12 from the hash table
    h.deleteItem(12);

    // Display the hash table
    h.displayHash();

    // Insert more items to trigger rehashing
    h.insertItem(33);
    h.insertItem(45);
    h.insertItem(19);

    // Display the hash table after rehashing
    cout << "\nAfter rehashing:\n";
    h.displayHash();

    return 0;
}