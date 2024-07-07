//
//  common.h
//  Playground
//
//  Created by XU Luyao on 2024/6/23.
//  Copyright © 2024年 XU Luyao. All rights reserved.
//

#ifndef common_h
#define common_h

#include <unistd.h>

void    *debug_malloc(size_t size, const char *file, int line);//malloc leak check only in playground
void    debug_free(void *ptr, const char *file, int line);//malloc leak check only in playground

#define malloc(size) debug_malloc(size, __FILE__, __LINE__)
#define free(ptr) debug_free(ptr, __FILE__, __LINE__)

#endif /* common_h */
