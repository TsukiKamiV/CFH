/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpantign <maildelulua42@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 01:40:53 by lpantign          #+#    #+#             */
/*   Updated: 2024/05/27 01:40:55 by lpantign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 ** Applies the function f to each character of the string passed as argument
 ** to create a new string with the results of successive applications of f.
 ** @param s - the string to map
 ** @param f - the function to apply to each character
 ** @return a new string with mapped characters or NULL if allocation fails
 **/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*new_str;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		new_str[i] = f(i, s[i]);
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

/*
int main(void)
{
    char *s = "Hello, World!";
    char *new_s = ft_strmapi(s, &add_index_to_char);
    printf("%s\n", s);
    printf("%s\n", new_s);
    free(new_s);
    return 0;
}*/
