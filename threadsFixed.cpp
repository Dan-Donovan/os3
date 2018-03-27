/*
 * Machine Problem #3 - Synchronization with barriers
 * 
 * CS4414 Operating Systems
 * 
 * Dan Donovan
 * 
 * 
 * threadsFixed.cpp - c++ file containing functionality for creating N/2 threads and returning the maximum inputed value
 * Dan Donovan Spring 2018 
 * 
 * The following code display my implementation for finding the maximum value of N inputs using N/2 threads. It includes my chosen implementation for the barrier I use to aid in correct sychronization of threads.
 * 
 * 
 * 	COMPILE: make 
 * 	OBJECTS: threadsFixed.o
 * 	
 * 	HEADERS: threadsFixed.h
 * 
 * 
 * 
 * 	MODIFICATIONS:
 * 		3/25 - Moved comparision calculation logic and calls to barrier to be entirely 		*		within helper function bigger_number(). 
 * 		3/26 - Deleted print statements used for testing, and all other print statements 	*		except for final print statement.
 * 
 * 
 * 
 */

#include "threadsFixed.h"
#include <stdint.h>
#include <stdlib.h>
#include <cstddef>
#include <iostream>
#include <sstream>
#include <pthread.h>
#include <math.h>
#include <unistd.h>
#include <semaphore.h>

using namespace std;

/* Global Declarations */
int * arr; /* Array used to hold all initial inputs, and intermediary and final max values */
int count; /* Number of inputs N */
int thread_count; /* Number of threads used */

/* class for Barrier implementation */
class Barrier{
    
public:
    int value;
    sem_t mutex; /* Binary Semaphores */
    sem_t waitq;
    sem_t throttle;
    int init;

    void setupBS(); /* Initialize Semaphores */
    void set_init(int);
    void set_val(int);
    void wait(); /* wait() method that will be called at each round in helper function */
};
/* function to set the init (threshold) value of the barrier */
void Barrier::set_init(int num){
  init = num;
  
  }
/* function to set the init (threshold) value of the barrier */
void Barrier::set_val(int num){
  value = num;
  
  }

/* function to setup the binary semaphore attributes of the barrier */
void Barrier::setupBS(){
  sem_init(&mutex,0,1); 
  sem_init(&waitq,0,0); /* when first touched, I want it to wait */
  sem_init(&throttle,0,0);
  }

/* void method that waits for all threads before allowing the threads to continue to next round */
void Barrier:: wait(){
  
  /* mutex.wait() (critical section) */
  sem_wait(&mutex); 
  value--;
  /* if some threads haven't made it to the barrier yet */
  if(value != 0){ 
    
    /* wait and signal on various binary semaphores. */
    sem_post(&mutex); 
    sem_wait(&waitq);
    sem_post(&throttle);
    
  }
  
  else{ /* otherwise */
    /* for each of the threads */
    for (int i = 0; i < init -1; i++){
      /* signal the wait queue, and wait on the throttle BS to prevent potential future deadlock */
      sem_post(&waitq);
      sem_wait(&throttle);
    }
    /* reinitialize the barrier by reseting value */
    set_val(init);
   /* signal the mutex to allow it to be used in the next round */
   sem_post(&mutex);
  }
 
}
/* setting up another global, the Barrier barr */
Barrier * barr;
/* void * method that for a particular thread determines for each of the rounds of comparisions whether it will be doing computation, and performs those computations in each round, waiting after each round.  */
void * bigger_number(void * arg){
   /* get a pointer to a thread's arg struct and the value of id */
   pthread_arg * s = (pthread_arg *) arg;
   int tid = s->id;
   
    int log_count = count;
    int limit = 0;
    
    /* compute log2(N), the number of rounds of comparisions */
    while(log_count >>= 1){
      limit++;
    }
    /* for each of the rounds of comparisions */
    for(int i = 0; i < limit; i++){
	/* if a thread's will be computing comparisions in this round */
	if (  (2*tid) % (int) pow(2.0,(double)(i+1)) == 0.0){
	  /* get the two indexes that are to be compared */
	  int startIndex = 2*tid;
	  int endIndex = 2*tid + (int) pow(2.0,(double)i);
	   
	  /* if second index > first index replace first index with SI's value */
	   if (arr[startIndex] < arr[endIndex]){
	    arr[startIndex] = arr[endIndex];
	      }
	}
      /* call to the barrier so a thread waits until all threads have finished the round */
      barr->wait();
      
    }

  
}

/* main method where input and thread creation / joining  occurs */
int main() {
   
    count = 0;
    thread_count = 0;
    /* allocate space for the array to hold the input */
    arr =  (int *) malloc(sizeof(int)*8200);
    
    
    string s;
    bool cont = true;
    /* get the input and put it into an array, and get the number count of inputs */
    while (cont == true)
    {
     getline(cin, s);
     if (s.empty()){
       cont = false;
     }
     else{
       stringstream example(s);
       int value = 0;
       example >> value;
       arr[count] = value;
      count += 1;
     }
   }
   
    /* calculate number of thread counts and initialize various thread arguments */
    thread_count = count /2;
    pthread_t tid[thread_count];
    pthread_attr_t attr;
    pthread_attr_init(&attr); 
    pthread_arg arg[thread_count];
    
    /* create a new Barrier and set its initial values */
    barr = new Barrier();
    barr->set_init(thread_count);
    barr->set_val(thread_count);
    barr->setupBS();
    
    /* for each of the threads */
    for(int k = 0; k < count / 2; k++){
      /* set the struct argument id to appropriate value and call pthread_create */
      arg[k].id = k;
      pthread_create(&tid[k], &attr,bigger_number,&arg[k]);
    }
    
    /* After all rounds and helper function is finished executing*/
    for (int j = 0; j < count / 2; j++){
      /* main thread waits for all sub threads to terminate. */
      pthread_join(tid[j], NULL);
    }
    /* after joining each thread, print the max value to stdout */
    cout << arr[0] << endl;
    
    free(arr);
    free(barr);
    return 0;
    }
   