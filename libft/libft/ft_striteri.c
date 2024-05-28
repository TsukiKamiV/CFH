//
//  ft_striteri.c
//  libft
//
//  Created by XU Luyao on 2024/5/27.
//  Copyright © 2024年 XU Luyao. All rights reserved.
//

#include "ft_striteri.h"

void    ft_striteri(char *s, void(*f)(unsigned int, char *))
{
    unsigned int i;
    
    i = 0;
    if (!s || !f)
        return;
    while (s[i])
    {
        f(i, &s[i]);
        i++;
    }
}
