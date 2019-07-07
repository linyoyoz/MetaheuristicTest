#include<iostream>
#include<ctime>
#include<cstdlib>
#include"HillClimbing.h"
using namespace std;
int Evaluate(bool *s,int bits)//計算總和的f
{
	int f=0;
	for(int i=0;i<bits;i++)
		f+=s[i];
	return f;
}

void NeighborSelection(bool *s,bool *v,int bits)//HC找一個隨機的state變更
{
	copy(s,s+bits,v);
	int change = rand()%bits;
	v[change]=v[change]%2+1;
}
void PrintState(bool *s,int bits,int f1)//顯示state
{
	cout<<f1<<":";
	for(int i=0;i<bits;i++)
		cout<<s[i];
	cout<<endl;
}
int* HillClimbing(int iterations,int bits,int *ans)//HC
{
	//random init state
	bool *s,*v;
	s = new bool[bits];
	v = new bool[bits];
	for(int i=0;i<bits;i++)
		s[i]=rand()%2;
	
	int f1= Evaluate(s,bits);//E->f1
	for(int i=0;i<iterations;i++)
	{
		NeighborSelection(s,v,bits);//change 1 bits in next state
		int f2=Evaluate(v,bits);
		if(f2>f1)
		{
			copy(v,v+bits,s);
			f1=f2;
		}
		ans[i]+=f1;
		//PrintState(s,bits,f1);
	}
	return ans;
}
