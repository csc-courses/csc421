/*
 * author: bjr
 * update:
 *	 31 aug 2024 -bjr: created
 *	  4 sep 2024 -bjr: 
 */

#ifndef _VIRTMEM_H
#define _VIRTMEM_H 1

#define PAGE_MASK 0xfe00
#define OFFSET_MASK 0x01ff

#define MEMORY_SIZE 65536u
#define PAGE_SIZE 512
#define N_PAGE_TABLES 4 
#define PAGE_TABLE_SIZE (MEMORY_SIZE/PAGE_SIZE)

struct PhysicalMemory {
	char * memory ;
	char * next_free_page ;
} ;

struct VirtualMemory {
	struct PhysicalMemory * pm ;
	char * ptes[PAGE_TABLE_SIZE] ;
} ;

extern int g_debug ;
extern int is_verbose ;

struct PhysicalMemory * create_physicalmemory(void) ;
struct VirtualMemory * create_virtualmemory(struct PhysicalMemory * pm) ;
void pmem_dump(struct PhysicalMemory * pm, int limit ) ;
void pte_dump(struct VirtualMemory * vm, int limit ) ;
char * mmu_map(struct VirtualMemory * vm, int v_addr) ;
int allocate_page(struct VirtualMemory * vm, int v_addr) ;
char vm_read_char(struct VirtualMemory * vm, int v_addr) ;
void vm_write_char(struct VirtualMemory * vm, int v_addr, char ch) ;
int vm_read_str(struct VirtualMemory * vm, int v_addr, char * s, int len ) ;
void vm_write_str(struct VirtualMemory * vm, int v_addr, char * s) ;

#endif

// end of file
