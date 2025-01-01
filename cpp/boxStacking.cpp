// C++ program to implement
// box stacking problem
#include <bits/stdc++.h>
using namespace std;

int maxHeight(vector<int> &height, vector<int> &width, vector<int> &length) {
  
    int n = height.size();

    // Create a 2d array to store all
    // orientations of boxes in (l, b, h)
    // manner.
    vector<vector<int>> boxes;
    for (int i = 0; i < n; i++) {
        int a = height[i], b = width[i], c = length[i];

        boxes.push_back({a, b, c});
        boxes.push_back({a, c, b});
        boxes.push_back({b, a, c});
        boxes.push_back({b, c, a});
        boxes.push_back({c, a, b});
        boxes.push_back({c, b, a});
    }

    // Sort the boxes in descending
    // order of length and width.
    sort(boxes.begin(), boxes.end(), greater<vector<int>>());

    vector<int> dp(boxes.size());

    int ans = 0;

    // Check for all boxes starting as base.
    for (int i = boxes.size() - 1; i >= 0; i--) {
        dp[i] = boxes[i][2];

        for (int j = i + 1; j < boxes.size(); j++) {
            if (boxes[i][0] > boxes[j][0] && boxes[i][1] > boxes[j][1]) {
                dp[i] = max(dp[i], boxes[i][2] + dp[j]);
            }
        }

        ans = max(ans, dp[i]);
    }

    return ans;
}

int main() {
  
    vector<int> height = {4, 1, 4, 10};
    vector<int> width = {6, 2, 5, 12};
    vector<int> length = {7, 3, 6, 32};

    cout << maxHeight(height, width, length);
    return 0;
}
