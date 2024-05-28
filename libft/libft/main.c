//
//  main.c
//  libft
//
//  Created by XU Luyao on 2024/5/24.
//  Copyright © 2024年 XU Luyao. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "ft_split.h"
#include "ft_memcpy.h"
#include "ft_itoa.h"
#include "ft_strmapi.h"
#include "ft_toggle_case.h"

void test_split(void);
void test_itoa(void);
void test_strmapi(void);

int main()
{
    //test: split
    //test_split();
    
    //test: memcpy
    //test_memcpy();
    
    //test: itoa
    //test_itoa();
    
    //test: strmapi
    test_strmapi();
    
    return (0);
}

void test_split(void)
{
        char const *str = "Hello, how, are, you?";
        char charset = ',';
        char **split_result = ft_split(str, charset);
    
        if (split_result)
        {
            for (int i = 0; split_result[i]; i++)
            {
                printf("Word %d: %s\n", i + 1, split_result[i]);
                free(split_result[i]); // Don't forget to free allocated memory for each word
            }
            free(split_result); // Don't forget to free the array itself
        }
        else
        {
            printf("Error splitting string.\n");
        }
}

void test_memcpy() {
    char src1[] = "Hello World";
    char src2[] = "Hello World";
    //char dest1[50];
    //char dest2[50];
    
    //ft_memcpy(dest1, src, strlen(src) +1);
    //printf("Copied string ft: %s\n", dest1);
    
    //memcpy(dest2, src, strlen(src)+1);
    //printf("Copied string lib: %s\n", dest2);
    
    ft_memcpy(src1 + 7, src1 + 1, 4);
    printf("%s\n", src1);
    memcpy(src2 + 7, src2 + 1, 4);
    printf("%s\n", src2);
}

void test_itoa()
{
    int nbr = -21;
    char *result = ft_itoa(nbr);
    printf("%s\n", result);
}

void test_strmapi(void)
{
    char *original = "Hello, World!";
    char *result = ft_strmapi(original, ft_toggle_case);
    if (result)
    {
        printf("Original: %s\n", original);
        printf("Modified: %s\n", result);
        free(result);
    }
}
