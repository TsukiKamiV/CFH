#include <stdio.h>
#include <stdlib.h>

int	is_prime(int nb)
{
	int	i = nb;
	while (i)
	{
		if (i != 1 && i != nb && nb % i == 0)
			return (0);
		i--;
	}
	return (1);
}

void	fprime(int nb, int factor)
{
	while (factor < nb)
	{
		if (nb % factor == 0 && is_prime(factor) == 1)
		{
			nb = nb / factor;
			printf("%d*", factor);
			if (is_prime(nb) == 1)
			{
				printf("%d\n", nb);
				return ;
			}
			else
			{
				fprime(nb, factor);
				return ;
			}
		}
		factor++;
	}
}

int main(int argc, const char * argv[])
{
	if (argc != 2)
		printf("\n");
	else if (atoi(argv[1]) <= 1)
		printf("\n");
	else if(is_prime(atoi(argv[1]) == 1))
		printf("%d\n", atoi(argv[1]));
	else
		fprime(atoi(argv[1]), 2);
	return 0;
}
