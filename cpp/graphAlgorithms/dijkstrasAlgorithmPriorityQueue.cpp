#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

// Define a struct Node to store the values
struct Node {
    int v;
    int distance;

    // Define a comparator method to compare distance of two nodes
    bool operator<(const Node& other) const {
        return distance > other.distance;
    }
};

// Function to implement Dijkstra Algorithm to find shortest distance
vector<int> dijkstra(int V, vector<vector<pair<int, int>>>& adj, int S) {
    // Initialize a visited array and map
    vector<bool> visited(V, false);
    unordered_map<int, Node> m;
    
    // Initialize a priority queue
    priority_queue<Node> pq;

    // Insert source node into map
    m[S] = {S, 0};
    // Add source node to priority queue
    pq.push({S, 0});

    // While the priority queue is not empty
    while (!pq.empty()) {
        // Pop the node with the minimum distance from priority queue
        Node n = pq.top();
        pq.pop();

        // Get the vertex and distance
        int v = n.v;
        int distance = n.distance;

        // Mark the vertex as visited
        visited[v] = true;

        // Get the adjacency list of the vertex
        vector<pair<int, int>> adjList = adj[v];

        // For every adjacent node of the vertex
        for (const auto& edge : adjList) {
            // If the node is not yet visited
            if (!visited[edge.first]) {
                // If the node is not present in the map
                if (m.find(edge.first) == m.end()) {
                    // Put the node in the map
                    m[edge.first] = {v, distance + edge.second};
                } else {
                    // Get the node from the map
                    Node& sn = m[edge.first];

                    // Check if the new distance is less than the current distance of the node
                    if (distance + edge.second < sn.distance) {
                        // Update the node's distance
                        sn.v = v;
                        sn.distance = distance + edge.second;
                    }
                }

                // Push the node to the priority queue
                pq.push({edge.first, distance + edge.second});
            }
        }
    }

    // Initialize a result vector
    vector<int> result(V, 0);

    // For every key in the map
    for (const auto& entry : m) {
        // Add the distance of the node to the result
        result[entry.first] = entry.second.distance;
    }

    // Return the result vector
    return result;
}

int main() {
    // Initialize adjacency list and map
    vector<vector<pair<int, int>>> adj;
    unordered_map<int, vector<pair<int, int>>> m;

    // Initialize number of vertices and edges
    int V = 6;
    int E = 5;

    // Define u, v, and w
    vector<int> u = {0, 0, 1, 2, 4};
    vector<int> v = {3, 5, 4, 5, 5};
    vector<int> w = {9, 4, 4, 10, 3};

    // For every edge
    for (int i = 0; i < E; ++i) {
        // Create an edge pair
        pair<int, int> edge = {v[i], w[i]};

        // If u[i] is not present in map
        if (m.find(u[i]) == m.end()) {
            // Create a new adjacency list
            vector<pair<int, int>> adjList;
            m[u[i]] = adjList;
        }

        // Add the edge to the adjacency list
        m[u[i]].push_back(edge);

        // Create another edge pair
        pair<int, int> edge2 = {u[i], w[i]};

        // If v[i] is not present in map
        if (m.find(v[i]) == m.end()) {
            // Create a new adjacency list
            vector<pair<int, int>> adjList2;
            m[v[i]] = adjList2;
        }

        // Add the edge to the adjacency list
        m[v[i]].push_back(edge2);
    }

    // For every vertex
    for (int i = 0; i < V; ++i) {
        // If the vertex is present in map
        if (m.find(i) != m.end()) {
            // Add the adjacency list to the main adjacency list
            adj.push_back(m[i]);
        } else {
            // Add null to the main adjacency list
            adj.push_back({});
        }
    }

    // Define source node
    int S = 1;

    // Call the dijkstra function
    vector<int> result = dijkstra(V, adj, S);

    // Print the result in the specified format
    cout << "[";
    for (int i = 0; i < V; ++i) {
        if (i > 0) {
            cout << ", ";
        }
        cout << result[i];
    }
    cout << "]";

    return 0;
}
