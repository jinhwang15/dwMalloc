//
//  test2.cpp
//
//  Created by Daniel Weyh on 25.05.12.
//  Copyright (c) 2012 HU Berlin. All rights reserved.
//

#include <iostream>

#include <thread>
#include <mutex>
#include <random>
#include <vector>
#include <map>
#include <chrono>

#include "dwMalloc.h"

std::mt19937_64 RNG;
std::mutex RNGMutex;
//std::mutex output;

int M = 50; // repeats per thread
int N = 10; // synchronous threads
int K = 10;  // thread packets
int maxNumbers = 1000;  // max numbers in threads

static bool alreadyPrint = false;

void doSomethingThread(){
  std::mt19937_64* localRNG = new std::mt19937_64();
  
  RNGMutex.lock();
  localRNG->seed(static_cast<unsigned>(RNG()));
  RNGMutex.unlock();
  
  for(int i = 0; i < M; ++i){
    unsigned numNumbers = (static_cast<unsigned>((*localRNG)()) % maxNumbers) + 1;
    
    unsigned* initialNumbers = new unsigned[numNumbers]();
    unsigned* recent = initialNumbers;
    
    for(int i=0; i < numNumbers; ++i){
      *recent = static_cast<unsigned>((*localRNG)());
      ++recent;
    }
    
    recent = new unsigned[numNumbers]();
    memcpy(recent, initialNumbers, numNumbers*sizeof(unsigned));
    
    if(memcmp(recent, initialNumbers, numNumbers*sizeof(unsigned)))
      throw "Fuck";
    
    delete[](initialNumbers);
    delete[](recent);
  }
  
  delete(localRNG);
  return;
}


int main(int argc, char** argv){
  std::chrono::high_resolution_clock hrc;
  RNG.seed((long) &argc);
  
  if (argc > 1)
    M = atoi(argv[1]);
  if (argc > 2)
    N = atoi(argv[2]);
  if (argc > 3)
    K = atoi(argv[3]);
  if (argc > 4)
    maxNumbers = atoi(argv[4]);
  
  std::vector<std::thread> threads;
  threads.reserve(N);
  
  std::chrono::time_point<std::chrono::high_resolution_clock> start = hrc.now();
  
  for (int k = 0; k < K; ++k) {
    for(int i = 0; i < N; ++i){
      try {
        threads.push_back(std::thread(doSomethingThread));
      } catch (std::system_error) {
        ;
      }
    }
    
    for(std::thread &t : threads)
    {
      t.join();
    }
    threads.clear();
  }
  std::cout << M << "\t" << N << "\t" << K << "\t" << maxNumbers << "\t" << (std::chrono::duration_cast<std::chrono::nanoseconds>(hrc.now() - start)).count() << std::endl;
  return 0;
}