/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpantign <maildelulua42@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:08:51 by lpantign          #+#    #+#             */
/*   Updated: 2024/06/03 22:28:00 by lpantign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_size(long n)
{
	int	size;

	size = 0;
	if (n <= 0)
		size++;
	while (n != 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

static void	fill_tab(long n, int size, int offset, char *tab)
{
	while (size > offset)
	{
		tab[size - 1] = (n % 10) + '0';
		n = n / 10;
		size--;
	}
}

char	*ft_itoa(int n)
{
	int		offset;
	int		size;
	char	*tab;
	long	nb;

	nb = n;
	offset = 0;
	size = get_size(nb);
	tab = (char *)malloc(sizeof(char) * (size + 1));
	if (!tab)
		return (NULL);
	if (nb < 0)
	{
		tab[0] = '-';
		offset = 1;
		nb *= -1;
	}
	fill_tab(nb, size, offset, tab);
	tab[size] = '\0';
	return (tab);
}

/*
int main(void)
{
    int n = -2147483648;
    char *str = ft_itoa(n);
    printf("%s\n", str);
    free(str);
    return (0);
}*/
