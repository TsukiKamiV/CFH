#include "get_next_line.h"

size_t  ft_strlen(const char *s)
{
    size_t  i;
    
    i = 0;
    while (s[i])
        i++;
    return (i);
}

size_t  ft_strlcat(char *dest, const char *src, size_t size)
{
    size_t  i;
    size_t  j;
    size_t  res;
    
    i = 0;
    j = 0;
    res = 0;
    while (dest[i] != '\0')
        i++;
    while (src[res])
        res++;
    if (size < i)
        res += size;
    else
        res += i;
    while (src[j] && i + 1 < size)
    {
        dest[i] = src[j];
        i++;
        j++;
    }
    dest[i] = '\0';
    return (res);
}

void    *ft_calloc(size_t nmemb, size_t size)
{
    void    *dest;
    unsigned char *ptr;
    size_t  i;
    
    dest = (void *)malloc(nmemb * size);
    if (!dest)
        return (NULL);
    i = 0;
    ptr = (unsigned char *)dest;
    while (i < nmemb * size)
    {
        ptr[i] = 0;
        i++;
    }
    return (dest);
}

size_t ft_strlcpy(char *dest, const char *src, size_t size)
{
    size_t i;
    size_t s_len;
    
    s_len = ft_strlen(src);
    if (size > 0)
    {
        i = 0;
        while (i < size - 1 && src[i])
        {
            dest[i] = src[i];
            i++;
        }
        dest[i] = '\0';
    }
    return (s_len);
}

char    *ft_strjoin(const char *s1, const char *s2)
{
    size_t len1;
    size_t  len2;
    char *dest;
    
    len1 = ft_strlen(s1);
    len2 = ft_strlen(s2);
    dest = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
    if (!dest)
        return (NULL);
    ft_strlcpy(dest, s1, len1 + 1);
    ft_strlcat(dest, s2, len1 + len2 + 1);
    return (dest);
}


char    *ft_strdup(const char *s)
{
    char    *dest;
    size_t  i;
    size_t  len;
    
    len = ft_strlen(s);
    dest = (char *)malloc((len + 1) * sizeof(char));
    if (!dest)
        return (NULL);
    i = 0;
    while (s[i])
    {
        dest[i] = s[i];
        i++;
    }
    dest[i] ='\0';
    return (dest);
}

char    *ft_strchr(const char *s, int c)
{
    int i;
    
    i = 0;
    while (s[i])
    {
        if (s[i] == (char)c)
            return ((char *)(s + i));
        i++;
    }
    if (s[i] == (char)c)
        return ((char *)(s + i));
    return (NULL);
}

