//
//  ft_putstr_fd.c
//  libft
//
//  Created by XU Luyao on 2024/5/27.
//  Copyright © 2024年 XU Luyao. All rights reserved.
//

#include "ft_putstr_fd.h"
#include <unistd.h>
#include "ft_strlen.h"
void    ft_putstr_fd(char *s, int fd)
{
    if (!s)
        return ;
    write(fd, s, ft_strlen(s));
}
