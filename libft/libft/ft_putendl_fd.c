//
//  ft_putendl_fd.c
//  libft
//
//  Created by XU Luyao on 2024/5/27.
//  Copyright © 2024年 XU Luyao. All rights reserved.
//

#include "ft_putendl_fd.h"
#include <unistd.h>
#include "ft_strlen.h"

void    ft_putendl(char *s, int fd)
{
    write(fd, s, ft_strlen(s));
    write(fd, "\n", 1);
}
