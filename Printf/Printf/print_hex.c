//
//  print_hex.c
//  Printf
//
//  Created by XU Luyao on 2024/6/11.
//  Copyright © 2024年 XU Luyao. All rights reserved.
//

#include "ft_printf.h"

void    put_hex(unsigned int n, const char fmt);
int hex_len(unsigned int n);

int hex_len(unsigned int n)
{
    int count = 0;
    while (n)
    {
        n /= 16;
        count++;
    }
    return (count);
}

void    put_hex(unsigned int n, const char fmt)
{
    if (n >= 16)
    {
        put_hex(n / 16, fmt);
        put_hex(n % 16, fmt);
    }
    else
    {
        if (n <= 9)
            ft_putchar_ft(n + '0', 1)
        else
        {
            if (fmt == 'x')
                ft_putchar_fd((n - 10 + 'a'), 1);
            if (fmt == 'X')
                ft_putchar_fd((n - 10 + 'A'), 1);
        }
    }
}

int print_hex(unsigned int n, const char fmt)
{
    if (n == 0)
        return (write(1, "0", 1));
    else
        put_hex(n, fmt);
    return (hex_len(n));
}
