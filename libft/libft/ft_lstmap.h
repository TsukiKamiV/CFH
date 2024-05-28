//
//  ft_lstmap.h
//  libft
//
//  Created by XU Luyao on 2024/5/28.
//  Copyright © 2024年 XU Luyao. All rights reserved.
//

#ifndef ft_lstmap_h
#define ft_lstmap_h

#include <stdio.h>
#include "t_list.h"
#include "ft_lstnew.h"

t_list  *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif /* ft_lstmap_h */
