class Solution {
public:
    int trailingZeroes(int n) {
        int count = 0, five = 5;
        while(n/five>0){
            count += n/five; 
            five *= 5;
        }
        return count;
    }
};