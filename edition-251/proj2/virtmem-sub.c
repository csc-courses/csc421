#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<assert.h>
#include <ctype.h>

#include "virtmem.h"

/*
 * template-author:  bjr
 * template-update:
 *		4 sep 2024 -bjr: 
 * 
 * this is a template. change "author" and continue work
 *
 * student-author: 
 * update: 
 *
 * student pledge: this is my own work, unless otherwise noted
 *		
 */


// the code you are to write is found below the following 
// provided code blocks

// the constructors 

struct PhysicalMemory * create_physicalmemory() {
	struct PhysicalMemory * pm ;
	pm = (struct PhysicalMemory *) malloc(sizeof(struct PhysicalMemory)) ;
	//pm->memory = (char *) malloc(MEMORY_SIZE) ;
	pm->memory = (char *) aligned_alloc(PAGE_SIZE, MEMORY_SIZE) ;
	for (int i=0; i<MEMORY_SIZE; i++) pm->memory[i] = '\0' ;
	pm->next_free_page = pm->memory ;
	return pm ;
}

struct VirtualMemory * create_virtualmemory(struct PhysicalMemory * pm) {
	struct VirtualMemory * vm ;
	vm = (struct VirtualMemory *) malloc(sizeof(struct VirtualMemory)) ;
	vm->pm = pm ;
	for (int i =0; i<PAGE_TABLE_SIZE; i++) vm->ptes[i] = NULL ;
	return vm ;
}


// how to update the page tables to map a new virtual page frame

int allocate_page(struct VirtualMemory * vm, int address) {
	int page = (address & PAGE_MASK) >> 9 ;
	vm->ptes[page] = vm->pm->next_free_page ;
	vm->pm->next_free_page += PAGE_SIZE ;
	return 0 ;
}

// diagnostic write routines for the data structures

void pmem_dump(struct PhysicalMemory * pm, int limit) {
	assert( limit<=MEMORY_SIZE ) ;
	for (int i=0; i<limit; i++) 
		putchar(pm->memory[i]) ;
}

void pte_dump(struct VirtualMemory * vm, int limit ) {
	assert( limit<=PAGE_TABLE_SIZE ) ;
	for (int i=0; i<limit; i++) 
		printf("%d\t%p\n", i, vm->ptes[i]) ;
}

// reading and writing a character into virtual memory

char vm_read_char(struct VirtualMemory * vm, int v_addr) {
	char * c_p = mmu_map(vm, v_addr) ;
	return *c_p ;
}

void vm_write_char(struct VirtualMemory * vm, int v_addr, char ch) {
	char * c_p = mmu_map(vm, v_addr) ;
	if (is_verbose>1) {
		char c_ch = (isprint(ch))?ch:'_' ;
		printf("(%s,%d): vm: %p, v_addr: %d, char: %c, c_p: %p\n", __FILE__, __LINE__, vm,v_addr, c_ch, c_p) ;
	}
	*c_p = ch ;
	return ;
}


// the code you need to write is bellow this line 


char * mmu_map(struct VirtualMemory * vm, int v_addr) {

// this is where you do most of your work
// calculate the proper char * that points to memory at
// the virtual address v_addr in the virtual memory space vm

	return NULL ;
}


int vm_read_str(struct VirtualMemory * vm, int v_addr, char * s, int len ) {

// read a string from the virtual memory; beginning at virtual address v_addr, 
// in the virtual memory space vm, into the memory location s, not more than
// len characters including the null byte terminator

	return 0 ;
}

void vm_write_str(struct VirtualMemory * vm, int v_addr, char * s) {

// write a string into the virtual memory; beginning at virtual address v_addr, 
// in the virtual memory space vm, from  string at memory location s

	return ;
}

//end of file

