#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

string manacher(string s) {
    string T = "#";
    for (char c : s) {
        T += c;
        T += '#';
    }
    int n = T.length();
    vector<int> P(n, 0);
    int C = 0, R = 0;
    for (int i = 0; i < n; i++) {
        int mirr = 2 * C - i;
        if (i < R)
            P[i] = min(R - i, P[mirr]);
        // Attempt to expand palindrome centered at i
        int a = i + (1 + P[i]);
        int b = i - (1 + P[i]);
        while (a < n && b >= 0 && T[a] == T[b]) {
            P[i]++;
            a++;
            b--;
        }
        // If palindrome centered at i expands past R, adjust center and right boundary
        if (i + P[i] > R) {
            C = i;
            R = i + P[i];
        }
    }
    // Find the maximum element in P
    int maxLen = *max_element(P.begin(), P.end());
    int centerIndex = find(P.begin(), P.end(), maxLen) - P.begin();
    int start = (centerIndex - maxLen) / 2;
    return s.substr(start, maxLen);
}

int main() {
    string s = "babad";
    string longestPalindrome = manacher(s);
    cout << "Longest Palindromic Substring: " << longestPalindrome << endl;
    return 0;
}

// https://cp-algorithms.com/string/manacher.html

/*
This code implements **Manacher’s Algorithm**, which is a highly optimized way to find the **Longest Palindromic Substring** in a string. While a naive approach takes $O(n^2)$ time, Manacher's does it in **linear time** $O(n)$.

Here is the breakdown of how the code works:

---

## 1. String Transformation (Handling Even Lengths)

Palindromes can be odd-length (e.g., "aba") or even-length (e.g., "abba"). To treat them the same, the code inserts special characters (`#`) between every character.

* **Input:** `"babad"`
* **Output `T`:** `"#b#a#b#a#d#"`
This ensures that every palindrome, whether originally even or odd, now has an **odd length** and a single center character.

---

## 2. Key Variables

* **`P[i]`**: Stores the radius of the palindrome centered at index `i` in the transformed string `T`.
* **`C` (Center)**: The center of the palindrome that currently has the rightmost boundary.
* **`R` (Right Boundary)**: The rightmost edge ($R = C + P[C]$) of the palindrome centered at `C`.
* **`mirr` (Mirror)**: The mirror position of `i` with respect to center `C`. Since symmetry exists around `C`, `P[i]` can often be inherited from `P[mirr]`.

---

## 3. The Logic (The "Mirror" Trick)

The core efficiency comes from this line:
`P[i] = min(R - i, P[mirr]);`

If the current index `i` is within the boundary `R`, we don't start checking from scratch. We look at the value already calculated for its "mirror" image on the left side of the center `C`. We take the minimum of:

1. The value at the mirror position.
2. The distance to the right boundary (`R - i`), because we haven't explored what lies beyond `R` yet.

---

## 4. Expansion and Updating

* **Expansion:** After using the mirror trick, the code tries to expand the palindrome further using a `while` loop.
* **Updating Center:** If the newly expanded palindrome at `i` reaches further than the current `R`, we update `C` to `i` and `R` to the new boundary. This "sliding window" of symmetry is what keeps the algorithm linear.

---

## 5. Extracting the Result

Finally, the code finds the largest value in `P`.

* The value `maxLen` in `P` is exactly the length of the palindrome in the **original** string.
* The formula `start = (centerIndex - maxLen) / 2` converts the position in the `#`-filled string back to the original string's index.

---

## 6. Complexity Analysis

| Metric | Complexity | Explanation |
| --- | --- | --- |
| **Time Complexity** | $O(n)$ | Each character is visited a constant number of times because `R` only ever moves to the right. |
| **Space Complexity** | $O(n)$ | We create a transformed string and a vector `P` of size $2n + 1$. |

### Summary Table

| Original | Transformed | Max P[i] | Result |
| --- | --- | --- | --- |
| `aba` | `#a#b#a#` | 3 (at center `b`) | `aba` |
| `abba` | `#a#b#b#a#` | 4 (at center `#`) | `abba` |

Would you like me to trace a specific string like "racecar" step-by-step to show how `C` and `R` move?
*/