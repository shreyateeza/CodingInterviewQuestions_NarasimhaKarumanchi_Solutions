This Java code implements **Radix Sort**, a non-comparative sorting algorithm that sorts integers by processing individual digits. The `radixSort` method orchestrates the sorting process, while the `countingSort` method sorts the array based on a specific digit's place value.

### Explanation of the Code

The provided code is written in **Java**, not C++. It consists of two main methods:

-   `radixSort(int[] arr)`: This is the main function. It first finds the maximum element in the array to determine the number of digits in the largest number. It then iterates, calling `countingSort` for each digit place value (units, tens, hundreds, and so on) starting from 1. The `placeVal` variable is used to determine which digit is being sorted (e.g., `placeVal=1` for units digit, `placeVal=10` for tens digit). This process continues until all digits of the largest number have been considered.

-   `countingSort(int[] arr, int placeVal)`: This is a helper method that sorts the input array `arr` based on the digit at the specified `placeVal`. It uses a **Counting Sort** algorithm.
    1.  `int[] counts = new int[NUM_DIGITS];`: An array `counts` of size 10 is created to store the frequency of each digit (0-9) at the current `placeVal`.
    2.  `for (int elem : arr) { ... }`: This loop counts the occurrences of each digit. For each element `elem`, `(elem / placeVal) % 10` isolates the digit at the `placeVal` position, and its count is incremented in the `counts` array.
    3.  `int startingIndex = 0; ... for (int i = 0; i < counts.length; i++) { ... }`: This loop modifies the `counts` array to store the **starting index** for each digit in the final sorted array. The value at `counts[i]` becomes the index where the first element with digit `i` should be placed.
    4.  `int[] sortedArray = new int[arr.length]; ... for (int elem : arr) { ... }`: A new array `sortedArray` is created. This loop iterates through the original array `arr` again. For each element, it determines its digit at the `placeVal` and uses the modified `counts` array to find the correct sorted position. The element is placed in `sortedArray`, and the corresponding index in the `counts` array is incremented to prepare for any duplicate digits.
    5.  `for (int i = 0; i < arr.length; i++) { ... }`: Finally, the `sortedArray` is copied back to the original array `arr`, ensuring the sorting is applied in-place for the next pass of `radixSort`.

***

### Dry Run with an Example

Let's trace `radixSort` with the array `arr = {170, 45, 75, 90, 802, 24, 2, 66}`.

#### Pass 1: Sorting by the **units** digit (`placeVal = 1`)

1.  **Count Digits**: The `counts` array will track the units digit of each number.
    -   `170`: units digit is 0. `counts[0]++`.
    -   `45`: units digit is 5. `counts[5]++`.
    -   `75`: units digit is 5. `counts[5]++`.
    -   `90`: units digit is 0. `counts[0]++`.
    -   `802`: units digit is 2. `counts[2]++`.
    -   `24`: units digit is 4. `counts[4]++`.
    -   `2`: units digit is 2. `counts[2]++`.
    -   `66`: units digit is 6. `counts[6]++`.
    -   **`counts` array**: `[2, 0, 2, 0, 1, 2, 1, 0, 0, 0]` (for digits 0-9)

2.  **Calculate Starting Indices**: The `counts` array is modified to hold the starting index for each digit.
    -   `counts[0]` becomes 0.
    -   `counts[1]` remains 2 (0+2).
    -   `counts[2]` becomes 2 (2+0).
    -   `counts[3]` becomes 4 (2+2).
    -   `counts[4]` becomes 4 (4+0).
    -   ...and so on.
    -   **`counts` array**: `[0, 2, 2, 4, 4, 5, 7, 8, 8, 8]`

3.  **Place Elements in Sorted Array**: A new array `sortedArray` is filled based on the `counts` array.
    -   `170`: units digit is 0. `sortedArray[counts[0]] = 170`. `counts[0]` becomes `0+1=1`.
    -   `45`: units digit is 5. `sortedArray[counts[5]] = 45`. `counts[5]` becomes `5+1=6`.
    -   `75`: units digit is 5. `sortedArray[counts[5]] = 75`. `counts[5]` becomes `6+1=7`.
    -   `90`: units digit is 0. `sortedArray[counts[0]] = 90`. `counts[0]` becomes `1+1=2`.
    -   ...and so on.
    -   **`sortedArray` after pass 1**: `{170, 90, 802, 2, 24, 45, 75, 66}`. The numbers are now sorted by their units digit.

