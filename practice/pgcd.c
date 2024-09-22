#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("\n");
		return (0);
	}
	int	a = atoi(argv[1]);
	int b = atoi(argv[2]);
	int	i = a;
	int	j;
	while (i > 0)
	{
		j = b;
		while (j > 0)
		{
			if (b % j == 0 && a % j == 0 && ((b % j) == (a % j)))
			{
				printf("%d\n", j);
				return (0);
			}
			j--;
		}
		i--;
	}
	return (0);
}
