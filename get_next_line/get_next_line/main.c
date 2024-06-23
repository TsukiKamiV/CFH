//
//  main.c
//  get_next_line
//
//  Created by XU Luyao on 2024/6/17.
//  Copyright © 2024年 XU Luyao. All rights reserved.
//

#include <stdio.h>
#include "get_next_line.h"

int main(int argc, const char * argv[])
{
    int fd;
    int i;
    char *line;
    
    //delete this line before submit
    printf("BufferSize is: %d\n", BUFFER_SIZE);
    
    i = 1;
    fd = open("/Users/Luyao/CFH/get_next_line/get_next_line/test.txt", O_RDONLY);
    while (i < 5)
    {
        printf("get_next_line即将运行第%d次\n", i);
        line = get_next_line(fd);
        printf("结果是：%s\n\n", line);
        i++;
    }
    close (fd);
    return (0);
}
