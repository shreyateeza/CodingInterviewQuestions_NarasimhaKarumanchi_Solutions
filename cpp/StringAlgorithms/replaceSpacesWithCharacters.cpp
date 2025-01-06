#include <iostream>
#include <string>

using namespace std;

void replaceSpaces(char* str, int length) {
  int spaceCount = 0; 
  for (int i = 0; i < length; i++) {
    if (str[i] == ' ') {
      spaceCount++;
    }
  }

  int newLength = length + spaceCount * 2; 
  str[newLength] = '\0'; 

  for (int i = length - 1; i >= 0; i--) {
    if (str[i] == ' ') {
      str[newLength - 1] = '0';
      str[newLength - 2] = '2';
      str[newLength - 3] = '%';
      newLength -= 3;
    } else {
      str[newLength - 1] = str[i];
      newLength--;
    }
  }
}

int main() {
  char str[] = "Mr John Smith okay  okay    "; 
  int length = 24; // Actual length of the string without extra spaces

  replaceSpaces(str, length);

  cout << str << endl; 
  return 0;
}

// Answer: Mr%20John%20Smith%20okay%20%20okay