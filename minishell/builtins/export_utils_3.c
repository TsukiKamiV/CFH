#include "../minishell.h"

void print_sorted_exports(char **sorted_exports, int fd_out)
{
	int i = 0;
	
	sort_char_array(sorted_exports);
	while (sorted_exports[i])
	{
		printf("%d\n", fd_out);
		ft_putendl_fd(sorted_exports[i], fd_out);
		//ft_putstr_fd(sorted_exports[i], fd_out);
		free(sorted_exports[i]);
		i++;
	}
	free(sorted_exports);
}

int	is_valid_identifier(const char *str)
{
	int	i;
	
	if (!str || !str[0] || !(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	i = 0;
	while (str[i])
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}
