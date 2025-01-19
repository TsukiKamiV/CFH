#include "../minishell.h"

/**
 * @brief Cherche à exécuter une commande fournie par l'utilisateur
 * @param shell_data La structure principale de minishell
 * @return 0 si la commande a été exécutée, -1 si la commande n'a pas été trouvée
 *
 * @details Très laid, à revoir
*/
int	execute_builtin_command(t_shell_data *shell_data)
{
	if (shell_data->command_table->token_list == NULL)
		return (-1); // Commande vide
	if (!ft_strncmp(shell_data->command_table->token_list->value, "env", 3))
		return (env_builtin(shell_data), 0); // 0 car env retournera toujours 0 sans options
	else if (!ft_strncmp(shell_data->command_table->token_list->value, "pwd", 3))
		return (pwd_builtin(), 0); // 0 car pwd retournera toujours 0 sans options (à vérifier)
	// else if (!ft_strncmp(shell_data->command_table->token_list->value, "export", 6))
	// 	return (export_builtin(shell_data), 0); // 0 car export retournera toujours 0 sans options (à vérifier)
	else if (!ft_strncmp(shell_data->command_table->token_list->value, "unset", 5))
		return (unset_builtin(shell_data), 0); // 0 car unset retournera toujours 0 sans options (à vérifier)
	return (-1); // Commande non trouvée
}
