//
//  ft_lstadd_back.c
//  libft
//
//  Created by XU Luyao on 2024/5/28.
//  Copyright © 2024年 XU Luyao. All rights reserved.
//

#include "ft_lstadd_back.h"

void    ft_lstadd_back(t_list **lst, t_list *new)
{
    if (!lst || !new)
        return ;
    if (*lst)
        ft_lstlast(*lst)->next = new;
    else
        *lst = new;
}
