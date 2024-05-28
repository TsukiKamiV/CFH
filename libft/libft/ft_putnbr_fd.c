//
//  ft_putnbr_fd.c
//  libft
//
//  Created by XU Luyao on 2024/5/27.
//  Copyright © 2024年 XU Luyao. All rights reserved.
//

#include "ft_putnbr_fd.h"
#include <unistd.h>
#include "ft_putchar_fd.h"

static void print_nbr(long nb, int fd)
{
    if (nb / 10)
    {
        print_nbr(nb / 10, fd);
        print_nbr(nb % 10, fd);
    }
    else
        ft_putchar_fd(nb + '0', fd);
}
void    ft_putnbr_fd(int n, int fd)
{
    long    nb;
    
    nb = n;
    if (nb < 0)
    {
        write(fd, "-", 1);
        nb = -nb;
    }
    print_nbr(nb, fd);
}
