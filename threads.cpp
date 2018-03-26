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

#include "threads.h"
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
pthread_barrier_t mybarrier;
//Barrier barr;

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
  //cout << "init for barrier is " << init << endl;
  }
void Barrier::set_val(int num){
  value = num;
  //cout << "value for barrier is " << value << endl;
  }
void Barrier::setupBS(){
  sem_init(&mutex,0,1);
  sem_init(&waitq,0,0);
  sem_init(&throttle,0,0);
  }
void Barrier:: wait(){
  //mutex.wait();
  cout << "in the wait method! oh boy" << endl;
  sem_wait(&mutex);
  cout << "first wait is working after the mutex!" << endl;
  value--;
  cout << "the current value after subtracting is " << value << endl;
  if(value != 0){
//     mutex.signal();
//     waitq.wait();
//     throttle.signal();
    cout << "testing if sem_post is proper" << endl;
    sem_post(&mutex);
    cout << " made it here OKAY OKAY" << endl;
    sem_wait(&waitq);
    cout << "sem wait has changed after the second wait() call" << endl;
    sem_post(&throttle);
    
  }
  
  else{
    cout << "we are now in the else statement since all threads have finished" << endl;
    for (int i = 0; i < init -1; i++){
//       waitq.signal();
//       throttle.wait();
      sem_post(&waitq);
      sem_wait(&throttle);
    }
    cout << "made it through for loop :) " << endl;
  // value = init;
    set_val(init);
//    mutex.signal();
  // cout << "------------------------" << endl;
   sem_post(&mutex);
   cout << "end of wait??" <<endl;
  }
  cout << "done waiting perchance? " << endl;
}


void * bigger_number(void * arg){
  //cout << "inside the belly of the beast" << endl;
   pthread_arg * s = (pthread_arg *) arg;
   //int multiplier = s->multiplier;
   cout << s->startIndex << "end " << s->endIndex << endl;
   if (arr[s->startIndex] < arr[s->endIndex]){
    // cout << "here lol " << endl;
     cout << arr[s->startIndex] << "next" << arr[s->endIndex] << endl;
     arr[s->startIndex] = arr[s->endIndex];
  }
  //cout << "here?" << endl;
  cout << "resulting VALUE is " << arr[s->startIndex] << endl;
  //pthread_barrier_wait(&mybarrier);
 /// cout << "actually going!" << endl;
  //barr.wait();
  return 0;
}

// void * fake(void * arg){
//   cout << "fake doing nothing" << endl;
//  // pthread_barrier_wait(&mybarrier);
//   cout << "im going!" << endl;
//   return 0;
// }


int main() {
   

    int count = 0;
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
    
    pthread_t tid[count /2];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    
    pthread_arg arg[count / 2];
    
    Barrier barr;
    barr.set_init(count / 2);
    barr.set_val(count / 2);
    barr.setupBS();
    
    pthread_barrier_t mybarrier;
    pthread_barrier_init(&mybarrier, NULL, (count /2) - 1);
    int log_count = count;
    int limit = 0;
    
    while(log_count >>= 1){
      limit++;
    }
    
    //cout << "count is " << count << " limit is " << limit << endl;
    
    cout << "----------------------------" << endl;
    for(int i = 0; i < limit; i++){
      barr.set_init(count / 2);
      barr.setupBS();
      cout << "i equals " << i << endl;
      for(int k = 0; k < count / 2; k++){
	
	if (  (2*k) % (int) pow(2.0,(double)(i+1)) == 0.0){
	  arg[k].startIndex = 2*k;
	  arg[k].endIndex = 2*k + (int) pow(2.0,(double)i);
	//  cout << arg[k].startIndex << "This is the start index" << endl;
	  //arg[i].multiplier = i;
	  if (i == 0){
	    cout << "CREATING NEW THREAD" << endl;
	    pthread_create(&tid[k], &attr,bigger_number,&arg[k]);
	    
	  //  cout << "something is wrong" << endl;
	  }
	  else{
	    cout << "using old threads" << endl;
	   bigger_number(&arg[k]); 
	  }
	}
	
	else{
// 	  if (i == 0){
// 	    cout << "CREATING NEW BAD THREAD" << endl;
// 	    pthread_create(&tid[k], &attr,fake,&arg[k]);
// 	    cout << "waiting" << endl;
// 	  }
// 	  
// 	  else{
// 	    cout << "using same dummy threads" << endl;
// 	   fake(&arg[k]);
// 	  }
	  cout << "Thread is doing no calculations" << endl;  
	  
	}

// 	usleep(3000000);

	barr.wait();
      }
    
     
      
    }
    cout << "---------------- " << endl;
    
    for (int j = 0; j < count / 2; j++){
      pthread_join(tid[j], NULL);
    }
    
      
    cout << "the biggest element is " << arr[0] << endl;
    //initialize array of size p
    //pthread_t [8000];
    
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
  
  
  
  return 0;
}

