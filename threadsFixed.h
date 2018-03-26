#ifndef __THREADSFIXED_H__
#define __THREADSFIXED_H__




typedef struct __attribute__ ((packed)) {
  int id;
} pthread_arg;


extern void * bigger_number(void * arg);




#endif
