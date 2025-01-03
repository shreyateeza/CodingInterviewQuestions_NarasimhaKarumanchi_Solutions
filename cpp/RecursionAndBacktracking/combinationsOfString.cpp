#include<iostream>
using namespace std;
void Combi(char a[], int reqLen, int s, int currLen, bool check[], int l)
{
   if(currLen > reqLen)
   return;
   else if (currLen == reqLen) {
      cout<<"\t";
      for (int i = 0; i < l; i++) {
         if (check[i] == true) {
            cout<<a[i]<<" ";
         }
      }
      cout<<"\n";
      return;
   }
   if (s == l) {
      return;
   }
   check[s] = true;
   Combi(a, reqLen, s + 1, currLen + 1, check, l);
   check[s] = false;
   Combi(a, reqLen, s + 1, currLen, check, l);
}

int main() {
   int i,n;
   bool check[n];
   cout<<"Enter the number of element array have: ";
   cin>>n;
   char a[n];
   cout<<"\n";
   for(i = 0; i < n; i++) {
      cout<<"Enter "<<i+1<<" element: ";
      cin>>a[i];
      check[i] = false;
   }
   for(i = 1; i <= n; i++) {
      cout<<"\nThe all possible combination of length "<<i<<" for the given array set:\n";
      Combi(a, i, 0, 0, check, n);
   }
   return 0;
}