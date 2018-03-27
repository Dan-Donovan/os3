#ifndef __THREADSFIXED_H__
#define __THREADSFIXED_H__




typedef struct __attribute__ ((packed)) {
  int id; // id value used to compute 2 indexes to compare in each of the rounds for a particular thread
} pthread_arg; //struct that used for each thread in the helper function. 


extern void * bigger_number(void * arg); 




#endif
