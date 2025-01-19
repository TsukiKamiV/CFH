/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpantign <maildelulua42@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 06:57:06 by lpantign          #+#    #+#             */
/*   Updated: 2024/05/27 20:42:33 by lpantign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*next_save;
	t_list	*head;

	head = *lst;
	while (head)
	{
		next_save = head->next;
		(*del)(head->content);
		free(head);
		head = next_save;
	}
	*lst = NULL;
}
