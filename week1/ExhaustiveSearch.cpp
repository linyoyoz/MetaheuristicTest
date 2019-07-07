#include<iostream>
#include<ctime>
#include<cstdlib>
#include"ExhaustiveSearch.h"
using namespace std;
int EvaluateES(bool *s,int bits)//計算總和的f
{
	int f=0;
	for(int i=0;i<bits;i++)
		f+=s[i];
	return f;
}

void EnumNext(bool *v,int bits)//ES找下一個State
{
	for(int i=bits-1;i>=0;i--)
	{
		if(v[i]==1)
			v[i]=0;
		else
		{
			v[i]=1;
			break;
		}
	}
}
int* ExhaustiveSearch(int iterations,int bits,int *ans)//ES
{
	bool *s,*v;
	s=new bool[bits];//init state
	v=new bool[bits];//用於數數字
	for(int i=0;i<bits;i++)
		s[i]=0;
	copy(s,s+bits,v);
	int f1= EvaluateES(s,bits);
	for(int i=0;i<iterations;i++)
	{
		EnumNext(v,bits);//按照順序+1
		int f2=EvaluateES(v,bits);
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