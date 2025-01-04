#include <bits/stdc++.h>
using namespace std;
class tree
{
public:
    int n;
    tree *l;
    tree *r;
};

tree *TreeNode(int n)
{
    tree *node = new tree();
    node->n = n;
    node->l = NULL;
    node->r = NULL;
    return (node);
}
int Floor(tree *parent, int input)
{
    if (parent == NULL)
        return -1;
 
    if (parent->n == input)
        return parent->n;
 
    if (parent->n > input)
        return Floor(parent->l, input);

    else{
        int floor = Floor(parent->r, input);
        return (floor<=input && floor!=-1)? floor : parent->n; 
    }
} 

int main()
{
    int num;
    cout<< "Enter the number for which you have to find the floor" << endl;
    cin>> num;
    tree *parent = TreeNode(16);
    parent->l = TreeNode(12);
    parent->r = TreeNode(20);
    parent->l->l = TreeNode(10);
    parent->l->r = TreeNode(14);
    parent->r->l = TreeNode(18);
    parent->r->r = TreeNode(22);
    cout << Floor(parent, num) << endl;
  
    return 0;
}