/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpantign <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:38:54 by lpantign          #+#    #+#             */
/*   Updated: 2024/05/23 15:41:42 by lpantign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	int		start;
	int		end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen((char *)s1) - 1;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (end > start && ft_strchr(set, s1[end]))
	end--;
	trimmed = ft_substr(s1, start, end - start + 1);
	if (!trimmed)
		return (NULL);
	return (trimmed);
}
/*
#include <stdio.h>
int main(void)
{
    const char *s1 = "kakakakaBonjour je suis un trimmerkkkakkaaakaaa";
    const char *set1 = "kak";
    const char *s2 = "Bonjour je suis un trimmer";
    const char *set2 = " ";
    const char *s3 = "Pierre qui roule n'amasse pas mousse";
    const char *set3 = "Pierre qui roule n'amasse pas mousse";
    const char *s4 = "Pierre qui roule n'amasse pas mousse";
    const char *set4 = "";
    char *new_str = NULL;

    new_str = ft_strtrim(s1, set1);
    if (!new_str)
        return (1);
    printf("Original 1: %s | Trim set: %s\n", s1, set1);
    printf("Trimmed 1: %s\n", new_str);
    free(new_str);
    new_str = ft_strtrim(s2, set2);
    if (!new_str)
        return (1);
    printf("Original 2: %s | Trim set: %s\n", s2, set2);
    printf("Trimmed 2: %s\n", new_str);
    free(new_str);
    new_str = ft_strtrim(s3, set3);
    if (!new_str)
        return (1);
    printf("Original 3: %s | Trim set: %s\n", s3, set3);
    printf("Trimmed 3: %s\n", new_str);
    free(new_str);
    new_str = ft_strtrim(s4, set4);
    if (!new_str)
        return (1);
    printf("Original 4: %s | Trim set: %s\n", s4, set4);
    printf("Trimmed 4: %s\n", new_str);
    free(new_str);

    return (0);
}*/
