void dfsUtil(int root, vector<vector<int>>& adjList, vector<int>& traversal, vector<bool>& visited){
	visited[root] = true;
	traversal.push_back(root);
	for(int i=0; i<adjList[root].size(); i++){
		int node = adjList[root][i];
		if(visited[node] == false){
			dfsUtil(node, adjList, traversal, visited);
		}
	}
}


vector<int> dfs(vector<vector<int>> &adjList) {
    int N = adjList.size();
	vector<int> traversal;
	vector<bool> visited(N, false);
	dfsUtil(0, adjList, traversal, visited);
	return traversal;
}
