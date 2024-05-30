//
//  ft_lstclear.c
//  libft
//
//  Created by XU Luyao on 2024/5/28.
//  Copyright © 2024年 XU Luyao. All rights reserved.
//

#include "ft_lstclear.h"

void    ft_lstclear(t_list **lst, void (*del)(void *))
{
    if (lst && (*lst) && del)
    {
        if ((*lst)->next)
        {
            ft_lstclear((&(*lst)->next), del);
        }
        del((*lst)->content);
        free(*lst);
        *lst = NULL;
    }
}
