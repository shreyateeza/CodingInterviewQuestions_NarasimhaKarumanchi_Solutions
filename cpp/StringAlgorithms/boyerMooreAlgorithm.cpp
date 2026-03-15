/* C++ Program for Bad Character Heuristic of Boyer Moore String Matching Algorithm */
#include <bits/stdc++.h>
using namespace std;
#define NO_OF_CHARS 256

// The preprocessing function for Boyer Moore's bad character heuristic
void badCharHeuristic(string str, int size,	int badchar[NO_OF_CHARS]){
	int i;
	// Initialize all occurrences as -1
	for (i = 0; i < NO_OF_CHARS; i++)
		badchar[i] = -1;

	// Fill the actual value of last occurrence of a character
	for (i = 0; i < size; i++)
		badchar[(int)str[i]] = i;
}

/* A pattern searching function that uses Bad Character Heuristic of Boyer Moore Algorithm */
void search(string txt, string pat){
	int m = pat.size();
	int n = txt.size();

	int badchar[NO_OF_CHARS];

	/* Fill the bad character array by calling the preprocessing function badCharHeuristic() for given pattern */
	badCharHeuristic(pat, m, badchar);

	int s = 0; // s is shift of the pattern with respect to text
	while (s <= (n - m)) {
		int j = m - 1;

		/* Keep reducing index j of pattern while characters of pattern and text are matching at this shift s */
		while (j >= 0 && pat[j] == txt[s + j])
			j--;

		/* If the pattern is present at current shift, then index j will become -1 after the above loop */
		if (j < 0) {
			cout<<"pattern occurs at shift = "<<s<< endl;

			/* Shift the pattern so that the next
			character in text aligns with the last
			occurrence of it in pattern.
			The condition s+m < n is necessary for
			the case when pattern occurs at the end
			of text */
			s += (s + m < n) ? m - badchar[txt[s + m]] : 1;
		}

		else
			/* Shift the pattern so that the bad character
			in text aligns with the last occurrence of
			it in pattern. The max function is used to
			make sure that we get a positive shift.
			We may get a negative shift if the last
			occurrence of bad character in pattern
			is on the right side of the current
			character. */
			s += max(1, j - badchar[txt[s + j]]);
	}
}

/* Driver code */
int main(){
	string txt = "ABAAABCD";
	string pat = "ABC";
	search(txt, pat);
	return 0;
}

