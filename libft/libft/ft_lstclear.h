//
//  ft_lstclear.h
//  libft
//
//  Created by XU Luyao on 2024/5/28.
//  Copyright © 2024年 XU Luyao. All rights reserved.
//

#ifndef ft_lstclear_h
#define ft_lstclear_h

#include <stdio.h>
#include <stdlib.h>
#include "t_list.h"
void    ft_lstclear(t_list **lst, void (*del)(void *));

#endif /* ft_lstclear_h */
