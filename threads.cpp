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


using namespace std;

/* Global Declarations */

int * arr;






void * bigger_number(void * arg){
  cout << "inside the belly of the beast" << endl;
   pthread_arg * s = (pthread_arg *) arg;
   //int multiplier = s->multiplier;
   cout << s->startIndex << "end " << s->endIndex << endl;
   if (arr[s->startIndex] < arr[s->endIndex]){
     cout << "here lol " << endl;
     cout << arr[s->startIndex] << "next" << arr[s->endIndex] << endl;
     arr[s->startIndex] = arr[s->endIndex];
  }
  cout << "here?" << endl;
  cout << arr[s->startIndex] << endl;
  
  return 0;
}


int main() {
   
    //general strucutre
    //int arr [8200];
    //Stardard in
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
     // int value = stoi(input);
      count += 1;
     }
     
    }
    
    pthread_t tid[count];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    
    pthread_arg arg[count];
    
    int log_count = count;
    int limit = 0;
    
    while(log_count >>= 1){
      limit++;
    }
    cout << "count is " << count << " limit is " << limit << endl;
    for(int i = 0; i < limit; i++){
      cout << "i equals " << i << endl;
      for(int k = 0; k < count; k++){
	
	if (  k % (int) pow(2.0,(double)(i+1)) == 0.0){
	  arg[k].startIndex = k;
	  arg[k].endIndex = k + (int) pow(2.0,(double)i);
	  cout << arg[k].startIndex << "This is the start index" << endl;
	  //arg[i].multiplier = i;
	  pthread_create(&tid[k], &attr,bigger_number,&arg[k]);
	  cout << "something is wrong" << endl;
	}
	else{
	  cout << "waiting" << endl;
	}
	//barrier
	cout << "no way jose" << endl;
	
      }
    }
    cout << "what the heck? " << endl;
    
    for (int j = 0; j < count; j++){
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

