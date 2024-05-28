//
//  ft_putchar_fd.c
//  libft
//
//  Created by XU Luyao on 2024/5/27.
//  Copyright © 2024年 XU Luyao. All rights reserved.
//

#include "ft_putchar_fd.h"
#include <unistd.h>

void    ft_putchar_fd(char c, int fd)
{
    write(fd, &c, 1);
}
