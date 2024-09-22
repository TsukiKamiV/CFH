#include <unistd.h>

void    ft_put_char(char c)
{
	write(1, &c, 1);
}

void    print_hex(int number)
{
	char    c;
	
	if (number >= 16)
	{
		print_hex(number / 16);
		print_hex(number % 16);
	}
	else
	{
		if (number <= 9)
			c = number + '0';
		else
			c = number + 'a' - 10;
		ft_put_char(c);
	}
}

int ft_atoi(char *str)
{
	int sign = 1;
	int result = 0;
	int i = 0;
	
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

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		write(1, "\n", 1);
		return (0);
	}
	int	number = ft_atoi(argv[1]);
	if (number < 0)
		return (0);
	print_hex(number);
	write(1, "\n", 1);
	return (0);
}

