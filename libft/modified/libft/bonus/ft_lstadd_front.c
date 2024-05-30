//
//  ft_lstadd_front.c
//  libft
//
//  Created by XU Luyao on 2024/5/28.
//  Copyright © 2024年 XU Luyao. All rights reserved.
//

#include "ft_lstadd_front.h"

void    ft_lstadd_front(t_list **lst, t_list *new)
{
   if (!lst || !new)
       return ;
    new->next = *lst;
    *lst = new;
}
