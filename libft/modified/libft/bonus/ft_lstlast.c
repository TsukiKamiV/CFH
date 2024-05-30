//
//  ft_lstlast.c
//  libft
//
//  Created by XU Luyao on 2024/5/28.
//  Copyright © 2024年 XU Luyao. All rights reserved.
//

#include "ft_lstlast.h"

t_list *ft_lstlast(t_list *lst)
{
    while (lst && lst->next)
        lst = lst->next;
    return (lst);
}
