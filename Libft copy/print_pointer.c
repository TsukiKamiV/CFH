//
//  print_pointer.c
//  Printf
//
//  Created by XU Luyao on 2024/6/11.
//  Copyright © 2024年 XU Luyao. All rights reserved.
//

//#include "ft_printf.h"
//#include <unistd.h>

# include "libft.h"

int    ft_ptr_len(uintptr_t num)
{
    int    len;
    
    len = 0;
    while (num != 0)
    {
        len++;
        num = num / 16;
    }
    return (len);
}

void    ft_put_ptr(uintptr_t num)
{
    if (num >= 16)
    {
        ft_put_ptr(num / 16);
        ft_put_ptr(num % 16);
    }
    else
    {
        if (num <= 9)
            ft_putchar_fd((num + '0'), 1);
        else
            ft_putchar_fd((num - 10 + 'a'), 1);
    }
}

int    ft_print_pointer(unsigned long long ptr)
{
    int    print_length;
    
    print_length = 0;
    print_length += write(1, "0x", 2);
    if (ptr == 0)
        print_length += write(1, "0", 1);
    else
    {
        ft_put_ptr(ptr);
        print_length += ft_ptr_len(ptr);
    }
    return (print_length);
}
