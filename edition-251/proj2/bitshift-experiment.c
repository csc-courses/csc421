#include<stdio.h>
#include<assert.h>

int main(){
	assert(sizeof(short)==2) ;
	short ss ; 
	unsigned short us ;
	ss = -1 ; 
	us = ss ;
	for (int i=0;i<4;i++) {
		printf("%6d %6du\n", ss, us) ;
		ss = ss>>1 ; 
		us = us>>1 ;
	}
	return 0 ;
}