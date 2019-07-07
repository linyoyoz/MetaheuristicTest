#include<iostream>
#include<string>
#include<sstream>
#include<ctime>
#include<cstdlib>
#include<fstream>
#include"HillClimbing.h"
#include"ExhaustiveSearch.h"
using namespace std;

int main(int argc,char** argv)
{
	srand(time(NULL));//每次執行依照時間產生亂數
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
	int *ans;//用來紀錄每個iterations目前找到的最好結果
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
	fp.open("test.csv", ios::out);
	for(int i=0;i<iterations;i++)//將每個iterations之結果寫入檔案
	{
		ans[i]/=runs;
		fp<<i<<","<<ans[i]<<endl;
	}
	cout<<"find max:"<<ans[iterations-1]<<endl;
	fp<<endl;
    fp.close();
	
	return 0;
}