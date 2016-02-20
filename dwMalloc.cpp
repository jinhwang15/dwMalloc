//
//  dwMalloc.cpp
//  dwMalloc
//
//  Created by Daniel Weyh on 01.07.12.
//  Copyright (c) 2012. All rights reserved.
//

#include <thread>
#include <map>
#include <mutex>

#include "malloc-2.8.3.h"
#include "dwMalloc.h"

#ifdef _WIN32
#define thread_local __declspec(thread)
#else
#define thread_local __thread
#endif

namespace dwmalloc {
  mspace mspaces[N_MSPACES];
  bool everUsed = 0;
  short lastMspace = 0;

  thread_local short mspaceId = -1;
  std::mutex initMutex;
      
  void inline initTheSpaces(){
    for(int i = 0; i < N_MSPACES; i++)
      mspaces[i] = create_mspace(0, 1);
  }
  
  void* malloc(size_t size){
    if(!everUsed){
	    initMutex.lock();
      if (!everUsed) {
        initTheSpaces();
        everUsed = true;
      }
      initMutex.unlock();
    }
    
    if ( mspaceId < 0 ) {
      mspaceId = (lastMspace+1) % N_MSPACES;

      initMutex.lock();
      lastMspace = mspaceId;
      initMutex.unlock();
      
      return mspace_malloc(mspaces[ mspaceId ], size);
    }
        
	return mspace_malloc(mspaces[ mspaceId ], size);
  }

  void inline free(void* ptr){
    mspace_free( mspaces[ mspaceId ], ptr );
  }
  
}


//scalar, throwing new and it matching delete
void* operator new (std::size_t size) throw(std::bad_alloc)
{
  return dwmalloc::malloc(size);
} 

void operator delete (void* ptr) throw()
{
  dwmalloc::free(ptr);
}


//scalar, nothrow new and it matching delete
void* operator new (std::size_t size,const std::nothrow_t&) throw()
{
  return dwmalloc::malloc(size);
}; 


void operator delete (void* ptr, const std::nothrow_t&) throw()
{
  dwmalloc::free(ptr);
}; 

//array throwing new and matching delete[]
void* operator new  [](std::size_t size) throw(std::bad_alloc)
{
  return dwmalloc::malloc(size);
}; 
void operator delete[](void* ptr) throw()
{
  dwmalloc::free(ptr);
}; 

//array, nothrow new and matching delete[]
void* operator new [](std::size_t size, const std::nothrow_t&) throw()
{
  return dwmalloc::malloc(size);
}; //array nothrow new
void operator delete[](void* ptr, const std::nothrow_t&) throw()
{
  dwmalloc::free(ptr);
};//matching delete[]


