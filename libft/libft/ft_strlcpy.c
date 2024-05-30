//
//  ft_strlcpy.c
//  libft
//
//  Created by XU Luyao on 2024/5/30.
//  Copyright © 2024年 XU Luyao. All rights reserved.
//

#include "ft_strlcpy.h"

size_t  ft_strlcpy(char *dest, const char *src, size_t size)
{
    size_t  i;
    size_t  s_len;
    
    s_len = ft_strlen(src);
    if (size > 0)
    {
        i = 0;
        while (i < size -1 && src[i])
        {
            dest[i] = src[i];
            i++;
        }
        dest[i] = '\0';
    }
    return (s_len);
}
