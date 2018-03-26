#ifndef __THREADS_H__
#define __THREADS_H__




typedef struct __attribute__ ((packed)) {
  //int id;
  int startIndex;
  int endIndex;
  int multiplier;
} pthread_arg;


extern void * bigger_number(void * arg);




#endif
