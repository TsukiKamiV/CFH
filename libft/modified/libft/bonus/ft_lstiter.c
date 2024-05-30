//
//  ft_lstiter.c
//  libft
//
//  Created by XU Luyao on 2024/5/28.
//  Copyright © 2024年 XU Luyao. All rights reserved.
//

#include "ft_lstiter.h"

void    ft_lstiter(t_list *lst, void (*f)(void *))
{
    while (lst && f)
    {
        f(lst->content);
        lst = lst->next;
    }
}
