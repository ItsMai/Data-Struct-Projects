  
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <bits/stdc++.h>

using namespace std;

void helper(string in, int start, int end){
	if(start == end){
		cout << in << endl;
	}else{
		for(int i = start; i <= end; i++){
			swap(in[start], in[i]); 	//swaping once for first one
			helper(in, start+1, end);	//only changing the left one to be swapped
			swap(in[start], in[i]);		//swapping for second time
		}
	}
}
void permutations(string in){
	long unsigned int length = in.size()-1;
	helper(in, 0, (int)length);

}
