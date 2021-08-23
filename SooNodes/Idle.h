// (c) Dominique Attali 2003 (LIS)

#ifndef __IDLE_H
#define __IDLE_H

extern void SetIdle(); 
extern void SetIdle(void (*cb)(void *), void * data);
extern void SetNoIdle();

#endif
