//
//  dwMalloc.h
//  dwMalloc
//
//  Created by Daniel Weyh on 01.07.12.
//  Copyright (c) 2012. All rights reserved.
//

#ifndef dwMalloc_dwMalloc_h
#define dwMalloc_dwMalloc_h

#ifndef N_MSPACES
#define N_MSPACES 10
#endif

namespace dwmalloc {
      
  void* malloc(size_t size);
  void free(void* ptr);
      
}

#endif
