void dfsUtil(int root, int parent, vector<vector<int>>& adjList, vector<int>& traversal){
	traversal.push_back(root);
	for(int i=0; i<adjList[root].size(); i++){
		int node = adjList[root][i];
		if(node != parent) dfsUtil(node, root, adjList, traversal);
	}
}

vector<int> dfs(vector<vector<int>> &adjList) {
    // add your logic here
	vector<int> traversal;
	dfsUtil(0, -1, adjList, traversal);
	return traversal;
}
