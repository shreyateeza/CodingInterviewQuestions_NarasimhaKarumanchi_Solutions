// C++ Program to find area of the largest region of 1s

#include <bits/stdc++.h>
using namespace std;

// A function to check if cell(r, c) can be included in DFS
bool isSafe(vector<vector<int>> &M, int r, int c, int rows, int cols) {

    // row number is in range, column number is in range and
    // value is 1
    return (r >= 0 && r < rows) && (c >= 0 && c < cols) 
                                                  && (M[r][c] == 1);
}

// Breadth-First-Search to visit all cells in the current island
int BFS(vector<vector<int>> &M, int r, int c, int rows, int cols) {

    // These arrays are used to get row and column
    // numbers of 8 neighbours of a given cell
    vector<int> dirR = {-1, -1, -1, 0, 0, 1, 1, 1};
    vector<int> dirC = {-1, 0, 1, -1, 1, -1, 0, 1};

    int area = 0;

    // create a queue for bfs traversal
    queue<pair<int, int>> q;

    // Push the cell(r, c) into queue and mark it as visited
    q.push({r, c});
    M[r][c] = 0;
    while (!q.empty()) {
        pair<int, int> curr = q.front();
        q.pop();
          
          // Increment the area of region
          area += 1;

          // Recur for all 8 connected neighbours
        for (int i = 0; i < 8; i++) {
            int newR = curr.first + dirR[i];
            int newC = curr.second + dirC[i];

            if (isSafe(M, newR, newC, rows, cols)) {
                M[newR][newC] = 0;
                  q.push({newR, newC});
            }
        }
    }
    return area;
}


// function to find area of the largest region of 1s
int largestRegion(vector<vector<int>> &M) {
      int rows = M.size(), cols = M[0].size();
  
    // Initialize result as 0 and traverse through the
    // all cells of given matrix
    int maxArea = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
              
            // If a cell with value 1 is found
            if (M[i][j] == 1) {
                int area = BFS(M, i, j, rows, cols);

                // maximize the area 
                maxArea = max(maxArea, area);
            }
        }
    }
    return maxArea;
}

int main() {
    vector<vector<int>> M = {{1, 0, 0, 0, 1, 0, 0},
                             {0, 1, 0, 0, 1, 1, 1},
                             {1, 1, 0, 0, 0, 0, 0},
                             {1, 0, 0, 1, 1, 0, 0},
                             {1, 0, 0, 1, 0, 1, 1}};

    cout << largestRegion(M);

    return 0;
}