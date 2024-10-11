int	get_digit(char c, int base)
{
	int	max_digit;
	if (base <= 10)
		max_digit = base - 1 + '0';
	else
		max_digit = base - 1 - 10 + 'a';
	if (c >= 0 && base <= 9 && base <= max_digit)
		return (c - '0');
	else if (c >= 'a' && c <= 'f' && c <= max_digit)
		return (c - 'a' + 10);
	else
		return (-1);
}

int	ft_atoi_base(const char *str, int base)
{
	int	res = 0;
	int	sign = 1;
	int	digit;
	int	i = 0;

	if (!str || base < 2 || base > 16)
		return (0);
	if (str[0] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i])
	{
		digit = get_digit(str[i], base);
		if (digit == -1)
			break;
		res = res * base + digit;
		i++;
	}
	return (res * sign);
}
