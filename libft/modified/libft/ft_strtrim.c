/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:35:26 by luxu              #+#    #+#             */
/*   Updated: 2024/05/22 18:52:44 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_in_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char const	*start;
	char const	*end;
	char	*ret;
	size_t	s1_len;
	size_t	set_len;	
	size_t	ret_len;

	if (!s1 || !set)
		return (NULL);
	start = (unsigned char *)s1;
	end = (unsigned char *)s1 + s1_len - 1;
	while (*start && is_in_set(*start, set))
		start++;
	while (end >= start && is_in_set(*end, set)
		end--;
	ret_len = end - start + 1;
	ret = strdup(start, len);
	if (ret == NULL)
		return (NULL);
	return (ret);
}
