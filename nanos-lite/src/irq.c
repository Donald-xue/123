#include <common.h>
#include <stdio.h>

extern void do_syscall(Context *c);
Context* schedule(Context *prev);

static Context* do_event(Event e, Context* c) {
  switch (e.event) {
	  case EVENT_YIELD: //printf("Get an EVENT_YIELD!\n"); 
						return schedule(c);
						break;
	  case EVENT_SYSCALL: //printf("Get an EVENT_SYSCALL!\t");
						  do_syscall(c);
						  break;
	  case EVENT_IRQ_TIMER:
	                      return c;
	                      //return schedule(c);
	                      break;
	  default: panic("Unhandled event ID = %d", e.event);
  }
//  printf("Finished do_evext!\n");
  return c;
}

void init_irq(void) {
  Log("Initializing interrupt/exception handler...");
  cte_init(do_event);
}
