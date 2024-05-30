/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:12:37 by luxu              #+#    #+#             */
/*   Updated: 2024/05/22 16:56:24 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t ft_count_words(char const *s, char c)
{
    size_t  count;
    int i;
    int j;
    
    count = 0;
    i = 0;
    j = 0;
    while (s[i])
    {
        if (s[i] == c)
                i++;
        else if (s[i] != c)
        {
            while (s[i + j] != c && s[i + j])
                j++;
            count++;
            i = i + j;
            j = 0;
        }
    }
    return(count);
}

char **ft_split(char const *s, char c)
{
    char    **ret;
    size_t  words;
    size_t  index;
    size_t  word_len;
    size_t  i;
    size_t  j;
    
    words = ft_count_words(s, c);
    ret = (char **)malloc((words + 1) * sizeof(char *));
    if (ret == NULL)
        return (NULL);
    i = 0;
    j = 0;
    index = 0;
    while (s[i])
    {
        if (s[i] == c)
            i++;
        else if (s[i] != c)
        {
            while (s[i + j] && s[i + j] != c)
                j++;
            word_len = j;
            ret[index] = (char *)malloc((word_len + 1) * sizeof(char));
            if (!ret[index])
                return (NULL);
            ft_memcpy(ret[index], s + i, word_len);
            ret[index][word_len + 1] = '\0';
            i = i + j;
            j = 0;
            index++;
        }
    }
    ret[index] = NULL;
    return (ret);
}
