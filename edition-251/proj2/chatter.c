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

#define USAGE_MESSAGE "usage: chatter [-t -v...]"
#define N_VM 4

int main(int argc, char * argv[]) {
	int ch ;
	int i, j ;
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
		
		// create N_VM virtual memory spaces
		pm = create_physicalmemory() ;
		for (i=0; i<N_VM; i++) {
			vm_s[i] = create_virtualmemory(pm) ;
		}
		
		// allocate N_VM pages in each of the N_VM spaces
		for (i=0; i<N_VM; i++) {
			for (j=0; j<N_VM; j++) {
				allocate_page(vm_s[j],i*PAGE_SIZE) ;
			}
		}
		
		// print page tables
		if (print_page_tables) for (i=0; i<N_VM; i++) {
			printf("\nvirtual space %d:\n",i) ;
			pte_dump(vm_s[i], 8) ;
			printf("\n") ;
		}
		
		// fill up virtual memory, a different character
		// for each vm space
		for (i=0; i<N_VM; i++) {
			for (j=0; j<(N_VM*PAGE_SIZE); j++) {
				vm_write_char(vm_s[i],j,'A'+i) ;
			}
		}
		
		// print physical memory
		pmem_dump(pm, N_VM*N_VM*PAGE_SIZE+2*N_VM) ;
		
	}
	return 0 ;
}

// end of file
