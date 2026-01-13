#include <cog/paging.h>

#define ENTRY_SIZE 1024

uint32_t page_directory[ENTRY_SIZE]
__attribute__((aligned(4096)));

uint32_t first_page_table[1024]
__attribute__((aligned(4096)));

extern void paging_enable(uint32_t* pd);

void paging_init() {
  for (int i = 0; i < ENTRY_SIZE; i++) {
    /*This sets the following flags to the pages:
      Supervisor: Only kernel-mode can access them
      Write Enabled: It can be both read from and written to
      Not Present: The page table is not present*/
    page_directory[i] = 0x00000002;
  }

  // Identity Map 4 MiB => PTE[i] = phys=i*4096 | Present | RW
  for (int i = 0; i < ENTRY_SIZE; i++) {
  first_page_table[i] = (i * 0x1000) | 0x3; // present | writable
  }
  page_directory[0] = ((uint32_t)first_page_table) | 0x3;

  paging_enable(page_directory);
}
