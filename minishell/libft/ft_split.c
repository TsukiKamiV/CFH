/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpantign <maildelulua42@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 00:59:29 by lpantign          #+#    #+#             */
/*   Updated: 2024/06/04 01:39:00 by lpantign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Free the allocated memory in case of an error.
 *
 * @param splitted The array of strings to free.
 * @param index The current index to free.
 * @return 1 if index is less than 0, otherwise 0.
 */
static int	freefunc(char **splitted, int index)
{
	while (index >= 0)
	{
		free(splitted[index]);
		index--;
	}
	free(splitted);
	return (0);
}

/**
 * Count the number of words separated by the given charset in the string.
 *
 * @param str The input string.
 * @param charset The delimiter character.
 * @return The number of words.
 */
static int	word_count(const char *str, char charset)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && str[i] == charset)
			i++;
		if (str[i] && str[i] != charset)
		{
			count++;
			while (str[i] && str[i] != charset)
				i++;
		}
	}
	return (count);
}

/**
 * Allocate memory for a word and copy it from the input string.
 *
 * @param str The input string.
 * @param charset The delimiter character.
 * @return The allocated word or NULL in case of error.
 */
static char	*malloc_word(const char *str, char charset)
{
	char	*word;
	int		len;
	int		i;

	len = 0;
	while (str[len] && str[len] != charset)
		len++;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

/**
 * Split the input string into an array of words separated by the given charset.
 *
 * @param splitted The array to hold the split words.
 * @param charset The delimiter character.
 * @param str The input string.
 * @return The array of split words or NULL in case of error.
 */
static char	**splitter(char **splitted, char charset, const char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && str[i] == charset)
			i++;
		if (str[i] && str[i] != charset)
		{
			splitted[j] = malloc_word(&str[i], charset);
			if (!splitted[j])
			{
				freefunc(splitted, j);
				return (NULL);
			}
			j++;
			while (str[i] && str[i] != charset)
				i++;
		}
	}
	splitted[j] = NULL;
	return (splitted);
}

/**
 * Split the input string into an array of words separated by the given charset.
 *
 * @param str The input string.
 * @param charset The delimiter character.
 * @return The array of split words or NULL in case of error.
 */
char	**ft_split(const char *str, char charset)
{
	char	**splitted;
	int		count;

	if (!str)
		return (NULL);
	count = word_count(str, charset);
	splitted = (char **)malloc(sizeof(char *) * (count + 1));
	if (!splitted)
		return (NULL);
	return (splitter(splitted, charset, str));
}
/*
int main(void)
{
	char *str = "   Bonjour salut je  suis nul en                   dev ";
	char **tab = ft_split(str, ' ');

	for (int i = 0; tab[i]; i++)
		printf("%s\n", tab[i]);
	return (0);
}*/
