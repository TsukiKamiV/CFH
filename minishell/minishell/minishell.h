//
//  minishell.h
//  minishell
//
//  Created by Luyao Xu on 24/12/2024.
//

#ifndef minishell_h
#define minishell_h

#include "libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include <signal.h>

typedef struct s_command
{
	char	**argv;
	char	*input_redir;
	char	*output_redir;
	struct s_command *next;
}	t_command;

typedef struct s_shell_data
{
	char	**env;
	char	*username;
	char	*hostname;
	char	*prompt;
	char	*line;
	struct sigaction	sig_config;
	int		exit_status;//($?)
	t_command	*commands;
	
}	t_shell_data;

extern void rl_clear_history(void);
void	parse_line(t_shell_data *data);
bool	validate_quotes(const char *input);
void	error_exit(t_shell_data *data, const char *msg, int status);


#endif /* minishell_h */
