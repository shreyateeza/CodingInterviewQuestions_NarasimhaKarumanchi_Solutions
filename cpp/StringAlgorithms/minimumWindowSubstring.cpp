class Solution {
public:
    string minWindow(string s, string x) {
        unordered_map<char, int> m;
        for(int i=0; i<x.size(); i++){
            m[x[i]]++;
        }
        int length = s.size();
        int left=0, right=0, ansLeft=0, ansRight=0, counter=x.size();
        bool flag=false;
        string ans="";
        while(right < s.size()){
            char c = s[right];
            if(m.find(c) != m.end()){
                if(m[c]>0) counter--;
                m[c]--;
            }
            while(counter==0 && left<=right){
                if(right-left+1 <= length){
                    length = right-left+1;
                    flag = true;
                    ansLeft = left;
                    ansRight = right;
                }
                if(left == right) break;
                c = s[left];
                if(m.find(c) != m.end()){
                    m[c]++;
                    if(m[c]>0) counter++;
                }
                left++;
            }
            right++;
        }
        if(!flag) return ans;
        for(int i=ansLeft; i<=ansRight; i++) ans += s[i];
        return ans;
    }
};

/*

This code is a classic implementation of the **Sliding Window** algorithm. It solves the "Minimum Window Substring" problem: finding the smallest substring in `s` that contains all the characters (including duplicates) present in `x`.

Here is the breakdown of how it works.

---

### 1. The Setup (Counting Requirements)

First, the code uses a frequency map to understand what characters it needs to "collect" from string `s`.

* **`map<char, int> m`**: Stores each character in `x` and how many times it appears.
* **`counter`**: Initialized to the size of `x`. This tracks how many characters we still need to find to complete a valid window.

### 2. The Sliding Window (The Core Logic)

The algorithm uses two pointers, `left` and `right`, to create a "window" that moves across string `s`.

#### **Phase A: Expanding the Window (`right` pointer)**

The code moves the `right` pointer to the right, one character at a time.

* If the current character `s[right]` is in our target map `m`:
* If we still "need" this character (i.e., `m[c] > 0`), we decrement the `counter`.
* We decrement the count in the map (even if it goes negative, which just means we have extra copies of that character in our current window).



#### **Phase B: Shrinking the Window (`left` pointer)**

Once `counter == 0`, it means the current window contains **all** required characters. Now, the code tries to make the window as small as possible:

1. **Update the Answer**: If the current window is smaller than the previous smallest (`length`), it saves the new `ansLeft` and `ansRight`.
2. **Move `left**`: It tries to remove the character at `s[left]`.
* If the character being removed was a "required" character (making its count in the map `> 0` again), the `counter` increases, and the window is no longer valid.
* The loop then goes back to **Phase A** to find a new valid character to replace what was lost.



---

### 3. Final Result

After the loop finishes:

* If `flag` is still `false`, no valid window was found, so it returns an empty string.
* Otherwise, it builds the result string using the saved `ansLeft` and `ansRight` indices.

---

### Key Variables Summary

| Variable | Purpose |
| --- | --- |
| `m` | Frequency map of characters needed from `x`. |
| `counter` | The number of characters still missing to make the window "valid." |
| `left` / `right` | The boundaries of the current search window. |
| `ansLeft` / `ansRight` | The boundaries of the **best (smallest)** window found so far. |

### A Small Optimization Note

The code uses `std::map<char, int>`, which has $O(\log N)$ lookup time. In competitive programming, using an array of size 128 or 256 (for ASCII) or `std::unordered_map` is often preferred to achieve $O(1)$ lookup, making the entire algorithm run in $O(n)$ time.

Would you like me to rewrite this using a more optimized approach, or perhaps walk through a dry run with a specific example like `s = "ADOBECODEBANC"` and `x = "ABC"`?

*/