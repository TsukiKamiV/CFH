#include <stdio.h>
#include <stdlib.h>

int	count_size(long nb)
{
	int	i = 0;

	if (nb == 0)
		return (1);
	else if (nb < 0)
	{
		i = 1;
		nb = -nb;
	}
	while (nb)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char	*itoa(int nbr)
{
	char *str = NULL;
	int	size = count_size((long)nbr);
	long nb = (long)nbr;
	int	is_negative = 0;

	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	/*
	if (nb == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}*/
	if (nb < 0)
	{
		is_negative = 1;
		str[0] = '-';
	}
	str[size] = '\0';
	while (size > is_negative)
	{
		str[size - 1] = nb % 10 + '0';
		nb /= 10;
		size--;
	}
	return (str);
}




int main()
{
	int	a = -2147483648;
	int	b = 2147483647;
	int c = 0;
	printf("%d\n", a);
	printf("%d\n", b);
	printf("%d\n", c);
	return (0);
}


