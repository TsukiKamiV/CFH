//
//  main.c
//  Playground
//
//  Created by XU Luyao on 2024/6/4.
//  Copyright © 2024年 XU Luyao. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

char    *myFunc(const char *s, char c);
char    **ft_allocation(size_t n);
size_t  ft_count_words(char const *s, char c);
char    *ft_substr(char const *s, unsigned int start, size_t len);
size_t  ft_strlcpy(char *dest, const char *src, size_t size);
size_t  ft_strlen(const char *s);


int main()
{
    //myFunc_memchr(((void *)0), '\0', 0x20);
    //myFunc(((void *)0));
    char *s = "      split       this for   me  !       ";
    
    char **result = myFunc(s, ' ');
    if (!result)
        printf("Success");
    else
        printf("Error");
}

size_t  ft_strlen(const char *s)
{
    size_t  i;
    
    i = 0;
    while (s[i])
        i++;
    return (i);
}

size_t  ft_strlcpy(char *dest, const char *src, size_t size)
{
    size_t  i;
    size_t  s_len;
    
    s_len = ft_strlen(src);
    if (size > 0)
    {
        i = 0;
        while (i < size -1 && src[i])
        {
            dest[i] = src[i];
            i++;
        }
        dest[i] = '\0';
    }
    return (s_len);
}

size_t  ft_count_words(char const *s, char c)
{
    size_t  count;
    int             i;
    int             j;
    
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
    return (count);
}

char    **ft_allocation(size_t n)
{
    char    **ret;
    
    ret = (char **)malloc((n + 1) * sizeof (char *));
    if (!ret)
        return (NULL);
    return (ret);
}

char    *ft_substr(char const *s, unsigned int start, size_t len)
{
    size_t  s_len;
    size_t  ret_len;
    char    *ret;
    
    if (!s)
        return (NULL);
    s_len = ft_strlen(s);
    if (start >= s_len)
    {
        ret = (char *)malloc(1);
        if (ret)
            ret[0] = '\0';
        return (ret);
    }
    ret_len = s_len - start;
    if (ret_len > len)
        ret_len = len;
    ret = (char *)malloc((ret_len + 1) * sizeof(char));
    if (!ret)
        return (NULL);
    ft_strlcpy(ret, s + start, ret_len + 1);
    return (ret);
}

char *myFunc(const char *s, char c) //split
{
    char    **ret;
    size_t  words;
    size_t  index;
    size_t  start;
    size_t  end;
    
    words = ft_count_words(s, c);
    ret = ft_allocation(words);
    if (!ret)
        return (NULL);
    index = 0;
    start = 0;
    while (index < words)
    {
        while (s[start] == (unsigned char)c && s[start])
            start++;
        end = start;
        while (s[end] != c && s[end])
            end++;
        ret[index] = ft_substr(s, start, end - start);
        if (!ret[index])
            return (NULL);
        start = end;
        index++;
    }
    ret[index] = NULL;
    return (ret);
}

void *myFunc_memchr(const void *s, int c, size_t n)
{
    size_t  i;

    if (s)
    {
        i = 0;
        while (i < n)
        {
            if (*(unsigned char *)(s + i) == (unsigned char)c)
                return ((void *)(s + i));
            i++;
        }
    } else {
        raise(SIGSEGV);
    }
    return NULL;
}
