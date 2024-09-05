#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<assert.h>

#include "virtmem.h"

/*
 * author: bjr
 * update:
 *	 31 aug 2024 -bjr: created
  *	  4 sep 2024 -bjr: 
 */

int g_debug = 0 ;
int is_verbose = 0 ;

#define USAGE_MESSAGE "usage: demand [-t][-v...]"
#define N_VM 4

#define LINE_LENGTH 2048

void pte_dump_all(struct VirtualMemory * vm_s[], int n_vm) {
	int i ;
	assert(n_vm<=N_VM) ;
	for (i=0; i<n_vm; i++) {
		printf("\nvirtual space %d at %p:\n",i, vm_s[i]) ;
		pte_dump(vm_s[i], 8) ;
		printf("\n") ;
	}
	return ;
}

int main(int argc, char * argv[]) {
	int ch ;
	int i, j ;
	char buf[LINE_LENGTH] ;
	char * buf_p ;
	int print_page_tables = 0 ;

	while ((ch = getopt(argc, argv, "vt")) != -1) {
		switch(ch) {
			case 'v':
				is_verbose ++ ;
				break ;
			case 't':
				print_page_tables = 1;
				break ;
			default:
				printf("%s\n", USAGE_MESSAGE) ;
				return 0 ;
		}
	}
	argc -= optind;
	argv += optind;

	{
		struct PhysicalMemory * pm ;
		struct VirtualMemory * vm_s[N_VM] ;
		int vm_select ; 
		int vm_free[N_VM] ;
		
		// create N_VM virtual memory spaces
		pm = create_physicalmemory() ;
		for (i=0; i<N_VM; i++) {
			vm_s[i] = create_virtualmemory(pm) ;
			vm_free[i] = 0 ;
		}

		if (print_page_tables) pte_dump_all(vm_s, N_VM) ;
		
		while ((buf_p = fgets(buf,LINE_LENGTH, stdin))) {  // ((...)) makes clang happy
		
			// first character commands
			switch (*buf_p) {
			case '+':
				pte_dump_all(vm_s, N_VM) ;
				continue ;
			case '.':
				return 0 ;
			}
		
			vm_select = *(buf_p++)-'0' ;
			if (vm_select<0 || vm_select>=N_VM) continue ;
	
			vm_write_str(vm_s[vm_select], vm_free[vm_select], buf_p) ;
			vm_free[vm_select] += strlen(buf_p)+1 ; // null byte
		}	
		
		// print physical memory
		pmem_dump(pm, N_VM*N_VM*PAGE_SIZE+2*N_VM) ;
		
	}
	return 0 ;
}

// end of file
