#include <am.h>
#include <riscv/riscv.h>
#include <klib.h>

static Context* (*user_handler)(Event, Context*) = NULL;

Context* __am_irq_handle(Context *c) {
/*	for(int i = 0; i < 32; i++){
		printf("gpr(%d) = %x\n", i, c->gpr[i]);
	}
*/	
//	printf("%x %x %x\n", c->mcause, c->mstatus, c->mepc);
  if (user_handler) {
    Event ev = {0};
    switch (c->mcause) {
		case 0xffffffff: ev.event = EVENT_YIELD; break;
		case 0:
		case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:    
		case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
						 ev.event = EVENT_SYSCALL; break;
		default: ev.event = EVENT_ERROR; break;
    }
    c = user_handler(ev, c);
    assert(c != NULL);
  }
//  printf("Finished __am_irq_handle!\n");
  return c;
}

extern void __am_asm_trap(void);

bool cte_init(Context*(*handler)(Event, Context*)) {
  // initialize exception entry
  asm volatile("csrw mtvec, %0" : : "r"(__am_asm_trap));
//  printf("Initializing CTE...");

  // register event handler
  user_handler = handler;

  return true;
}

Context *kcontext(Area kstack, void (*entry)(void *), void *arg) {
  return NULL;
}

void yield() {
  asm volatile("li a7, -1; ecall");
//  printf("Finished yield!\n");
}

bool ienabled() {
  return false;
}

void iset(bool enable) {
}
