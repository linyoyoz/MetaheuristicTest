#ifndef __ES_H__
#define __ES_H__
int EvaluateES(bool *s,int bits);
void EnumNext(bool *v,int bits);
int* ExhaustiveSearch(int iterations,int bits,int *ans);
#endif