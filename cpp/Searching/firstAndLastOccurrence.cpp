vector<int> searchRange(vector<int> &A, int B) {
    // add your logic here
	int N = A.size();
    int low = 0, high = N-1, lower = -1, upper = -1;
    while(low<=high){
        int mid = low + (high-low)/2;
        if(A[mid] == B){
            lower = mid;
            high = mid-1;
        }
        else if(A[mid]>B) high = mid-1;
        else low = mid+1;
    }
    low = 0, high  = N-1;
    while(low<=high){
        int mid = low +(high-low)/2;
        if(A[mid] == B){
            upper = mid;
            low = mid+1;
        }
        else if(A[mid]>B){
            high = mid-1;
        }
        else low = mid+1;
    }
    return {lower, upper};
}