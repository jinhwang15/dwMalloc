//
//  test3.cpp
//  dwMalloc
//
//  Created by Daniel Weyh on 05.07.12.
//  Copyright (c) 2012 HU Berlin. All rights reserved.
//

#include <iostream>
#include "dwMalloc.h"
#include <thread>
#include <vector>

void doThings(){
  void* bla = dwmalloc::malloc(10);
  dwmalloc::free(bla);
  return;
}

int main(int argc, char** argv){
  
  void* bla = dwmalloc::malloc(10);
  dwmalloc::free(bla);
  
  std::vector<std::thread> threads;
  
  for(int j = 0; j < 10; j++){
    
    for(int i = 0; i < 10+j; i++){
      threads.push_back(std::thread(doThings));
    }

    for(std::thread& tr : threads){
      tr.join();
    }
    threads.clear();
  }
  std::cout << "hi there" << std::endl;
  
  return 0;
}