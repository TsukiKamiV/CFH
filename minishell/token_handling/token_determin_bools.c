#include "../minishell.h"

//fonction boolean pour builtin
bool	is_builtin(const char *value)
{
	return (!ft_strcmp(value, "cd") || !ft_strcmp(value, "echo") || !ft_strcmp(value, "exit") ||\
			!ft_strcmp(value, "pwd") || !ft_strcmp(value, "export") || !ft_strcmp(value, "unset") ||\
			!ft_strcmp(value, "env"));
}

//separator a ajouter?
bool	is_separator(const char *value)
{
	return (!ft_strcmp(value, "||") || !ft_strcmp(value, "&&") || !ft_strcmp(value, ";"));
}

bool	is_operator(const char *value)
{
	return (!ft_strcmp(value, "&"));
}

bool	is_pipe(const char *value)
{
	return (!ft_strcmp(value, "|"));
}

bool	is_redirection(const char *value)
{
	return (!ft_strcmp(value, ">") || !ft_strcmp(value, ">>") ||\
			!ft_strcmp(value, "<") || !ft_strcmp(value, "<<"));
}
