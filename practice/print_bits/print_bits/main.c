#include <unistd.h>

void	ft_putstr(char *s)
{
	int	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}

void	print_bits(unsigned char octet)
{
	unsigned int nb = (unsigned int) octet;
	char bits[] = "00000000";
	if (nb % 2 != 0)
	{
		bits[7] = '1';
		nb--;
	}
	else
		bits[7] = '0';
	int index = 1;
	int temp = nb;
	while (nb)
	{
		temp = nb;
		while (temp > 1)
		{
			temp = temp / 2;
			index++;
		}
		bits[8 - index] = '1';
		int m = 1;
		while (index > 1)
		{
			m *= 2;
			index--;
		}
		nb = nb - m;
		index = 1;
	}
	ft_putstr(bits);
}

int main()
{
	char c = 22;
	print_bits(c);
	return (0);
	
}
