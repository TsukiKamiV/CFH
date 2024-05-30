#include "libft.h"

size_t  ft_count_digit(long n)
{
    size_t  digit = 0;
    if (n == 0)
        return (1);
    while (n != 0)
    {
        n = n / 10;
        digit++;
    }
    return (digit);
}

char    *ft_itoa(int n)
{
    char *ret;
    size_t  digit;
    size_t  i;
    size_t  sign;
    long num = n;
    
    if (n == 0)
        return ("0");
    else if (n < 0)
    {
        sign = 1;
        num = -num;
    }
    else
        sign = 0;
    digit = ft_count_digit(num);
    ret = (char *)malloc((digit + sign + 1) * sizeof(char));
    if (!ret)
        return (NULL);
    if (sign == 1)
        ret[0] = '-';
    i = digit + sign - 1;
    while (num != 0)
    {
        ret[i] = num % 10 + '0';
        num /= 10;
        i--;
    }
    ret[digit + sign] = '\0';
    return (ret);
}
