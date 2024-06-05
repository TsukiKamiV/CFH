//
//  trashbin.c
//  Playground
//
//  Created by XU Luyao on 2024/6/5.
//  Copyright © 2024年 XU Luyao. All rights reserved.
//

#include <stdio.h>

char        **ft_split(char const *s, char c)
{
    size_t    i;
    size_t    j;
    int        index;
    char    **split;
    
    if (!s || !(split = malloc((count_words(s, c) + 1) * sizeof(char *))))
        return (0);
    i = 0;
    j = 0;
    index = -1;
    while (i <= ft_strlen(s))
    {
        if (s[i] != c && index < 0)
            index = i;
        else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
        {
            split[j++] = word_dup(s, index, i);
            index = -1;
        }
        i++;
    }
    split[j] = 0;
    return (split);
}
