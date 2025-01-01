bool canCompleteProgram(int n, vector<vector<int>> &prerequisites) {
    // add your logic here
	vector<vector<int>> answer(n);
	int N = prerequisites.size();
	for(int i=0; i<N; i++){
		answer[prerequisites[i][1]].push_back(prerequisites[i][0]);
	}
	vector<int> indegree(n, 0);
	for(int i=0; i<N; i++){
		indegree[prerequisites[i][0]]++;
	}
	queue<int> q;
	for(int i=0; i<n; i++){
		if(indegree[i] == 0) q.push(i);
	}
	while(!q.empty()){
		int course = q.front();
		q.pop();
		for(int i=0; i<answer[course].size(); i++){
			indegree[answer[course][i]]--;
			if(indegree[answer[course][i]] == 0){
				q.push(answer[course][i]);
			}
		}
	}
	for(int i=0; i<n; i++){
		if(indegree[i]>0) return false;
	}
	return true;
}
