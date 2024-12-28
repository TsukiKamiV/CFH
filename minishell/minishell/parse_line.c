//
//  parse_line.c
//  minishell
//
//  Created by Luyao Xu on 25/12/2024.
//

#include "minishell.h"

void	parse_line(t_shell_data *data)
{
	char	*str;
	
	str = ft_strdup(data->line);
	if (!validate_quotes(str))
		error_exit(data, "Invalid quotes", 2);
}
