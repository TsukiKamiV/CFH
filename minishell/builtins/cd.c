#include "../minishell.h"

//char	*get_cd_dir(t_shell_data *data)
//{
//	t_token		*arg;
//	char		*dir;
//
//	arg = data->command_table->token_list;
//	if (arg)
//		arg = arg->next;
//	if (!arg || arg->type != ARGUMENT)
//	{
//		dir = get_env_value("HOME", data->env);
//		if (!dir)
//		{
//			write(STDERR, "cd: HOME not set\n", 17);
//			return (NULL);
//		}
//	}
//	else if (!ft_strcmp(arg->value, "-"))
//	{
//		dir = get_env_value("OLDPWD", data->env);
//		if (!dir)
//		{
//			write(STDERR, "cd: OLDPWD not set\n", 19);
//			return (NULL);
//		}
//		write(data->command_table->fd_out, dir, ft_strlen(dir));
//		write(data->command_table->fd_out, "\n", 1);
//	}
//	else
//		dir = arg->value;
//	return (dir);
//}

char	*get_cd_dir(t_shell_data *data)
{
	t_token	*arg;
	char	*dir;
	
	arg = data->command_table->token_list;
	if (arg)
		arg = arg->next;
	if (!arg || arg->type != ARGUMENT)
	{
		dir = get_env_value("HOME", data->env);
		if (!dir)
		{
			write(STDERR, "cd: HOME not set\n", 17);
			return (NULL);
		}
		return (dir);
	}
	if (!ft_strcmp(arg->value, "-"))
	{
		dir = get_env_value("OLDPWD", data->env);
		if (!dir)
		{
			write(STDERR, "cd: OLDPWD not set\n", 19);
			return (NULL);
		}
		write(data->command_table->fd_out, dir, ft_strlen(dir));
		write(data->command_table->fd_out, "\n", 1);
		return (dir);
	}
	return (arg->value);
}

int	cd_change_dir(t_shell_data *data, char *dir)
{
	char	*old;
	char	*new;
	
	old = getcwd(NULL, 0);
	if (chdir(dir) != 0)
	{
		free (old);
		ft_putendl_fd("cd: No such file or directory", data->command_table->fd_out);
		data->exit_status = 1;
		return (1);
	}
	new = getcwd(NULL, 0);
	if (old)
		set_env_value(&data->env, "OLDPWD", old);
	if (new)
		set_env_value(&data->env, "PWD", new);
	free (old);
	free (new);
	data->exit_status = 0;
	return (0);
}

int	cd_builtin(t_shell_data *data)
{
	char	*dir;
	
	if (!data || !data->command_table)
		return (1);
	dir = get_cd_dir(data);
	if (!dir)
	{
		data->exit_status = 1;
		return (1);
	}
	return (cd_change_dir(data, dir));
}