4.  **Copy Back**: The `sortedArray` is copied to `arr`. `arr` is now `{170, 90, 802, 2, 24, 45, 75, 66}`.

#### Pass 2: Sorting by the **tens** digit (`placeVal = 10`)

The process repeats. The `counts` array is reset and re-populated based on the tens digit of each number in the **current `arr`**.
1.  **Count Digits**: `170` (tens digit 7), `90` (tens digit 9), `802` (tens digit 0), `2` (tens digit 0), etc.
2.  **Calculate Starting Indices**: The `counts` array is modified.
3.  **Place Elements**: The `sortedArray` is populated. `802` and `2` (both with tens digit 0) will be placed first, maintaining their relative order from the previous pass (`802` before `2`). This is a key property of Radix Sort—it's **stable**.
4.  **Copy Back**: The `sortedArray` is copied to `arr`. `arr` becomes `{802, 2, 24, 45, 66, 75, 90, 170}`.

#### Pass 3: Sorting by the **hundreds** digit (`placeVal = 100`)

The process repeats one last time.
1.  **Count Digits**: `802` (hundreds digit 8), `2` (hundreds digit 0), etc.
2.  **Calculate Starting Indices**.
3.  **Place Elements**.
4.  **Copy Back**: The final sorted array is copied to `arr`. `arr` is now `{2, 24, 45, 66, 75, 90, 170, 802}`.

The `while` loop condition `maxElem / placeVal > 0` is now `802 / 1000 > 0`, which is false, so the process terminates.

***

### Time and Space Complexity

#### Time Complexity: $O(d \cdot (n+k))$
-   $n$: the number of elements in the array.
-   $k$: the base of the numbers being sorted (here, $k=10$ for decimal digits).
-   $d$: the number of digits in the maximum element. This is $O(\log_{k} M)$ where $M$ is the maximum value.
-   The `countingSort` function is called **$d$** times.
-   Each call to `countingSort` involves three passes:
    -   Counting digits: $O(n)$
    -   Calculating starting indices: $O(k)$
    -   Placing elements in the sorted array: $O(n)$
-   Thus, one call to `countingSort` is $O(n+k)$.
-   The total time complexity is $O(d \cdot (n+k))$. For decimal numbers, $k$ is a constant, so the complexity is often simplified to $O(d \cdot n)$.

#### Space Complexity: $O(n+k)$
-   The algorithm requires two auxiliary arrays:
    -   `counts` array: size $k=10$. This is $O(k)$.
    -   `sortedArray`: size $n$. This is $O(n)$.
-   The total space complexity is $O(n+k)$. For decimal numbers, this is simplified to $O(n)$ as $k$ is constant.


---

`
public class Solution {
    private static final int NUM_DIGITS = 10;

    public void countingSort(int[] arr, int placeVal) {
        // Sorts an array of integers where minimum value is 0 and maximum value is NUM_DIGITS
        int[] counts = new int[NUM_DIGITS];

        for (int elem : arr) {
            int current = elem / placeVal;
            counts[current % NUM_DIGITS] += 1
        }

        // we now overwrite our original counts with the starting index
        // of each digit in our group of digits
        int startingIndex = 0;
        for (int i = 0; i < counts.length; i++) {
            int count = counts[i];
            counts[i] = startingIndex;
            startingIndex += count;
        }

        int[] sortedArray = new int[arr.length];
        for (int elem : arr) {
            int current = elem / placeVal;
            sortedArray[counts[current % NUM_DIGITS]] = elem;
            // since we have placed an item in index counts[current % NUM_DIGITS],
            // we need to increment counts[current % NUM_DIGITS] index by 1 so the
            // next duplicate digit is placed in appropriate index
            counts[current % NUM_DIGITS] += 1;
        }

        // common practice to copy over sorted list into original arr
        // it's fine to just return the sortedArray at this point as well
        for (int i = 0; i < arr.length; i++) {
            arr[i] = sortedArray[i];
        }
    }

    public void radixSort(int[] arr) {
        int maxElem = Integer.MIN_VALUE;
        for (int elem : arr) {
            if (elem > maxElem) {
                maxElem = elem;
            }
        }

        int placeVal = 1;
        while (maxElem / placeVal > 0) {
            countingSort(arr, placeVal);
            placeVal *= 10;
        }
    }
}
`