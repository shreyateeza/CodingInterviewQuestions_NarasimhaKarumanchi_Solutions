Calculating complexity for graph algorithms requires looking at two main components: **Vertices ($V$)** (nodes) and **Edges ($E$)** (connections). Unlike linear arrays where complexity is usually just $O(N)$, graph complexity depends on how dense or sparse the connections are.

---

## 1. Key Metrics to Watch

* **$V$:** The number of nodes.
* **$E$:** The number of edges.
* **Adjacency List:** Space is $O(V + E)$ because you store every node and its neighbors.
* **Adjacency Matrix:** Space is $O(V^2)$ because you store a grid representing every possible connection.

---

## 2. Calculating Time Complexity

To find the time complexity, ask yourself:

1. **How many times is each vertex visited?**
2. **How many times is each edge explored?**
3. **What is the cost of the data structure operations (e.g., Priority Queue, Set, or Queue)?**

### Example: Breadth-First Search (BFS)

In BFS, we use a queue to visit nodes layer by layer.

* **Vertex Visit:** Each vertex is pushed and popped from the queue exactly **once**. $\rightarrow O(V)$
* **Edge Exploration:** For every vertex we pull out, we look at all its neighbors (its edges). In a directed graph, we check each edge once; in undirected, twice. $\rightarrow O(E)$
* **Total Time:** $O(V + E)$.

---

## 3. Calculating Space Complexity

Ask yourself:

1. **What is the size of the graph representation?**
2. **What auxiliary structures are used (Stacks, Queues, Distances array, Visited set)?**
3. **In recursion, what is the maximum depth of the call stack?**

### Example: Depth-First Search (DFS)

* **Auxiliary Space:** We need a `visited` array of size $V$. $\rightarrow O(V)$
* **Stack Space:** In the worst case (a graph that is just one long line), the recursion stack goes $V$ levels deep. $\rightarrow O(V)$
* **Total Space:** $O(V)$.

---

## 4. Complexity of Common Graph Algorithms

| Algorithm | Time Complexity | Space Complexity | Why? |
| --- | --- | --- | --- |
| **Dijkstra's** | $O((V + E) \log V)$ | $O(V + E)$ | Uses a Priority Queue to pick the smallest distance. |
| **Bellman-Ford** | $O(V \cdot E)$ | $O(V)$ | Relaxes all edges $V-1$ times. |
| **Kruskal's** | $O(E \log E)$ | $O(V + E)$ | Sorting edges takes $E \log E$. |
| **Floyd-Warshall** | $O(V^3)$ | $O(V^2)$ | Triple nested loop over all pairs of vertices. |

---

## 5. A Practical Example: Dijkstra's Complexity

If you are asked to explain Dijkstra's complexity using a **Binary Heap**:

1. **Extract Min:** We do this for every vertex. $V \times \log V$.
2. **Decrease Key:** Every time we find a shorter path through an edge, we update the heap. $E \times \log V$.
3. **Summing them up:** $O(V \log V + E \log V) = O((V + E) \log V)$.

### Pro-Tip for Interviews

If you see a graph problem, always clarify if it's an **Adjacency List** or **Matrix**. If someone says "BFS takes $O(V^2)$," they are likely assuming an Adjacency Matrix because you have to scan a whole row of length $V$ for every vertex to find neighbors.

**Would you like me to show you how the complexity changes if we use an Adjacency Matrix instead of an Adjacency List?**

---

**To calculate the time and space complexity of graph algorithms, you analyze how the algorithm scales with the number of vertices (V) and edges (E). Time complexity depends on the number of operations performed relative to V and E, while space complexity depends on the data structures used to store the graph and auxiliary information.**

---

## 🔑 Key Principles

### 1. **Input Size Representation**
- Graph algorithms are measured in terms of:
  - **V** = number of vertices
  - **E** = number of edges
- Complexity is expressed using **Big-O notation**.

### 2. **Time Complexity**
- Depends on:
  - Graph representation (**adjacency list vs adjacency matrix**).
  - Traversal or computation steps (loops, recursion, edge relaxations).
- Example:
  - **Adjacency list** → operations scale with \(O(V + E)\).
  - **Adjacency matrix** → operations scale with \(O(V^2)\).

### 3. **Space Complexity**
- Depends on:
  - Storage of graph (list vs matrix).
  - Auxiliary structures (visited arrays, recursion stack, priority queues).
- Example:
  - **Adjacency list** → \(O(V + E)\).
  - **Adjacency matrix** → \(O(V^2)\).

---

## 📊 Common Graph Algorithms

| Algorithm              | Time Complexity | Space Complexity | Notes |
|-------------------------|-----------------|------------------|-------|
| **DFS (Depth-First Search)** | \(O(V + E)\) | \(O(V)\) (stack + visited) | Efficient with adjacency list |
| **BFS (Breadth-First Search)** | \(O(V + E)\) | \(O(V)\) (queue + visited) | Similar to DFS |
| **Dijkstra’s Algorithm** | \(O((V + E)\log V)\) with heap | \(O(V + E)\) | Depends on priority queue |
| **Bellman-Ford** | \(O(V \cdot E)\) | \(O(V)\) | Handles negative weights |
| **Floyd-Warshall** | \(O(V^3)\) | \(O(V^2)\) | All-pairs shortest path |
| **Topological Sort** | \(O(V + E)\) | \(O(V)\) | Works on DAGs |
| **Kruskal’s MST** | \(O(E \log E)\) | \(O(V + E)\) | Sorting edges dominates |
| **Prim’s MST** | \(O((V + E)\log V)\) | \(O(V + E)\) | With min-heap |

---

## ⚖️ How to Calculate Step-by-Step
1. **Identify input size** → vertices (V), edges (E).
2. **Check graph representation**:
   - Adjacency list → efficient for sparse graphs.
   - Adjacency matrix → efficient for dense graphs.
3. **Count operations**:
   - Traversals → proportional to V + E.
   - Nested loops → often \(O(V^2)\) or higher.
4. **Account for auxiliary structures**:
   - Queues, stacks, heaps, recursion depth.

---

## 🚨 Risks & Trade-offs
- **Sparse vs dense graphs**: Algorithms may perform differently depending on representation.
- **Space-heavy algorithms** (like Floyd-Warshall) may be impractical for large graphs.
- **Priority queues** improve time but add memory overhead.

---

✅ In short: **Always express graph algorithm complexity in terms of V and E, consider representation (list vs matrix), and include auxiliary data structures in space analysis.**  

Would you like me to walk through a **worked example** (say BFS or Dijkstra) step by step, showing how each operation contributes to the final complexity?
