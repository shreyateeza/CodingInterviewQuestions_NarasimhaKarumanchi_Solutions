// A Space efficient Dynamic Programming based C++ program to find minimum number operations to convert s1 to s2
#include <bits/stdc++.h>
using namespace std;

// space optimization
int editDist(string& s1, string& s2){
    int m = s1.size();
    int n = s2.size();
 
    // prev stores results for (i-1) th row and curr for i-th row
    vector<int> prev(m + 1, 0), curr(n + 1, 0);

    // For 0-th row
    for (int j = 0; j <= n; j++) prev[j] = j;

    // Rest of the rows 
    for (int i = 1; i <= m; i++){
        curr[0] = i;  // j = 0
        for (int j = 1; j <= n; j++){
            if (s1[i - 1] == s2[j - 1])
                curr[j] = prev[j - 1];
            else            
                curr[j] = 1 + min({curr[j - 1], prev[j], prev[j - 1]});
        }
        prev = curr;
    }
    return prev[n];
}

int main(){
    string s1 = "GEEXSFRGEEKKS", s2 = "GEEKSFORGEEKS";
    cout << editDist(s1, s2) << "\n";
    return 0;
}
