//
//  ft_lstsize.c
//  libft
//
//  Created by XU Luyao on 2024/5/28.
//  Copyright © 2024年 XU Luyao. All rights reserved.
//

#include "ft_lstsize.h"

int ft_lstsize(t_list *lst)
{
    int i = 0;
    while (lst)
    {
        i++;
        lst = lst->next;
    }
    return (i);
}
