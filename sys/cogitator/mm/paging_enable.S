.section .text
.globl paging_enable
.type paging_enable, @function
paging_enable:
  movl 4(%esp), %eax /* eax = page_dir */
  movl %eax, %cr3 /* CR3 = page directory phys addr */
  movl %cr0, %eax
  orl $0x80000000, %eax /* set PG bit */
  movl %eax, %cr0

  ret
