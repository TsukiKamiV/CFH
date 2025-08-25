/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:19:42 by luxu              #+#    #+#             */
/*   Updated: 2024/06/03 15:47:46 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	if (lst && (*lst) && del)
	{
		if ((*lst)->next)
			ft_lstclear((&(*lst)->next), del);
		del((*lst)->content);
		free(*lst);
		*lst = NULL;
	}
}
