#include "../minishell.h"

/**
 * @brief Unset builtin, supprime une variable d'environnement
 * @param shell_data La structure principale de minishell
 * @return 0 quoi qu'il arrive
 */
int	unset_builtin(t_shell_data *shell_data)
{
	int	i;
	//char	**new_env;

	/*
	if (shell_data->command_table->token_list->value == "unset" && shell_data->command_table->token_list->next == NULL)
		return (0); // Rien ne se passe
	if (shell_data->command_table->token_list->next->type != ARGUMENT)
		return (0); // Rien ne se passe si l'argument n'est pas valide (à vérifier)

	*/

	i = 0;
	// Chercher l'index de la variable à supprimer et utiliser remove_string_from_array pour la supprimer
	while (shell_data->env[i])
	{
		if (ft_strncmp(shell_data->env[i], shell_data->command_table->token_list->next->value, ft_strlen(shell_data->command_table->token_list->next->value)) == 0)
		{
			shell_data->env = remove_string_from_array(shell_data->env, i);
			break ;
		}
		i++;
	}
	return (0);
}
