void generateStrings(int n, int k, int size){
    if(n<1) {
        printArray(arr, size);
        return;
    }
    //now generate all other strings
    for (int i = 0; i<k ; i++) {
        arr[n-1] = i;
        generateStrings(n-1, k, size);
    }
}