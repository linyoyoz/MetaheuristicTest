#ifndef __HC_H__
#define __HC_H__
int Evaluate(bool *s,int bits);
void NeighborSelection(bool *s,bool *v,int bits);
void PrintState(bool *s,int bits,int f1);
int* HillClimbing(int iterations,int bits,int *ans);


#endif