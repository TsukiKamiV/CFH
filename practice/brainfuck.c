#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	brainfuck(char *command)
{
	int	i = 0;
	int	j;
	char	c = '0';

	while (command[i])
	{
		if (command[i] == '>')
			i++;
		else if (command[i] == '<')
			i--;
		else if (command[i] == '+')
		{
			c = command[i] + 1;

