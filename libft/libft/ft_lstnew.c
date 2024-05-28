//
//  ft_lstnew.c
//  libft
//
//  Created by XU Luyao on 2024/5/28.
//  Copyright © 2024年 XU Luyao. All rights reserved.
//

#include "ft_lstnew.h"
#include <stdlib.h>
#include <fcntl.h>

t_list  *ft_lstnew(void *content)
{
    t_list  *new;
    
    new = malloc(sizeof(t_list));
    if (!new)
        return (NULL);
    new->content = content;
    new->next = NULL;
    return (new);
}
