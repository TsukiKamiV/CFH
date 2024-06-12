//
//  ft_printf.c
//  Printf
//
//  Created by XU Luyao on 2024/6/7.
//  Copyright © 2024年 XU Luyao. All rights reserved.
//

#include <unistd.h>
#include <stdarg.h>
#include "ft_printf.h"
#include "libft.h"

static int  print_format(const char *s, void *arg);

static int  print_format(const char *s, void *arg)
{
    int i = 0;
    if (*s == 'c')
        i += print_char((int)arg);
    else if (*s == 's')
        i += print_string((char *)arg);
    else if (*s == 'p')
        i += print_pointer((unsigned long)arg, 87);
    else if (*s == 'd')
        i += print_int((int)arg);
    else if (*s == 'i')
        i += print_int((int)arg);
    else if (*s == 'u')
        i += print_unsigned((unsigned int)arg);
    else if (*s == 'x')
        i += print_hex((unsigned int)arg, 87);
    else if (*s == 'X')
        i += print_hex((unsigned int)arg, 55);
    return (i);
}

int ft_printf(const char *fmt, ...)
{
    va_list ap;
    int count;
    
    va_start(ap, fmt);
    count = 0;
    while (*fmt)
    {
        if (*fmt == '%')
            count += print_fmt(*(++fmt), ap);
        //increase the format pointer and then de-reference it
        else
            count += write(1, fmt, 1);
        //the return value of 'write': Upon successful completion the number of bytes which were written is returned.
        ++fmt;
    }
    return (count);
}
