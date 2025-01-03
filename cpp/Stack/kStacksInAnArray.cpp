#include<bits/stdc++.h> 
using namespace std;

int pop(int stno,vector<int> &arr,int &t1,int &t2,int &t3){
	if(stno==0){
	if(t1!=0){

	return arr[t1--];
		}
	}
	else if(stno==1){
	if(t2!=0){
	return arr[t2--];
		}
	}	
	if(t3!=0){
		return arr[t1--];
	}
return INT_MAX;
}
void push(int ele,int stno,int &t1,int &t2,int &t3,int &b1,int &b2,int &b3,
vector<int>&arr){
	cout<<"Element pushed in the stack"<<endl;
	if(stno == 0){
		if(t1==b1){
			cout<<"overflow";
			return;
		}
		else arr[++t1]=ele;
		
		
	}
	else if(stno == 1){
		if(t2==b2){
			cout<<"overflow";
			return;
		}
		else arr[++t2]=ele;
		
	}
	else{
			
		if(t3==b3){
			cout<<"overflow";
			return;
		}
		else arr[++t3]=ele;
		
	
	}
	return ;
}

int main(){
	int n = 9;
	int k = 3;
	vector<int>arr(n);
	int t1 = -1 ,t2=2,t3=5;
	int b1=t1+3,b2=t2+3,b3=t3+3;
	//Suppose we are pushing element 11 in stack 0
	push(11,0,t1,t2,t3,b1,b2,b3,arr);
	push(13,0,t1,t2,t3,b1,b2,b3,arr);
	cout<<"Element popoed from the stack "<<pop(0,arr,t1,t2,t3);
	return 0;
}