Approaching dynamic programming (DP) can feel like learning a new language. Most problems follow a natural progression from a "brute force" recursive thought process to a highly optimized iterative table.

Here is the step-by-step roadmap to mastering these three approaches.

---

## 1. The Recursive Approach (The "Decision Tree")

The goal here is to break the problem into smaller versions of itself.

* **The Mindset:** "To solve for $N$, what do I need to know about $N-1$ or $N-2$?"
* **Key Components:**
1. **Base Case:** The simplest possible version of the problem where you already know the answer (e.g., $N=0$ or $N=1$).
2. **Recursive Relation:** The logic that connects the current state to the next smaller state.


* **The Downside:** Without optimization, this often results in an exponential time complexity $O(2^N)$ because you recalculate the same "sub-problems" thousands of times.

---

## 2. Top-Down DP (Memoization)

This is simply the recursive approach with a "memory." Before you calculate a value, you check a table to see if you've already done the work.

* **The Approach:**
1. Create a global array or hash map (often called `memo` or `dp`).
2. Initialize the table with a dummy value (like -1).
3. In your recursive function, **check before you calculate:** `if (memo[n] != -1) return memo[n];`
4. **Store after you calculate:** `return memo[n] = recursive_call(n-1) + ...;`


* **Best For:** Problems where you don't actually need to visit every possible state to find the answer. It only computes what it needs.

---

## 3. Bottom-Up DP (Tabulation)

This is the "iterative" approach. Instead of starting at $N$ and going down, you start at the base cases and build your way up to $N$.

* **The Approach:**
1. Create a table (array) of size $N+1$.
2. **Seed the Base Cases:** Manually set `dp[0]` and `dp[1]`.
3. **Iterate:** Use a `for` loop from 2 to $N$.
4. **Fill the Table:** Each cell `dp[i]` is calculated using previously filled cells.


* **Best For:** Performance. It avoids the overhead of the "function call stack" (preventing Stack Overflow errors) and is often easier to optimize for space.

---

## Example: The Fibonacci Sequence

Let's see all three side-by-side for finding the $n^{th}$ Fibonacci number.

| Approach | Logic Snippet | Complexity |
| --- | --- | --- |
| **Recursive** | `f(n) { return f(n-1) + f(n-2); }` | Time: $O(2^n)$ / Space: $O(n)$ |
| **Top-Down** | `if (dp[n] != -1) return dp[n];` | Time: $O(n)$ / Space: $O(n)$ |
| **Bottom-Up** | `for(i=2...n) { dp[i] = dp[i-1] + dp[i-2]; }` | Time: $O(n)$ / Space: $O(n)$ |

---

## How to choose which one to use?

1. **Start with Recursion:** If you can't define the relationship between states, you can't do DP. Draw a tree on paper first.
2. **Add Memoization:** If you see the same branches appearing multiple times in your tree, plug in a hash map. This is usually the fastest way to get a "passing" solution in an interview.
3. **Convert to Tabulation:** If you need to eke out more performance or if the recursion depth is too high (causing a crash), convert the logic into a `for` loop.

Would you like to try applying these three steps to a specific problem, like the **Climbing Stairs** or **Coin Change** problem?