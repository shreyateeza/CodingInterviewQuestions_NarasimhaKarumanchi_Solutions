#include<bits/stdc++.h>
using namespace std;

int non_overlapping_bridges(vector<pair<int,int>> &temp,int n)
{
	//Step - 1 Sort the north side. 
	sort(temp.begin(),temp.end());
	// Create the Dp array to store the flow of non overlapping bridges.
	// ans-->Store the final max number of non-overlapping bridges. 
	vector<int> dp(n+1,INT_MAX);
	int ans=0;
	for(int i=0;i<n;i++)
	{
		int idx=lower_bound(dp.begin(),dp.end(),temp[i].second)-dp.begin();
		dp[idx]=temp[i].second;
		ans=max(ans,idx+1);
	}
	return ans;
}

int main()
{
	int n=4;
	vector<pair<int,int>> temp;
	temp.push_back(make_pair(6,2));
	temp.push_back(make_pair(4,3));
	temp.push_back(make_pair(2,6));
	temp.push_back(make_pair(1,5));
	
	cout<<non_overlapping_bridges(temp,n)<<endl;
	return 0;
}
