class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        heights.push_back(0);
        stack<int> st;
        int N = heights.size(), area = 0;
        for(int i=0; i<N; i++){
            if(st.empty() || heights[i]>=heights[st.top()]) st.push(i);
            else{
                int temp = st.top();
                st.pop();
                area = max(heights[temp]*(st.empty()? i: i-st.top()-1), area);
                i--;
            }
        }
        return area;
    }
};