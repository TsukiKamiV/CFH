#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void    ft_putchar(char c)
{
	write(1, &c, 1);
}
/*
   10 void    ft_putnbr(int nbr)
   11 {
   12     unsigned long n = nbr;
   13     if (nbr < 0)
   14     {
   15         ft_putchar("-");
   16         n = -nbr;
   17     }
   18 */

int ft_is_prime(int a)
{
	int i = a;

	while (i)
	{
		if (a % i == 0 && i != 1 & i != a)
			return (0);
		i--;
	}
	return (1);
}

int add_prime_sum(int a)
{
	int res = 0;
	while (a)
	{
		if (ft_is_prime(a) == 1)
			res += a;
		a--;
	}
	return (res - 1);
}

int main(int argc, char *argv[])
{
	if (argc != 2)
		{
			printf("0\n");
			return (0);
		}
	printf("%d\n", add_prime_sum(atoi(argv[1])));
	return (0);
}
