//
//  ft_strmapi.c
//  
//
//  Created by XU Luyao on 2024/5/26.
//

#include "ft_strmapi.h"
#include "ft_strlen.h"
#include <stdlib.h>

char *ft_strmapi(char const *s, char(*f)(unsigned int, char))
{
    size_t  s_len;
    char    *ret;
    unsigned int  i;
    unsigned int slen;
    
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