/*
This code implements the **Bad Character Heuristic**, which is one of the two main components of the **Boyer-Moore** string-searching algorithm. Unlike simpler algorithms that slide one character at a time, Boyer-Moore skips large sections of the text by analyzing the pattern from **right to left**.

---

## 1. How the Logic Works

### Step A: Preprocessing (`badCharHeuristic`)

The goal is to create a lookup table (`badchar`) that stores the **last occurrence** of every possible character (0–255 in ASCII) within the pattern.

* If a character is not in the pattern, it stays as `-1`.
* If it is in the pattern, it stores the index. For "ABC", `badchar['A'] = 0`, `badchar['B'] = 1`, and `badchar['C'] = 2`.

### Step B: The Search Logic

1. **Right-to-Left Comparison:** It compares the pattern against the text starting from the last character of the pattern ($j = m-1$).
2. **Mismatches:** If a mismatch occurs at text character `txt[s + j]`:
* **Case 1:** The mismatched character exists in the pattern. We shift the pattern so that the last occurrence of that character in the pattern aligns with the character in the text.
* **Case 2:** The mismatched character does **not** exist in the pattern. We can safely shift the pattern past that character entirely.


3. **The "Max" Rule:** The shift is calculated as $j - \text{badchar}[\text{txt}[s + j]]$. We use `max(1, shift)` because if the last occurrence of the "bad character" is to the right of the current index $j$, the shift could be negative. We always want to move forward.

---

## 2. Complexity Analysis

Let $n$ be the length of the text and $m$ be the length of the pattern. Let $|\Sigma|$ be the size of the alphabet (in this case, 256).

### Time Complexity

* **Preprocessing:** $O(m + |\Sigma|)$. We loop through the alphabet to initialize the array and then loop through the pattern once.
* **Searching:**
* **Best Case:** $O(n/m)$. This happens when the characters are totally different, allowing the algorithm to skip $m$ characters at every step.
* **Worst Case:** $O(n \cdot m)$. This occurs with highly repetitive text and patterns (e.g., Text: "AAAAAAAAAAAAAAAA", Pattern: "BAAA"). However, in practice, Boyer-Moore is significantly faster than $O(n)$.



### Space Complexity

* **Auxiliary Space:** $O(|\Sigma|)$.
* The algorithm uses an integer array of size 256 (the `badchar` array) to store the last positions of characters. This is constant space relative to the input strings, but technically scales with the alphabet size.



---

## 3. Summary Table

| Feature | Complexity |
| --- | --- |
| **Best Time** | $O(n/m)$ |
| **Worst Time** | $O(n \cdot m)$ |
| **Space** | $O( |
| **Comparison Direction** | Right-to-Left |

Would you like me to walk through a manual trace of how "ABC" moves across "ABAAABCD" step-by-step?
YES

Let's trace the search of the pattern **"ABC"** ($m=3$) in the text **"ABAAABCD"** ($n=8$) step-by-step.

### Preprocessing (Bad Character Table)

First, we build our `badchar` array for the pattern "ABC":

* `badchar['A'] = 0`
* `badchar['B'] = 1`
* `badchar['C'] = 2`
* All other characters = `-1`

---

### Step-by-Step Trace

**Shift 0:**

```text
Text:    A  B  A  A  A  B  C  D
Pattern: A  B  C
Index:   0  1  2

```

1. Compare from right to left: `txt[2]` is 'A', `pat[2]` is 'C'. **Mismatch!**
2. `badchar['A']` is **0**.
3. Shift calculation: $j - \text{badchar}[\text{'A'}] = 2 - 0 = 2$.
4. New shift $s = 0 + 2 = 2$.

**Shift 2:**

```text
Text:    A  B  A  A  A  B  C  D
Pattern:       A  B  C
Index:         2  3  4

```

1. Compare from right to left: `txt[4]` is 'A', `pat[2]` is 'C'. **Mismatch!**
2. `badchar['A']` is **0**.
3. Shift calculation: $j - \text{badchar}[\text{'A'}] = 2 - 0 = 2$.
4. New shift $s = 2 + 2 = 4$.

**Shift 4:**

```text
Text:    A  B  A  A  A  B  C  D
Pattern:             A  B  C
Index:               4  5  6

```

1. Compare from right to left:
* `txt[6]` ('C') == `pat[2]` ('C') — **Match**
* `txt[5]` ('B') == `pat[1]` ('B') — **Match**
* `txt[4]` ('A') == `pat[0]` ('A') — **Match**


2. All characters match! **Pattern found at shift 4.**
3. Next shift calculation (to find more occurrences):
* `txt[s + m]` is `txt[4 + 3]` = `txt[7]` ('D').
* `badchar['D']` is **-1**.
* Shift: $m - (-1) = 3 - (-1) = 4$.


4. $s = 4 + 4 = 8$. Since $8 > (n - m)$, the loop terminates.

---

### Key Takeaway

Notice how we only performed **3 shifts** to search an 8-character string. A naive algorithm would have checked every single index (0, 1, 2, 3, 4, 5). By looking at the "bad character" and knowing where it exists in the pattern, we safely skipped unnecessary comparisons.

Would you like to see how this code would handle a case where the "bad character" exists to the *right* of the current mismatch (the negative shift case)?

Algorithm,Best Case,Worst Case,Main Idea
Naive,O(n),O(n⋅m),Check every single position.
KMP,O(n),O(n),Use a prefix table to never look back.
Boyer-Moore,O(n/m),O(n⋅m),Skip sections using character logic.


While the **Bad Character Heuristic** looks at the character that caused the mismatch, the **Good Suffix Heuristic** looks at the part of the pattern that *already matched* (the "suffix") and tries to find where else that same sequence appears in the pattern.

It’s essentially saying: *"We just matched 'ABC' at the end of our pattern. Is there another 'ABC' earlier in the pattern we can align this with?"*

---

## 1. The Two Main Cases

The Good Suffix Heuristic handles two specific scenarios when a mismatch occurs after some characters have already matched:

### Case 1: Matching Suffix Exists Elsewhere

If the suffix that matched (let's call it $t$) exists somewhere else in the pattern (preceded by a different character), we shift the pattern to align that earlier occurrence with the text.

* **Pattern:** `ABBABAB`
* **Text Match:** Imagine we matched the last `BAB`.
* **Logic:** We look for another `BAB` earlier in the pattern. There is one starting at index 2. We shift the pattern so that the earlier `BAB` aligns with the text where the last one was.

### Case 2: Only a Part of the Suffix is a Prefix

If the entire suffix doesn't exist elsewhere, we look for the **longest proper suffix** of our match that is also a **prefix** of the entire pattern.

* **Pattern:** `ABCCAB`
* **Text Match:** Imagine we matched `CAB` at the end, but the character before it mismatched.
* **Logic:** `CAB` doesn't exist elsewhere. However, the `AB` at the end of the suffix is also the `AB` at the start of the pattern. We shift the pattern so the start (`AB`) aligns with the end of where the match occurred in the text.

---

## 2. Why use both?

The full Boyer-Moore algorithm calculates the shift suggested by **both** the Bad Character and the Good Suffix heuristics and chooses the **larger** of the two.

| Heuristic | Best For... |
| --- | --- |
| **Bad Character** | Large alphabets (like Unicode) where mismatches happen often and provide big jumps. |
| **Good Suffix** | Small alphabets (like DNA sequences: A, T, C, G) where many characters repeat and the "Bad Character" rule often only shifts by 1. |

---

## 3. Complexity Impact

Adding the Good Suffix Heuristic is what guarantees the Boyer-Moore algorithm a **linear worst-case time complexity** of $O(n)$ for searching, whereas using only the Bad Character Heuristic can technically drop to $O(n \cdot m)$ in certain repetitive cases.

### Summary Table

| Step | Action |
| --- | --- |
| **Preprocessing** | $O(m)$ to build the suffix shift table. |
| **Search** | $O(n/m)$ best case; $O(n)$ worst case. |
| **Space** | $O(m)$ extra space for the suffix table. |

Would you like to see a code implementation of how the Good Suffix table is precomputed, or perhaps a comparison of Boyer-Moore vs. KMP?

*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Preprocessing for Case 2: Finding the strongest prefix that is also a suffix
void preprocess_strong_suffix(int *shift, int *bpos, string pat, int m) {
    int i = m, j = m + 1;
    bpos[i] = j;

    while (i > 0) {
        // If character at i-1 is not equal to character at j-1, 
        // continue finding next border
        while (j <= m && pat[i - 1] != pat[j - 1]) {
            // The character preceded by the current suffix is different,
            // so we calculate the shift for this suffix
            if (shift[j] == 0)
                shift[j] = j - i;

            // Update j to the next border
            j = bpos[j];
        }
        i--;
        j--;
        bpos[i] = j;
    }
}

// Preprocessing for Case 1: Matching suffix exists elsewhere or partial match
void preprocess_case2(int *shift, int *bpos, string pat, int m) {
    int i, j;
    j = bpos[0];
    for (i = 0; i <= m; i++) {
        // If the shift is not yet set (Case 1 didn't apply)
        if (shift[i] == 0)
            shift[i] = j;

        // If the suffix becomes shorter than the border, 
        // use the next border
        if (i == j)
            j = bpos[j];
    }
}

void search(string text, string pat) {
    int s = 0, j;
    int m = pat.length();
    int n = text.length();

    int bpos[m + 1], shift[m + 1];

    // Initialize shift array with 0
    for (int i = 0; i <= m; i++) shift[i] = 0;

    // Do preprocessing
    preprocess_strong_suffix(shift, bpos, pat, m);
    preprocess_case2(shift, bpos, pat, m);

    while (s <= n - m) {
        j = m - 1;

        // Keep reducing index j of pattern while characters match
        while (j >= 0 && pat[j] == text[s + j])
            j--;

        if (j < 0) {
            cout << "Pattern occurs at shift = " << s << endl;
            s += shift[0];
        } else {
            // Shift pattern by the value determined by the Good Suffix table
            s += shift[j + 1];
        }
    }
}

int main() {
    string text = "ABBABABACBA";
    string pat = "BAB";
    search(text, pat);
    return 0;
} 

/*
To truly understand why the full Boyer-Moore algorithm is so powerful, you have to see how these two heuristics play "Good Cop, Bad Cop" with the text. They tackle the problem from two different angles: one looks at the **mismatch**, and the other looks at the **match**.

---

## 1. Core Differences

| Feature | Bad Character Heuristic | Good Suffix Heuristic |
| --- | --- | --- |
| **Focus** | The character in the **text** that caused the mismatch. | The substring in the **pattern** that already matched. |
| **Logic** | "Where else does this 'bad' character appear in my pattern?" | "Where else does this 'good' suffix appear in my pattern?" |
| **Alignment** | Moves the pattern to align the text character with its last occurrence in the pattern. | Moves the pattern to align a repeating part of the pattern with the text. |
| **Best For** | Large alphabets (ASCII/Unicode) where unique characters are common. | Small alphabets (DNA: A, C, G, T) where characters repeat constantly. |
| **Worst Case** | Can be $O(n \cdot m)$ on its own (e.g., Text: `AAAAA`, Pattern: `BAAA`). | Guarantees $O(n)$ linear time in the worst case. |

---

## 2. Visual Comparison

### The Bad Character Rule

Imagine you are looking for **"ORANGE"** and you match the "E" and "G", but then hit a **"Z"** in the text.

* **Observation:** "Z" isn't in "ORANGE" at all.
* **Action:** You can jump the *entire* pattern past that "Z". It’s a massive skip.

### The Good Suffix Rule

Imagine you are looking for **"ANANA"** (like in BANANA). You match the final **"ANA"**, but the character before it mismatches.

* **Observation:** "ANA" is also at the beginning of the pattern.
* **Action:** You shift the pattern so that the prefix "ANA" aligns with where the suffix "ANA" just was in the text.

---

## 3. How they work together

In a standard implementation, the algorithm calculates the shift for **both** and takes the maximum:


$$\text{Shift} = \max(\text{Bad Character Shift}, \text{Good Suffix Shift})$$

### Why use both?

1. **Redundancy:** If the Bad Character is already part of the suffix you just matched, the Bad Character rule might suggest a "negative shift" (moving backward). The Good Suffix rule acts as a safety net to ensure you always move forward efficiently.
2. **Efficiency:** In DNA sequencing (A, T, C, G), the Bad Character rule is often weak because "A" is everywhere. However, the Good Suffix rule excels here because it finds repeating patterns in the sequence.

---

## 4. Summary Table

| Metric | Bad Character | Good Suffix |
| --- | --- | --- |
| **Preprocessing Complexity** | $O(m + | \Sigma |
| **Space Complexity** | $O( | \Sigma |
| **Skip Potential** | High (up to $m$) | High (up to $m$) |
| **Reliability** | Can fail to skip on small alphabets | Always provides a valid forward skip |

**Would you like me to provide a complete C++ implementation that combines both of these into the full Boyer-Moore algorithm?**
*/

