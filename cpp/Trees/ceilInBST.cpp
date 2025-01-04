#include <bits/stdc++.h> 
using namespace std; 

class tree { 
public: 
    int n; 
    tree* l; 
    tree* r; 
};
tree* newNode(int n) 
{ 
    tree* TreeNode = new tree(); 
    TreeNode->n = n; 
    TreeNode->l = NULL; 
    TreeNode->r = NULL; 
    return (TreeNode); 
} 
int Ceil(tree* parent, int input) 
{
    if (parent == NULL) 
        return -1; 
 
    if (parent->n == input) 
        return parent->n; 


    if (parent->n < input) 
        return Ceil(parent->r, input); 
 
    int ceil = Ceil(parent->l, input); 
    return (ceil >= input) ? ceil : parent->n; 
} 
  
int main() 
{ 
    int num;
    cout<<"Enter the value for which you want to find ceil"<< endl;
    cin>>num;
    tree* parent = newNode(15); 
    parent->l = newNode(11); 
    parent->r = newNode(19); 
    parent->l->l = newNode(9); 
    parent->l->r = newNode(13); 
    parent->r->l = newNode(17); 
    parent->r->r = newNode(21); 
    cout << Ceil(parent, num) << endl; 
  
    return 0; 
}