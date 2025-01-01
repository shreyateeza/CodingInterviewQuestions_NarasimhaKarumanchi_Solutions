vector<int> bfs(vector<vector<int>> &adjList) {
    // add your logic here
	int N = adjList.size();
	vector<int> result;
	vector<bool> visited(N, false);
	if(N == 0 ) return result;
	queue<int> q;
	q.push(0);
	visited[0] = true;
	for(int i=0; i<N; i++){
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
