class MedianFinder {
public:
    priority_queue<int> high;
    priority_queue<int, vector<int>, greater<int>> low;

    MedianFinder() {
    }
    
    void addNum(int num) {
        low.push(num);
        high.push(low.top());
        low.pop();
        if(high.size() > low.size()){
            low.push(high.top());
            high.pop();
        }
    }
    
    double findMedian() {
        return low.size()>high.size()? low.top(): (low.top()+high.top())/2.0;
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */