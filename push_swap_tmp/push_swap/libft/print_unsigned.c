//
//  print_unsigned.c
//  Printf
//
//  Created by XU Luyao on 2024/6/7.
//  Copyright © 2024年 XU Luyao. All rights reserved.
//

#include "libft.h"

static void put_unsigned(unsigned int nb)
{
    if (nb > 9)
        put_unsigned(nb / 10);
    if (nb <= 9)
    {
        ft_putchar_fd(nb + 48, 1);
        return ;
    }
    ft_putchar_fd((nb % 10) + 48, 1);
}

int print_unsigned(unsigned int nb)
{
    unsigned int    i;
    
    put_unsigned(nb);
    i = 1;
    while (nb > 9)
    {
        nb = nb / 10;
        i++;
    }
    return (i);
}
