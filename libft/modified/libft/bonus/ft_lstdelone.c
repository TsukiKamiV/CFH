//
//  ft_lstdelone.c
//  libft
//
//  Created by XU Luyao on 2024/5/28.
//  Copyright © 2024年 XU Luyao. All rights reserved.
//

#include "ft_lstdelone.h"

void    ft_lstdelone(t_list *lst, void (*del)(void *))
{
    if (!lst)
        return ;
    if (del)
        del(lst->content);
    free(lst);
}
