
#ifndef ft_printf_h
#define ft_printf_h

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include "libft.h"

int ft_printf(const char *fmt, ...);

int print_char(char const c);

int print_string(const char *s);

int print_int(int n);

int print_unsigned(unsigned int nb);

int print_hex(unsigned int n, const char fmt);

int print_ptr(unsigned long long ptr);

#endif /* ft_printf_h */
