//
//  ft_lstdelone.h
//  libft
//
//  Created by XU Luyao on 2024/5/28.
//  Copyright © 2024年 XU Luyao. All rights reserved.
//

#ifndef ft_lstdelone_h
#define ft_lstdelone_h

#include <stdio.h>
#include <stdlib.h>
#include "t_list.h"

void    ft_lstdelone(t_list *lst, void (*del)(void *));
#endif /* ft_lstdelone_h */
