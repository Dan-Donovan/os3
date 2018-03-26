/*
 * Machine Problem #1 Read-only functionality implementation for FAT16/32
 * 
 * CS4414 Operating Systems
 * 
 * Dan Donovan
 * 
 * 
 * myfat.cpp - c++ file containing functionality for read and write operations for FAT Systems
 * Dan Donovan Spring 2018 
 * 
 * The following code display the conceptual way I would go about implementing the various read and write functionality for FAT16/FAT32 file systems. It includes an idea on how I would have coded the problem and show my understanding for what needs to be done
 * 
 * 
 * 	COMPILE: make 
 * 	OBJECTS: myfat.o, fattester.o
 * 	
 * 	HEADERS: myfat.h
 * 
 * 
 * 
 * 	MODIFICATIONS:
 * 	3/14 -- created a new version of the myfat.cpp and myfat.h files as my previous files on my virtual machine were written over. These files show the function headers and method stubs as well as conceptially what I would have done in each method
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

int * arr;
//pthread_barrier_t mybarrier;
int count;
int thread_count;

class Barrier{
    
public:
    int value;
    sem_t mutex;
    sem_t waitq; //first time want to wait
    sem_t throttle;
    int init;

    void setupBS(); 
    void set_init(int);
    void set_val(int);
    void wait();
};

void Barrier::set_init(int num){
  init = num;
  
  }
void Barrier::set_val(int num){
  value = num;
  
  }
void Barrier::setupBS(){
  sem_init(&mutex,0,1);
  sem_init(&waitq,0,0);
  sem_init(&throttle,0,0);
  }
void Barrier:: wait(){
  
  //cout << "in the wait method! oh boy" << endl;
  sem_wait(&mutex);
  //cout << "first wait is working after the mutex!" << endl;
  value--;
  //cout << "the current value after subtracting is " << value << endl;
  if(value != 0){
//     mutex.signal();
//     waitq.wait();
//     throttle.signal();
    //cout << "testing if sem_post is proper" << endl;
    sem_post(&mutex);
    //cout << " made it here OKAY OKAY" << endl;
    sem_wait(&waitq);
    //cout << "sem wait has changed after the second wait() call" << endl;
    sem_post(&throttle);
    
  }
  
  else{
   // cout << "we are now in the else statement since all threads have finished" << endl;
    for (int i = 0; i < init -1; i++){
//       waitq.signal();
//       throttle.wait();
      sem_post(&waitq);
      sem_wait(&throttle);
    }
    //cout << "made it through for loop :) " << endl;
  // value = init;
    set_val(init);
//    mutex.signal();
  // cout << "------------------------" << endl;
   sem_post(&mutex);
   //cout << "end of wait??" <<endl;
  }
 // cout << "done waiting perchance? " << endl;
}

Barrier * barr;
void * bigger_number(void * arg){
  //cout << "inside the belly of the beast" << endl;
   pthread_arg * s = (pthread_arg *) arg;
   int tid = s->id;
   
    int log_count = count;
    int limit = 0;
    
    while(log_count >>= 1){
      limit++;
    }
    
    for(int i = 0; i < limit; i++){
	
	if (  (2*tid) % (int) pow(2.0,(double)(i+1)) == 0.0){
	  int startIndex = 2*tid;
	  int endIndex = 2*tid + (int) pow(2.0,(double)i);

	   cout << startIndex << "end " << endIndex << endl;
	   if (arr[startIndex] < arr[endIndex]){
	    // cout << "here lol " << endl;
	    cout << arr[startIndex] << "next" << arr[endIndex] << endl;
	    arr[startIndex] = arr[endIndex];
	      }
	}
      barr->wait();
      //pthread_barrier_wait(&mybarrier);
   //   cout << "after barrier" << endl;
    }
 /// cout << "actually going!" << endl;
  //barr.wait();
  
}


int main() {
   

    count = 0;
    thread_count = 0;
    string s;
    arr =  (int *) malloc(sizeof(int)*8200);
   // string input;
    bool cont = true;
    while (cont == true)
    {
     cout << "Enter number: ";
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
    thread_count = count /2;
    pthread_t tid[thread_count];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    
    pthread_arg arg[thread_count];
    
    barr = new Barrier();
    barr->set_init(thread_count);
    barr->set_val(thread_count);
    barr->setupBS();
    cout << "----------------------------" << endl;
    
    for(int k = 0; k < count / 2; k++){
      arg[k].id = k;
      pthread_create(&tid[k], &attr,bigger_number,&arg[k]);
    }
    
    for (int j = 0; j < count / 2; j++){
      pthread_join(tid[j], NULL);
    }
    
      
    cout << "the biggest element is " << arr[0] << endl;
    
    return 0;
    }
    
    //initialize various attributes. Initializes them for a set of standard.
    //pthread_attr_t (what is this lol look up documentation)
    
    //pthread_attr_init[]
  
    //pthread_create() //creates threads to do actual part of the process
  
//     //pthread_join() //main thread waits for all sub threads to terminate.
//   
//   
//   
//     pthread_t[8000];
//     pthread_attr_t attr;
//     pthread_t_init(&attr);
//       
//     
//     pthread_arg arg[num_threads];
//     
// 
//     
  
  
  
 