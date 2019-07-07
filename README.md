# week1 homework  

編譯:  
g++ -c ExhaustiveSearch.cpp  HillClimbing.cpp  
g++ -o search ExhaustiveSearch.o HillClimbing.o search.cpp  

測試HC 和 ES兩種演算法對於100bits之One Max Problem之結果  
search.cpp為主要程式碼，裏頭包含ES和HC兩種演算法，參數格式如同規定  

測試ES:   
  ./search es 1 1000 100 ""  
測試HC:  
  ./search hc 1 1000 100 ""  
輸出:  
excel畫出的圖表，1000次的interations於100bits 的測試  
![image](https://github.com/linyoyoz/MetaheuristicTest/blob/master/week1/100%20bits_1000iterations.PNG)   
