/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:37:39 by luxu              #+#    #+#             */
/*   Updated: 2024/05/31 19:59:17 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char ( *f)(unsigned int, char))
{
	char				*ret;
	size_t				s_len;
	unsigned int		i;
	unsigned int		slen;

	s_len = ft_strlen(s);
	slen = (unsigned int)s_len;
	ret = (char *)malloc((s_len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < slen)
	{
		ret[i] = f(i, s[i]);
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
