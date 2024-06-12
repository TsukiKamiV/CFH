//
//  print_int.c
//  Printf
//
//  Created by XU Luyao on 2024/6/7.
//  Copyright © 2024年 XU Luyao. All rights reserved.
//

#include "ft_printf.h"
#include <stdlib.h>

// Function to print an integer and return its length
int print_int(int n)
{
    long nbr;
    int i;
    char *str;
    
    if (n >= 0)
    {
        i = 1;
        nbr = n;
    }
    else
    {
        i = 2;
        nbr = -n;
    }
    
    // Use ft_itoa to convert the number to a string
    str = ft_itoa(n);
    if (!str)
        return 0;
    
    // Print the string representation of the number
    ft_putstr_fd(str, 1);
    
    // Free the allocated memory for the string
    free (str);
    
    // Count the digits in the number
    while (nbr >= 10) {
        nbr = nbr / 10;
        i++;
    }
    
    return (i);
}

