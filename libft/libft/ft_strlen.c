//
//  ft_strlen.c
//  
//
//  Created by XU Luyao on 2024/5/26.
//

#include "ft_strlen.h"
#include <stdio.h>

size_t  ft_strlen(char const *str)
{
    size_t  i = 0;
    
    while (str[i])
        i++;
    return (i);
}
