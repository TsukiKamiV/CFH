#include "../minishell.h"

/**
 * @brief Cherche à exécuter une commande fournie par l'utilisateur
 * @param shell_data La structure principale de minishell
 * @return 0 si la commande a été exécutée, -1 si la commande n'a pas été trouvée
 *
 * @details Très laid, à revoir
*/
// int	execute_simple_builtin_command(t_shell_data *shell_data)
// {
// 	if (shell_data->command_table->token_list == NULL)
// 		return (-1); // Commande vide
// 	if (!ft_strncmp(shell_data->command_table->token_list->value, "env", 3))
// 		return (env_builtin(shell_data), 0); // 0 car env retournera toujours 0 sans options
// 	else if (!ft_strncmp(shell_data->command_table->token_list->value, "pwd", 3))
// 		return (pwd_builtin(shell_data), 0); // 0 car pwd retournera toujours 0 sans options (à vérifier)
// 	// else if (!ft_strncmp(shell_data->command_table->token_list->value, "export", 6))
// 	// 	return (export_builtin(shell_data), 0); // 0 car export retournera toujours 0 sans options (à vérifier)
// 	else if (!ft_strncmp(shell_data->command_table->token_list->value, "unset", 5))
// 		return (unset_builtin(shell_data), 0); // 0 car unset retournera toujours 0 sans options (à vérifier)
// 	else if (!ft_strncmp(shell_data->command_table->token_list->value, "exit", 4))
// 		return (exit_builtin(shell_data));
// 	else if (!ft_strncmp(shell_data->command_table->token_list->value, "echo", 4))
// 		return (echo_builtin(shell_data));
// 	else if (!ft_strncmp(shell_data->command_table->token_list->value, "cd", 2))
// 		return (cd_builtin(shell_data));
// 	else if (!ft_strncmp(shell_data->command_table->token_list->value, "export", 6))
// 		return (export_builtin(shell_data));
// 	return (-1); // Commande non trouvée
// }


#define IS_BUILTIN(name, func)  \
	if (!ft_strcmp(token->value, name)) return func(shell_data);

int execute_simple_builtin_command(t_shell_data *shell_data)
{
	t_token *token;

	if (!shell_data->command_table || !shell_data->command_table->token_list)
		return -1;

	token = shell_data->command_table->token_list;
	IS_BUILTIN("env", env_builtin);
	IS_BUILTIN("pwd", pwd_builtin);
	IS_BUILTIN("unset", unset_builtin);
	IS_BUILTIN("exit", exit_builtin);
	IS_BUILTIN("echo", echo_builtin);
	IS_BUILTIN("cd", cd_builtin);
	IS_BUILTIN("export", export_builtin);

	return -1;
}
