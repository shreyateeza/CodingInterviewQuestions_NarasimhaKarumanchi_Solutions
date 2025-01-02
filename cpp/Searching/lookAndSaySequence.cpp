// C++ code to implement the above approach
#include <iostream>
#include <vector>

using namespace std;

// Function to generate the nth row of the look-and-say
// pattern

string generateNthRow(int n)
{
  //vector to store all the intermediary results
    vector<string> dp(n + 1);
  //initialization
    dp[1] = "1";
    for (int i = 2; i <= n; i++) {
        string prev = dp[i - 1];
        string curr = "";
        for (int j = 0; j < prev.size(); j++) {
            int count = 1;
            while (j + 1 < prev.size()
                   && prev[j] == prev[j + 1]) {
                count++;
                j++;
            }
            curr += to_string(count) + prev[j];
        }
        dp[i] = curr;
    }
    return dp[n];
}

int main()
{
    int n = 3;
    cout << generateNthRow(n) << endl;
    return 0;
}
