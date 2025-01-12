int removeDuplicates(int arr[], int n) {
    if(n == 0 || n == 1) return n;       
    int j = 0;
    unordered_map<int,int> mp;   
    for(int i=0; i<n; i++){
        if(mp.find(arr[i])==mp.end()){
          arr[j++] = arr[i];
        }
    }
    return j;
}