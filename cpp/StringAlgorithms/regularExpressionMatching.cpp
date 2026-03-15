/*
Given an input string s and a pattern p, implement regular expression matching with support for '.' and '*' where:
'.' Matches any single character.
'*' Matches zero or more of the preceding element.
The matching should cover the entire input string (not partial).
*/

class Solution {
public:
    bool isMatch(string s, string p) {
        int S = s.length(), P = p.length();
        vector<vector<int>> dp(S+1, vector<int>(P+1, 0));
        dp[0][0] = 1;
        for(int j=1; j<P+1; j++){
            if(p[j-1]=='*') dp[0][j] = dp[0][j-2];
        }
        for(int i=1; i<S+1; i++){
            for(int j=1; j<P+1; j++){
                if(s[i-1]==p[j-1] || p[j-1]=='.') dp[i][j] = dp[i-1][j-1];
                else if(p[j-1]=='*'){
                    if(p[j-2]==s[i-1] || p[j-2]=='.'){
                        dp[i][j] = dp[i-1][j] || dp[i][j-2];
                    }
                    else dp[i][j] = dp[i][j-2];
                }
            }
        }
        return dp[S][P];
    }
};

/*

This code solves the **Regular Expression Matching** problem using **Dynamic Programming (DP)**. Instead of using a slow recursive approach with backtracking, it builds a 2D table to store results of subproblems.

### The Core Logic: The DP Table

We create a 2D grid `dp[i][j]` where `i` represents the first $i$ characters of string `s` and `j` represents the first $j$ characters of pattern `p`. The value is `1` (true) if they match, and `0` (false) otherwise.

---

### Step-by-Step Breakdown

#### 1. Initialization (Base Case)

* `dp[0][0] = 1`: An empty string matches an empty pattern.
* **Empty String vs Pattern:** Patterns like `a*`, `a*b*`, or `.*` can match an empty string because the `*` can represent "zero" of the preceding character.
```cpp
if(p[j-1]=='*') dp[0][j] = dp[0][j-2];

```



#### 2. Filling the Table (The Transitions)

The code iterates through the string and pattern. For each cell `dp[i][j]`, there are three main scenarios:

* **Scenario A: Exact Match or Dot**
If `s[i-1] == p[j-1]` or `p[j-1] == '.'`, then the current characters match. The result depends on whether the *previous* parts matched:
`dp[i][j] = dp[i-1][j-1]`
* **Scenario B: The Wildcard `***`
This is the trickiest part. When we see a `*`, we have two choices:
1. **Treat as zero occurrences:** Ignore the `*` and its preceding character. We look back two steps in the pattern: `dp[i][j-2]`.
2. **Treat as one or more occurrences:** If the character before `*` matches the current string character (or is a `.`), we can "consume" one character from the string and stay at the current pattern position: `dp[i-1][j]`.


```cpp
if (p[j-2] == s[i-1] || p[j-2] == '.')
    dp[i][j] = dp[i-1][j] || dp[i][j-2]; // Match 1+ or Match 0
else
    dp[i][j] = dp[i][j-2]; // Must match 0

```



---

### Complexity Analysis

#### Time Complexity: $O(S \times P)$

* We have two nested loops: one running $S$ times (length of string) and one running $P$ times (length of pattern).
* Inside the loops, every operation (lookups, logic) is $O(1)$.
* Total time: **$O(S \times P)$**.

#### Space Complexity: $O(S \times P)$

* We store a 2D `vector` of size $(S+1) \times (P+1)$.
* Total space: **$O(S \times P)$**.
* *Note:* This could be optimized to $O(P)$ since we only ever look at the current row and the previous row.

---

### Example Trace

**s:** `"aa"`, **p:** `"a*"`

1. `dp[0][0] = 1`
2. `dp[0][2]` becomes `1` (because `a*` matches empty).
3. When `i=1, j=2`: `p[j-1]` is `*`. Since `p[j-2]` ('a') matches `s[i-1]` ('a'), `dp[1][2] = dp[0][2] || dp[1][0]`, which is `1`.
4. The final answer `dp[2][2]` will be `1`.

**Would you like me to show you the $O(P)$ space optimization for this specific code?**

*/