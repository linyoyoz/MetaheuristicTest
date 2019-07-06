#include<iostream>
#include<string>
#include<sstream>
#include<ctime>
#include<cstdlib>
#include<fstream>
using namespace std;
int Evaluate(bool *s,int bits)//計算總和的f
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
int* ExhaustiveSearch(int iterations,int bits,int *ans)//ES
{
	bool *s,*v;
	s=new bool[bits];//init state
	v=new bool[bits];//用於數數字
	for(int i=0;i<bits;i++)
		s[i]=0;
	copy(s,s+bits,v);
	int f1= Evaluate(s,bits);
	for(int i=0;i<iterations;i++)
	{
		EnumNext(v,bits);//按照順序+1
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
int main(int argc,char** argv)
{
	srand(time(NULL));
	string useAlgorithm;
	char* fileName;
	int runs,iterations,bits;
	if(argc<6)
	{
		cerr << "too few arguments, expecting 6 arguments to be given (only "<<argc<< ")" << endl;
		return 1;
	}
	else
	{
		useAlgorithm=argv[1];
		fileName=argv[5];
		istringstream(argv[2])>>runs;
		istringstream(argv[3])>>iterations;
		istringstream(argv[4])>>bits;
	}
	int *ans;
	ans = new int[iterations];
	for(int i=0;i<iterations;i++)
		ans[i]=0;
	for(int i=0;i<runs;i++)
	{
		if (useAlgorithm.compare("hc")==0)
			ans=HillClimbing(iterations,bits,ans);
		else if (useAlgorithm.compare("es")==0)
			ans=ExhaustiveSearch(iterations,bits,ans);
		else
		{
			cerr <<"algotithm argument must be hc or es"<<endl;
			return 1;
		}	
	}
	fstream fp;
	fp.open(fileName, ios::out);
	for(int i=0;i<iterations;i++)
	{
		ans[i]/=runs;
		fp<<i<<","<<ans[i]<<endl;
	}
	fp<<endl;
    fp.close();
	
	return 0;
}