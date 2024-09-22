#include <stdio.h>

void	ft_sort_int_tab(int *tab, unsigned int size)
{
	unsigned int	i;
	unsigned int	j;
	int	temp;

	i = 0;
	temp = 0;
	while (i < size)
	{
		j = 0;
		while (j < size - 1)
		{
			if (tab[j] > tab[j + 1])
			{
				temp = tab[j];
				tab[j] = tab[j + 1];
				tab[j + 1] = temp;
				//printf("%d and %d swapped\n", tab[j], tab[j + 1]);
			}
			j++;
		}
		i++;
	}
}

int main()
{
	int tab[] = {5, 4, 3, 2, 1};
	unsigned int size = 5;
	ft_sort_int_tab(tab, size);
	unsigned int i = 0;
	while (i < 5)
	{
		printf("%d\n", tab[i]);
		i++;
	}
	return (0);
}
