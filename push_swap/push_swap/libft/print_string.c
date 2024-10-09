//
//  print_string.c
//  Printf
//
//  Created by XU Luyao on 2024/6/7.
//  Copyright © 2024年 XU Luyao. All rights reserved.
//

#include "libft.h"

int print_string(char *s)
{
    unsigned int    i;
    
    if (!s)
    {
        ft_putstr_fd(("null"), 1);
        return (6);
    }
    i = ft_strlen(s);
    ft_putstr_fd(s, 1);
    return (i);
}
