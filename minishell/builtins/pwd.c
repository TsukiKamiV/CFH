#include "../minishell.h"

/**
 * @brief	Pwd builtin, affiche le répertoire courant
 * @return 0 dans tous les cas ?
 * ##ATTENTION: à modifier pour prendre le data (ou au pire le fd in) et write sur le fd_out##
 */
int	pwd_builtin(t_shell_data *shell_data)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		shell_data->exit_status = 1;
		return (shell_data->exit_status);
	}
	ft_putendl_fd(pwd, shell_data->command_table->fd_out);
	free(pwd);
	shell_data->exit_status = 0;
	return (shell_data->exit_status);
}
