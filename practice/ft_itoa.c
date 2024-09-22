#include <stdio.h>
#include <stdlib.h>

size_t	count_size(long  nb)
{
	size_t	size;

	size = 0;
	if (nb < 0)
	{
		nb = -nb;
		size++;
	}
	else if (nb == 0)
		size = 1;
	else
	{
		while (nb)
		{
			nb = nb / 10;
			size++;
		}
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*str;
	int	is_negative;
	long 	nb;
	size_t	size;

	size = count_size(n);
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	is_negative = 0;
	nb = (long)n;
	if (nb < 0)
	{
		is_negative = 1;
		nb = -nb;
		str[0] = '-';
	}
	str[size] = '\0';
	while (size > (size_t)is_negative)
	{
		str[size - 1] = nb % 10 + '0';
		nb = nb / 10;
		size--;
	}
	return (str);
}
