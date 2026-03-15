#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

void replaceSpacesInPlace(string& str, int actualLength) {
    int spaceCount = 0;
    for (int i = 0; i < actualLength; i++) {
        if (str[i] == ' ') {
            spaceCount++;
        }
    }

    int newLength = actualLength + spaceCount * 2;
    // Resize the string to the new length
    str.resize(newLength); //

    int originalIndex = actualLength - 1;
    int newIndex = newLength - 1;

    while (originalIndex >= 0) {
        if (str[originalIndex] == ' ') {
            str[newIndex] = '0';
            str[newIndex - 1] = '2';
            str[newIndex - 2] = '%';
            newIndex -= 3;
        } else {
            str[newIndex] = str[originalIndex];
            newIndex--;
        }
        originalIndex--;
    }
}

int main() {
    // Note: The input string must be a string or a large enough char array.
    // For string, resize handles memory management.
    string s = "Mr John Smith    "; // Assume original length is 13 ('M' to 'h')
    int length = 13; // The actual length of the string content

    replaceSpacesInPlace(s, length);

    cout << s << endl; // Output: Mr%20John%20Smith

    return 0;
}