/*
This is the complete, high-performance **Boyer-Moore String Matching Algorithm**. It combines both the **Bad Character Heuristic** and the **Good Suffix Heuristic** to ensure the maximum possible shift at every mismatch.
*/

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define NO_OF_CHARS 256

// --- BAD CHARACTER HEURISTIC PREPROCESSING ---
void badCharHeuristic(string str, int size, int badchar[NO_OF_CHARS]) {
    for (int i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;
    for (int i = 0; i < size; i++)
        badchar[(int)str[i]] = i;
}

// --- GOOD SUFFIX HEURISTIC PREPROCESSING ---
void preprocess_strong_suffix(int *shift, int *bpos, string pat, int m) {
    int i = m, j = m + 1;
    bpos[i] = j;
    while (i > 0) {
        while (j <= m && pat[i - 1] != pat[j - 1]) {
            if (shift[j] == 0)
                shift[j] = j - i;
            j = bpos[j];
        }
        i--; j--;
        bpos[i] = j;
    }
}

void preprocess_case2(int *shift, int *bpos, string pat, int m) {
    int j = bpos[0];
    for (int i = 0; i <= m; i++) {
        if (shift[i] == 0)
            shift[i] = j;
        if (i == j)
            j = bpos[j];
    }
}

// --- FULL BOYER-MOORE SEARCH ---
void search(string txt, string pat) {
    int m = pat.size();
    int n = txt.size();

    int badchar[NO_OF_CHARS];
    badCharHeuristic(pat, m, badchar);

    int shift[m + 1], bpos[m + 1];
    for (int i = 0; i <= m; i++) shift[i] = 0;

    preprocess_strong_suffix(shift, bpos, pat, m);
    preprocess_case2(shift, bpos, pat, m);

    int s = 0; // s is the shift of the pattern with respect to text
    while (s <= (n - m)) {
        int j = m - 1;

        // Keep reducing index j of pattern while characters match
        while (j >= 0 && pat[j] == txt[s + j])
            j--;

        if (j < 0) {
            cout << "Pattern occurs at shift = " << s << endl;
            // When pattern is found, use the shift suggested by Good Suffix
            s += shift[0];
        } else {
            /* Maximize the shift using both heuristics */
            int bc_shift = j - badchar[txt[s + j]];
            int gs_shift = shift[j + 1];
            s += max(gs_shift, bc_shift);
        }
    }
}

int main() {
    string txt = "ABAAABCDABC";
    string pat = "ABC";
    search(txt, pat);
    return 0;
}

```

---

## Why this is the "Gold Standard"

The beauty of this combined approach is that it covers the weaknesses of each individual rule:

1. **Efficiency:** On large alphabets, the `bc_shift` often provides a massive jump (up to $m$).
2. **Reliability:** On repetitive patterns or small alphabets (like binary or DNA), the `gs_shift` ensures we don't just crawl forward by 1 character.
3. **Direction:** Both rules agree on a **Right-to-Left** scan, which is counter-intuitive but mathematically superior for skipping text.

---

### Performance Summary

* **Worst-case time:** $O(n)$ (guaranteed by the Good Suffix rule).
* **Average/Best-case time:** $O(n/m)$ (the pattern "hops" over the text).
* **Space:** $O(m + |\Sigma|)$.

### A Quick Tip

If you are searching for very short patterns (e.g., 2 or 3 characters), the overhead of building these tables might actually make Boyer-Moore slower than a simple `std::string::find`. It truly shines when the pattern is long!

**Would you like me to show you how to adapt this to search for multiple patterns at once, or perhaps compare it to the Knuth-Morris-Pratt (KMP) algorithm?**
rf
*/