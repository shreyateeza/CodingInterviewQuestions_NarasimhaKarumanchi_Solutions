class MinStack {
public:
    stack<int> st;
    int minm = INT_MAX;

    MinStack() {
        while(!st.empty()) st.pop();
    }
    
    void push(int val) {
        if(st.empty()) minm = val;
        else if(minm >= val){
            st.push(minm);
            minm = val;
        }
        st.push(val);
    }
    
    void pop() {
        if(!st.empty()){
            if(st.top() == minm){
                st.pop();
                if(!st.empty()){
                    minm = st.top();
                    st.pop();
                }
                return;
            }
        }
        st.pop();
    }
    
    int top() {
        if(st.empty()) return -1;
        return st.top();
        
    }
    
    int getMin() {
        if(st.empty()) return -1;
        return minm;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */