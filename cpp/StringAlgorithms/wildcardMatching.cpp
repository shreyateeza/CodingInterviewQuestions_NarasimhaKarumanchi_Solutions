/*
Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*' where:
'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).
The matching should cover the entire input string (not partial).
*/

class Solution {
public:
    bool isMatch(string s, string p) {
        int N = p.length(), M = s.length();
        vector<bool> cur(M+1, false), prev(M+1, false);
        prev[0] = true;
        for(int i=1; i<=N; i++){
            if(p[i-1]=='*') cur[0] = prev[0];
            else cur[0] = false;
            for(int j=1; j<=M; j++){
                if(p[i-1]==s[j-1] || p[i-1]=='?'){
                    cur[j] = prev[j-1];
                }
                else if(p[i-1]=='*'){
                    cur[j] = prev[j] || cur[j-1];
                }
                else cur[j] = false;
            }
            prev = cur;
        }
        return prev[M];
    }
};

/*

This code solves the **Wildcard Matching** problem using **Dynamic Programming with Space Optimization**.

Unlike Regular Expression matching (where `*` modifies the *previous* character), in Wildcard matching, `*` is an independent entity that can match any sequence of characters.

---

### 1. How the Algorithm Works

The code uses a DP approach where `dp[i][j]` represents whether the first `i` characters of the pattern match the first `j` characters of the string. However, instead of a full 2D table, it uses two 1D vectors (`prev` and `cur`) to save memory.

#### The Base Case

* `prev[0] = true`: An empty pattern matches an empty string.
* `cur[0] = prev[0]`: If the pattern character is `*`, it can match an empty string if the previous pattern also matched an empty string.

#### The Transitions (The Logic)

For each character in the pattern (`p[i-1]`) and string (`s[j-1]`):

1. **Direct Match or `?**`:
If characters match or the pattern has `?`, the result depends on the diagonal previous state (did the strings match before these two characters?).
`cur[j] = prev[j-1]`
2. **The Wildcard `***`:
This is the "power" character. It has two choices:
* **Match Empty Sequence**: It ignores itself. Look at `prev[j]` (same string position, previous pattern).
* **Match One or More Characters**: It consumes a character from the string. Look at `cur[j-1]` (previous string position, same pattern).
`cur[j] = prev[j] || cur[j-1]`



---

### 2. Time and Space Complexity

#### Time Complexity: $O(N \times M)$

* There are two nested loops. The outer loop runs $N$ times (length of pattern), and the inner loop runs $M$ times (length of string).
* Every operation inside the inner loop is $O(1)$.
* Total complexity: **$O(N \times M)$**.

#### Space Complexity: $O(M)$

* The original DP approach uses $O(N \times M)$ space for a 2D grid.
* This specific implementation uses only two vectors (`prev` and `cur`), each of size $M+1$.
* Therefore, the space complexity is reduced to **$O(M)$**.

---

### 3. Example Trace

**s:** `"adce"`, **p:** `"*a*e"`

1. **Initial:** `prev = [T, F, F, F, F]`
2. **Pattern `***`: `cur[0]` stays `T`. `cur` fills with `T` because `cur[j-1]` propagates the truth. `prev = [T, T, T, T, T]`
3. **Pattern `a**`: Only `cur[1]` becomes `T` because `prev[0]` was `T` and `s[0]` is 'a'. `prev = [F, T, F, F, F]`
4. **Pattern `***`: `cur[0]` becomes `F`. `cur[1]` becomes `T` (from `prev[1]`). `cur[2..4]` become `T` because the truth propagates. `prev = [F, T, T, T, T]`
5. **Pattern `e**`: Only `cur[4]` becomes `T` because `prev[3]` was `T` and `s[3]` is 'e'.

**Final Result:** `prev[4]` is `true`.

> **Note:** The line `prev = cur;` at the end of the loop is what allows the "sliding" window effect, moving the "current" row results to the "previous" row for the next pattern character.

Would you like to see the **Greedy** version of this algorithm? It is significantly faster ($O(N+M)$ average) and uses $O(1)$ space.

*/