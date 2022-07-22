#include <common.h>
#include "syscall.h"

int sys_yield(Context *c){
	yield();
//	c->gpr[10] = 0;
	return 0;
}

void do_syscall(Context *c) {
  uintptr_t a[4];
  a[0] = c->GPR1;

  switch (a[0]) {
//	  case 0: break;
	  case 1: sys_yield(c);  break;
      default: panic("Unhandled syscall ID = %d", a[0]);
  }
//  printf("Finished do_syscall!\n");
}
