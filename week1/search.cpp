#include<iostream>
#include<string>
#include<sstream>
#include<ctime>
#include<cstdlib>
#include<vector>
#include<fstream>
using namespace std;
int Evaluate(vector<int> *s)//計算總和的f
{
	int f=0;
	for(vector<int>::iterator it=s->begin();it!=s->end();it++)
		f+=*it;
	return f;
}
void EnumNext(vector<int> *s)//ES找下一個State
{
	for(vector<int>::iterator it=s->end()-1;it!=s->begin();it--)
	{
		if(*it==1)
			*it=0;
		else
		{
			*it=1;
			break;
		}
	}
}
void PrintState(vector<int> *s,int f1)//顯示state
{
	cout<<f1<<":";
	for(vector<int>::iterator it=s->begin();it!=s->end();it++)
		cout<<*it;
	cout<<endl;
}

vector<int>* NeighborSelection(vector<int> *s)//HC找一個隨機的state變更
{
	vector<int> *v=new vector<int>();
	v->assign(s->begin(),s->end());
	int change = rand()%s->size();
	v->at(change)=(v->at(change)+1)%2;
	return v;
}
void HillClimbing(int iterations,int bits,vector<double> *ans)//HC
{
	//random init state
	vector<int> state;
	vector<int> *s=new vector<int>(bits,0);
	for(vector<int>::iterator it=s->begin();it!=s->end();it++)
		*it=rand()%2;
	
	int f1= Evaluate(s);//E->f1
	for(int i=0;i<iterations;i++)
	{
		vector<int> *v=NeighborSelection(s);//change 1 bits in next state
		int f2=Evaluate(v);
		if(f2>f1)
		{
			delete s;
			s=v;
			f1=f2;
		}
		else
			delete v;
		ans->at(i)+=f1;
		//PrintState(s,f1);
	}
}
void ExhaustiveSearch(int iterations,int bits,vector<double> *ans)//ES
{
	vector<int> *s,*en;
	s=new vector<int>(bits,0);//init state
	en=new vector<int>(bits,0);//用於數數字	
	int f1= Evaluate(s);
	for(int i=0;i<iterations;i++)
	{
		EnumNext(en);//按照順序+1
		int f2=Evaluate(en);	
		if(f2>f1)
		{
			s->assign(en->begin(),en->end());
			f1=f2;
		}
		ans->at(i)+=f1;
		//PrintState(s,f1);
	}
}
int main(int argc,char** argv)
{
	srand(time(NULL));
	string useAlgorithm,fileName;
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
	
	vector<double> ans(iterations,0);
	for(int i=0;i<runs;i++)
	{
		if (useAlgorithm.compare("hc")==0)
			HillClimbing(iterations,bits,&ans);
		else if (useAlgorithm.compare("es")==0)
			ExhaustiveSearch(iterations,bits,&ans);
		else
		{	
			cerr <<"algotithm argument must be hc or es"<<endl;
			return 1;
		}
	}
	fstream fp;
	fp.open("test.csv", ios::out);
	for(int i=0;i<=ans.size();i++)
	{
		ans[i]/=runs;
		fp<<i<<","<<ans[i]<<endl;
	}
	fp<<endl;
    fp.close();
	
	return 0;
}