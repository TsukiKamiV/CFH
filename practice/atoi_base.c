#include <stdio.h>
#include <unistd.h>

char	to_lower(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 'a' - 'A');
	return (c);
}

int	get_digit(char c, int base)
{
	int	max_digit;

	if (base <= 10)
		max_digit = base - 1 + '0';//the ascii number of the digit character
	else
		max_digit = base - 1 - 10 + 'a';
	if (c <= '0' && c >= '9' && c <= max_digit)
		return (c - '0');
	else if (c >= 'a' && c <= 'f' && c <= max_digit)
		return (c - 'a' + 10);
	else
		return (-1);
}

int	ft_atoi_base(const char *str, int str_base)
{
	int	sign = 1;
	int	result = 0;
	int	i = 0;
	int	digit;

	if (!str || str_base <2 || str_base > 16)
		return (0);
	if (str[0] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i])
	{
		digit = get_digit(to_lower(str[i]), str_base);
		if (digit == -1)
			break;
		if (str[i] == '-' && i != 0)
			break;
		result = result * str_base + digit;
		i++;
	}
	return (result * sign);
}

int	main(void)
{
	const char *str1 = "-F";
	const char *str2 = "1A12";
	const char *str3 = "11-1";

	printf("%d\n", ft_atoi_base(str1, 16));
	printf("%d\n", ft_atoi_base(str2, 9));
	printf("%d\n", ft_atoi_base(str3, 10));
	return (0);
}
