//
//  main.c
//  itoa_test
//
//  Created by Luyao Xu on 13/09/2024.
//
#include <stdlib.h>
#include <stdio.h>

int	count_digit(long nbr);
char	*ft_itoa(int nbr);

int main(int argc, const char * argv[]) {
	int	n1 = 123;
	int	n2 = 0;
	int	n3 = -123;
	int	max = 2147483647;
	int min = -2147483648;
	printf("123 | %s\n0 | %s\n-123 | %s\nint max | %s\nint min | %s\n", ft_itoa(n1), ft_itoa(n2), ft_itoa(n3), ft_itoa(max), ft_itoa(min));
	return 0;
}


int	count_digit(long nbr)
{
	int	digit;
	if (nbr < 0)
	{
		digit++;
		nbr = -nbr;
	}
	if (nbr == 0)
		digit = 1;
	if (nbr > 0)
		digit = 0;
	while (nbr)
	{
		nbr = nbr / 10;
		digit++;
	}
	return (digit);
}

char	*ft_itoa(int nbr)
{
	long n = (long)nbr;
	int	digit = count_digit((long)nbr);
	char	*str;
	
	str = (char *)malloc(sizeof(char) * (digit + 1));
	if (nbr == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	else if (nbr > 0)
	{
		str[digit + 1] = '\0';
		while (digit)
		{
			str[digit - 1] = n % 10 + '0';
			n = n / 10;
			digit--;
		}
	}
	else if (nbr < 0)
	{
		n = (long)nbr * -1;
		str[0] = '-';
		while (digit)
		{
			str[digit] = n % 10 + '0';
			n = n / 10;
			digit--;
		}
	}
	printf("String is: %s\n", str);
	return (str);
}

