//
//  main.cpp
//  test1
//
//  Created by Daniel Weyh on 01.07.12.
//  Copyright (c) 2012 HU Berlin. All rights reserved.
//

#include <iostream>
#include <thread>
#include "dwMalloc.h"

#define NTHREADS 20

#include <mutex>
std::mutex outputMutes;

void doNothing(){
  void* bla = dwmalloc::malloc(10000);
  dwmalloc::free(bla);
}

int main(int argc, const char * argv[])
{

  std::thread myThreads[NTHREADS];
  
  for(int i = 0; i < NTHREADS; i++){
    myThreads[i] = std::thread(doNothing);
  }
  
  for(int i = 0; i < NTHREADS; i++){
    myThreads[i].join();
  }
  
  std::cout << "success";
  return 0;
}

