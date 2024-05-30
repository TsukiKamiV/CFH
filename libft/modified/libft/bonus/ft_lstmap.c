//
//  ft_lstmap.c
//  libft
//
//  Created by XU Luyao on 2024/5/28.
//  Copyright © 2024年 XU Luyao. All rights reserved.
//

#include "ft_lstmap.h"

t_list  *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
    t_list *ret;
    t_list  *iter;
    
    if (lst && f && del)
    {
        ret = ft_lstnew(f(lst->content));
        iter = ret;
        while (lst && lst->next)
        {
            if (iter)
            {
                iter->next = ft_lstnew(f(lst->next->content));
                iter = iter->next;
                lst = lst->next;
            }
            return (ret);
        }
    }
    return (NULL);
}
