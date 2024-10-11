//
//  ft_printf.c
//  Printf
//
//  Created by XU Luyao on 2024/6/7.
//  Copyright © 2024年 XU Luyao. All rights reserved.
//

#include "libft.h"

static int  print_format(const char s, va_list ap);

static int  print_format(const char s, va_list ap)
{
    int i = 0;
    if (s == 'c')
        i = print_char((char)va_arg(ap, int));
    else if (s == 's')
        i = print_string(va_arg(ap, char *));
    else if (s == 'p')
        i = print_pointer(va_arg(ap, unsigned long long));
    else if (s == 'd')
        i = print_int(va_arg(ap, int));
    else if (s == 'i')
        i = print_int(va_arg(ap, int));
    else if (s == 'u')
        i = print_unsigned(va_arg(ap, unsigned int));
    else if (s == 'x')
        i = print_hex(va_arg(ap, unsigned int), 87);
    else if (s == 'X')
        i = print_hex(va_arg(ap, unsigned int), 55);
    return (i);
}

int ft_printf(const char *arg, ...)
{
    va_list ap;
    int count;
    
    va_start(ap, arg);
    count = 0;
    while (*arg)
    {
        if (*arg == '%')
            count += print_format(*(++arg), ap);
        //increase the format pointer and then de-reference it
        else
            count += write(1, arg, 1);
        //the return value of 'write': Upon successful completion the number of bytes which were written is returned.
        ++arg;
    }
    va_end(ap);
    return (count);
}
