#include <unistd.h>

void	ft_put_char(char c)
{
	write(1, &c, 1);
}

void	print_hex(int number)
{
	int	nb;
	char	c;

	if (number > 16)
	{
		nb = number / 16;
		print_hex(nb);
	}
	else
		nb = 16 - number;
	if (nb <= 10)
		c = nb + '0';
	else
		c = nb + 'a' - 10;
	ft_put_char(c);
}

int	ft_atoi(char *str)
{
	int	sign = 1;
	int	result = 0;
	int	i = 0;

	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * sign);
}

int	main(int argc, char *argv[])
{
	if (argc != 2)
	{
		write(1, "\n", 1);
		return (0);
	}
	if (argv[1] < 0)
		return (0);
	print_hex(ft_atoi(argv[1]));
	return (0);
}
