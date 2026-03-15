/* Following program is a C++ implementation of Rabin Karp
Algorithm given in the CLRS book */
#include <bits/stdc++.h>
using namespace std;

// d is the number of characters in the input alphabet
#define d 256

/* pat -> pattern
	txt -> text
	q -> A prime number
*/
void search(char pat[], char txt[], int q)
{
	int M = strlen(pat);
	int N = strlen(txt);
	int i, j;
	int p = 0; // hash value for pattern
	int t = 0; // hash value for txt
	int h = 1;

	// The value of h would be "pow(d, M-1)%q"
	for (i = 0; i < M - 1; i++)
		h = (h * d) % q;

	// Calculate the hash value of pattern and first
	// window of text
	for (i = 0; i < M; i++) {
		p = (d * p + pat[i]) % q;
		t = (d * t + txt[i]) % q;
	}

	// Slide the pattern over text one by one
	for (i = 0; i <= N - M; i++) {

		// Check the hash values of current window of text
		// and pattern. If the hash values match then only
		// check for characters one by one
		if (p == t) {
			/* Check for characters one by one */
			for (j = 0; j < M; j++) {
				if (txt[i + j] != pat[j]) {
					break;
				}
			}

			// if p == t and pat[0...M-1] = txt[i, i+1,
			// ...i+M-1]

			if (j == M)
				cout << "Pattern found at index " << i
					<< endl;
		}

		// Calculate hash value for next window of text:
		// Remove leading digit, add trailing digit
		if (i < N - M) {
			t = (d * (t - txt[i] * h) + txt[i + M]) % q;

			// We might get negative value of t, converting
			// it to positive
			if (t < 0)
				t = (t + q);
		}
	}
}

/* Driver code */
int main()
{
	char txt[] = "GEEKS FOR GEEKS";
	char pat[] = "GEEK";

	// we mod to avoid overflowing of value but we should
	// take as big q as possible to avoid the collison
	int q = INT_MAX;

	// Function Call
	search(pat, txt, q);
	return 0;
}


// Code 2

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// D is the number of characters in the input alphabet (e.g., 256 for ASCII)
#define D 256

/**
 * @param pat  Pattern to search for
 * @param txt  Text to search in
 * @param q    A prime number for modulo operations (prevents overflow)
 */
void rabinKarpSearch(string pat, string txt, int q) {
    int m = pat.length();
    int n = txt.length();
    int i, j;
    int p = 0; // hash value for pattern
    int t = 0; // hash value for txt window
    int h = 1;

    // The value of h would be "pow(D, m-1) % q"
    for (i = 0; i < m - 1; i++)
        h = (h * D) % q;

    // Calculate the initial hash value of pattern and first window of text
    for (i = 0; i < m; i++) {
        p = (D * p + pat[i]) % q;
        t = (D * t + txt[i]) % q;
    }

    // Slide the pattern over text one by one
    for (i = 0; i <= n - m; i++) {
        // If the hash values match, check characters one by one
        if (p == t) {
            bool match = true;
            for (j = 0; j < m; j++) {
                if (txt[i + j] != pat[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                cout << "Pattern found at index " << i << endl;
            }
        }

        // Calculate hash value for next window of text: 
        // Remove leading digit, add trailing digit
        if (i < n - m) {
            t = (D * (t - txt[i] * h) + txt[i + m]) % q;

            // We might get a negative value of t, converting it to positive
            if (t < 0) t = (t + q);
        }
    }
}

int main() {
    string txt = "GEEKS FOR GEEKS";
    string pat = "GEEK";
    
    // A prime number for modulo
    int q = 101; 

    rabinKarpSearch(pat, txt, q);
    return 0;
}


/*

The two code snippets you've provided implement the **Rabin-Karp Algorithm**, a string-searching algorithm that uses **hashing** to find a pattern within a text. While Code 1 uses C-style strings (`char[]`) and Code 2 uses C++ `std::string`, the underlying logic is identical.

Here is a breakdown of how the algorithm works and what the specific lines of code are doing.

---

## 1. The Core Idea: Rolling Hash

Instead of checking every character at every possible position (which is slow), Rabin-Karp treats a string as a number.

Imagine the alphabet is just digits 0-9. The string "123" becomes the number 123. If we want to check if "123" exists in "41235", we compare the number 123 to "412", then "123", then "235".

### Key Variables

* **`d` or `D` (256):** The base of our number system. Since we use ASCII characters, we treat each character as a digit in base-256.
* **`q`:** A prime number used for the modulo operation. This prevents the hash numbers from becoming so large that they overflow the computer's memory.
* **`h`:** This represents $d^{m-1} \pmod{q}$. It is used to "remove" the leading digit when we slide the window.

---

## 2. Step-by-Step Logic

### Step A: Pre-calculation

```cpp
for (i = 0; i < M - 1; i++)
    h = (h * d) % q;

```

This calculates $h = d^{M-1} \pmod{q}$. If our pattern is 4 characters long, and we are in base 10, $h$ would be $10^3 = 1000$. This helps us isolate the value of the first character in a window so we can subtract it later.

### Step B: Initial Hashing

```cpp
for (i = 0; i < M; i++) {
    p = (d * p + pat[i]) % q;
    t = (d * t + txt[i]) % q;
}

```

This converts the pattern and the first "window" of the text into numerical hash values. It uses Horner's method to calculate the polynomial:


$$Hash = (c_0 \cdot d^{m-1} + c_1 \cdot d^{m-2} + \dots + c_{m-1} \cdot d^0) \pmod{q}$$

### Step C: The Sliding Window

```cpp
if (p == t) {
    // Check characters one by one to handle "Spurious Hits"
}

```

If the hash values match, it's a "hit." However, because of the modulo operator, two different strings can sometimes have the same hash (a **collision**). The code performs a manual character-by-character check only when the hashes match to ensure it's a real match.

### Step D: The "Rolling" Part

```cpp
t = (d * (t - txt[i] * h) + txt[i + M]) % q;

```

This is the magic of the algorithm. Instead of re-calculating the hash from scratch for the next window, it:

1. **Subtracts** the leading character: `(t - txt[i] * h)`
2. **Shifts** the remaining digits to the left (multiply by `d`).
3. **Adds** the new trailing character: `+ txt[i + M]`

This allows the window to move in $O(1)$ constant time.

---

## 3. Differences Between Code 1 and Code 2

| Feature | Code 1 | Code 2 |
| --- | --- | --- |
| **String Type** | C-style `char[]` | C++ `std::string` |
| **Headers** | `<bits/stdc++.h>` (Non-standard) | `<iostream>`, `<string>` (Standard) |
| **Prime `q**` | `INT_MAX` (Very large) | `101` (Small, for demonstration) |
| **Safety** | Uses `strlen()` (Potential overhead) | Uses `.length()` (Efficient) |

**Note on Code 1's `q`:** Using `INT_MAX` as `q` is risky because the calculation `(d * (t - txt[i] * h) + txt[i + M])` will almost certainly overflow an `int` before the modulo is applied. Code 2's use of `101` is safer for 32-bit integers, though it leads to more hash collisions.

---

## Summary of Complexity

* **Average/Best Case:** $O(n + m)$, where $n$ is text length and $m$ is pattern length.
* **Worst Case:** $O(n \cdot m)$ (occurs if the hash function produces many collisions).

Would you like me to walk through a manual example of how the hash changes using a small prime number like 13?

*/