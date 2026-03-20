To master graphs for a Google interview, you need to shift from "knowing the algorithms" to "recognizing the patterns." Google rarely asks a straightforward "implement BFS" question. Instead, they present a real-world scenario (like organizing file dependencies or finding the shortest path in a city) that you must model as a graph.

---

## 1. The "Big Three" Algorithms
You must be able to write these from scratch, bug-free, in under 15 minutes.

* **Breadth-First Search (BFS):** Used for finding the **shortest path** in unweighted graphs.
    * *Key Concept:* Uses a `std::queue`.
    * *Google Twist:* "Find the minimum number of swaps to sort an array." (The array states are nodes, swaps are edges).
* **Depth-First Search (DFS):** Used for **reachability**, connectivity, and exhaustive searching.
    * *Key Concept:* Uses recursion or a `std::stack`.
    * *Google Twist:* "Find if a path exists in a 2D grid with obstacles."
* **Topological Sort (Kahn’s Algorithm):** Essential for **scheduling** or **dependency** problems.
    * *Key Concept:* Works on Directed Acyclic Graphs (DAGs). It uses "in-degree" counts.
    * *Google Twist:* "Given a list of build tasks and their prerequisites, output a valid build order."



---

## 2. Advanced Graph Patterns
Google interviewers often push candidates toward these "Level 2" topics to see if they can optimize.

### Union-Find (Disjoint Set Union)
This is the most efficient way to handle **connected components** and **cycle detection** in undirected graphs.
* **Why Google loves it:** It’s faster than BFS/DFS for dynamic connectivity ($O(\alpha(n))$, where $\alpha$ is the inverse Ackermann function—essentially constant time).
* **Practice Problem:** "Number of Islands II" (adding land dynamically).



### Dijkstra’s Algorithm
Used for **shortest path in weighted graphs** (where edges have different "costs").
* **Key Concept:** Uses a `std::priority_queue` (Min-Heap).
* **Google Twist:** "Find the path with the maximum probability of success" (Multiplying probabilities instead of adding weights).

---

## 3. Modeling: The Most Important Skill
In the interview, the word "graph" might never be mentioned. You need to identify the graph yourself.

| Scenario | Graph Model | Algorithm to Use |
| :--- | :--- | :--- |
| **Prerequisites / Build Systems** | Directed Graph | Topological Sort |
| **Social Networks (Degrees of separation)** | Undirected Graph | BFS |
| **Cheapest Flight with $K$ stops** | Weighted Graph | Modified Dijkstra or Bellman-Ford |
| **Word Ladders (Changing one letter)** | Implicit Graph | BFS |
| **Network Connectivity / Redundancy** | Undirected Graph | Union-Find or Articulation Points |



---

## 4. Common "Gotchas" and Tips
* **Cycle Detection:** Always remember that detecting a cycle in a *directed* graph requires tracking the "recursion stack" (Back-edges), whereas an *undirected* graph just needs a `visited` set and a `parent` pointer.
* **The "Visited" Set:** Forgetting to mark a node as visited is the #1 reason for infinite loops in interviews. Always write `visited.insert(node)` as soon as you push to the queue/stack.
* **Space Complexity:** Don't forget the Adjacency List. Storing a graph takes $O(V + E)$ space.

---

### Step-by-Step Study Guide
1.  **Days 1-2:** Master BFS/DFS on both **Adjacency Lists** and **2D Grids**.
2.  **Days 3-4:** Implement Topological Sort and Union-Find (with Path Compression).
3.  **Days 5-6:** Solve "Word Ladder," "Course Schedule," and "Number of Islands" on LeetCode.
4.  **Day 7:** Practice Dijkstra’s and learn about **Bi-directional BFS** (a common Google optimization for large graphs).

**Would you like me to walk through the logic of Union-Find, or should we try a mock "Topological Sort" coding problem?**