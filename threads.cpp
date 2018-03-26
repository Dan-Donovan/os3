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
#include <iostream>
#include <sstream>
#include <pthread.h>
#include <math.h>


using namespace std;

/* Global Declarations */








void bigger_number(void * arg){
   thread_arg s = (thread_arg *) arg;
   
   if (arr[s.startIndex] < arr[multiplier*s.endIndex]){
     arr[s.startIndex] = arr[multiplier*s.endIndex];
  }
   
  
  
}
int arr [8200];

int main() {
   
    //general strucutre
    //int arr [8200];
    //Stardard in
    int count = 0;
    cout << "Enter number: ";
   // string input;
    while (getline(cin, arr[count]) && input[0] != '\0')
    {
     // int value = stoi(input);
      
     // cout << input << endl;
     // arr[count] = value;
      //input = "";	
      count += 1;
      cout << "Enter number: ";
    }
    
    pthread_t [count];
    pthread_attr_t attr;
    pthread_attr_init(attr);
    
    pthread_arg = arg[count];
    
    int limit = log(count)
    
    for(int i = 0; i < limit; i++){
      
      if ( i % pow(2,(n+1)) == 0){
	arg[i].startIndex = i;
	arg[i].endIndex = i + pow(2,n)
	pthread_create(&t[i], &attr,bigger_number(),&arg[i])
      }
      
      //barrier
      
      
    }
    
    for (int j = 0; j < count; j++){
      p_thread_join(t[i], 0)
    }
    
    cout << arr[0] << endl;
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

