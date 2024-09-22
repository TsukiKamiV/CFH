#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}
/*
void	ft_putnbr(int nbr)
{
	unsigned long n = nbr;
	if (nbr < 0)
	{
		ft_putchar("-");
		n = -nbr;
	}
*/

int ft_is_prime(int a)
{
	int	i = a;

	while (i)
	{
		if (a % i == 0 && i != 1 & i != a)
			return (0);
		i++;
	}
	return (1);
}

int	add_prime_sum(int a)
{
	int	res = 0;
	while (a)
	{
		if (ft_is_prime(a) == 1)
			res += a;
		a--;
	}
	return (res);
}

int	main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("\n");
		return (0);
	}
	printf("%d\n", add_prime_sum(atoi(argv[1])));
	return (0);
}
