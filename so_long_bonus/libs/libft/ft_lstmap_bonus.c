/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:25:14 by luxu              #+#    #+#             */
/*   Updated: 2024/06/03 16:45:17 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	void	*set;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		set = f(lst->content);
		new_node = ft_lstnew(set);
		if (!new_node)
		{
			del(set);
			ft_lstclear(&new_list, (*del));
			return (new_list);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}

/*
{
	t_list	*ret;
	t_list	*iter;

	if (!lst || !f || !del)
		return (NULL);
	ret = ft_lstnew(f(lst->content));
	iter = ret;
	while (lst && lst->next)
	{
		if (!iter)
			return (NULL);
		iter->next = ft_lstnew(f(lst->next->content));
		iter = iter->next;
		lst = lst->next;
	}
	return (ret);
}*/
