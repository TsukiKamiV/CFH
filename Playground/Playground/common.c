//
//  common.c
//  Playground
//
//  Created by XU Luyao on 2024/6/23.
//  Copyright © 2024年 XU Luyao. All rights reserved.
//

#include "common.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#undef malloc
#undef free

void    *debug_malloc(size_t size, const char *file, int line)
{
    void *ptr = malloc(size);
    printf("Malloc: %p, size: %zu, at %s:%d\n", ptr, size, file, line);
    return ptr;
}

void    debug_free(void *ptr, const char *file, int line)
{
    free(ptr);
    printf("Free: %p, at %s:%d\n", ptr, file, line);
}
