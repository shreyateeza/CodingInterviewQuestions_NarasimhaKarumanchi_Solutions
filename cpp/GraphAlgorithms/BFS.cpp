vector<int> bfs(vector<vector<int>> &adjList) {
    // add your logic here
	int N = adjList.size();
	vector<int> result;
	vector<bool> visited(N, false);
	if(N == 0 ) return result;
	queue<int> q;
	q.push(0);
	visited[0] = true;
	for(int i=0; i<N; i++){  // This line is incorrect, see below the correct code
		int node = q.front();
		q.pop();
		result.push_back(node);
		for(int j=0; j<adjList[node].size(); j++){
			if(visited[adjList[node][j]]) continue;
			q.push(adjList[node][j]);
			visited[adjList[node][j]] = true;
		}
	}
	return result;
}

/*

This code implements a **Breadth-First Search (BFS)** traversal of a graph starting from **Node 0**. It uses a queue to explore the graph level by level and returns a list of nodes in the order they were visited.

However, there is a **significant logical bug** in the loop structure that would cause this code to fail on most graphs. Let's break down how it works and where it goes wrong.

---

### 1. The Core Components
* **`adjList`**: The input is an adjacency list where `adjList[i]` contains all neighbors of node `i`.
* **`visited`**: A boolean vector that prevents the algorithm from going in circles (infinite loops) by marking nodes once they've been added to the queue.
* **`queue<int> q`**: The "waiting room." BFS always uses a queue to ensure nodes are processed in the order they are discovered (First-In, First-Out).



---

### 2. The Step-by-Step Logic
1.  **Initialization**: It marks Node 0 as visited and pushes it into the queue.
2.  **The "Discovery" Loop**:
    * It takes a node out of the front of the queue (`q.pop()`).
    * It adds that node to the `result` vector.
    * It looks at all neighbors of that node. If a neighbor hasn't been visited yet, it marks it as `visited` and pushes it into the `q`.

---

### 3. The Bug: `for(int i=0; i<N; i++)`
This is the part that needs a "helpful peer" correction.

In standard BFS, you should loop **as long as the queue is not empty** (`while (!q.empty())`). In your code, the loop is fixed to run exactly `N` times:
```cpp
for(int i=0; i<N; i++) { ... }
```

**Why is this a problem?**
* **Disconnected Graphs**: If the graph has 10 nodes but Node 0 is only connected to 3 of them, the queue will become empty after 3 iterations. On the 4th iteration, `q.front()` will be called on an **empty queue**, which causes the program to crash (undefined behavior).
* **Standard Practice**: A BFS should explore based on connectivity, not a fixed count of nodes.



---

### 4. The Corrected Version
Here is how that middle section should look to be robust:

```cpp
vector<int> bfs(vector<vector<int>> &adjList) {
    int N = adjList.size();
    if(N == 0) return {};

    vector<int> result;
    vector<bool> visited(N, false);
    queue<int> q;

    q.push(0);
    visited[0] = true;

    // Correct logic: loop while there are nodes left to explore
    while(!q.empty()) {
        int node = q.front();
        q.pop();
        result.push_back(node);

        for(int neighbor : adjList[node]) {
            if(!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    return result;
}
```

### Summary of BFS Complexity
* **Time Complexity**: $O(V + E)$ where $V$ is vertices and $E$ is edges.
* **Space Complexity**: $O(V)$ to store the `visited` array and the queue.

Would you like me to show you how to modify this code so it can handle **disconnected graphs** (where some nodes aren't reachable from Node 0)?

*/


#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph {
    int V; 
    vector<vector<int>> adj; 

public:
    Graph(int v) : V(v), adj(v) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // Undirected graph
    }

    // Standard BFS logic for one component
    void bfs(int startNode, vector<bool>& visited) {
        queue<int> q;

        visited[startNode] = true;
        q.push(startNode);

        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            cout << curr << " ";

            for (int neighbor : adj[curr]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }

    // Wrapper function to handle disconnected components
    void connectedComponentsBFS() {
        vector<bool> visited(V, false);

        for (int i = 0; i < V; i++) {
            // If the node hasn't been visited, it's a new component
            if (!visited[i]) {
                bfs(i, visited);
            }
        }
    }
};