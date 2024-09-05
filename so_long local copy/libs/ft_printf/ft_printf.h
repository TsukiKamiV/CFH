
#ifndef ft_printf_h
#define ft_printf_h

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include "../libft/libft.h"

int ft_printf(const char *arg, ...);

int print_char(const char c);

int print_string(char *s);

int print_int(int n);

int print_unsigned(unsigned int nb);

int print_hex(unsigned int n, const char fmt);

int print_pointer(unsigned long long ptr);

#endif /* ft_printf_h */
