string reverseWords(string &s) {
	int N = s.size();
	int i=0;
	stack<string> st;
	string str = "";
	while(i<N){
		if(s[i]==' ' && str!=""){
			st.push(str);
			str = "";
		}
		else{
			str += s[i];
		}
		i++;
	}
	st.push(str);
	string answer = "";
	while(st.size()!=1){
		answer += (st.top() + " ");
		st.pop();
	}
	answer += st.top();
	
	return answer;
}