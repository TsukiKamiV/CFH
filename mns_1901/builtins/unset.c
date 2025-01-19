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

	if (!shell_data->splitted_prev_command[1])
		return(print_tab(shell_data->env), 0); // Affiche l'environnement si unset est appelé sans argument
	// Obtenir l'index de la variable à supprimer (si elle existe)
	while (shell_data->env[i])
	{
		// Si la variable est trouvée
		if (!ft_strncmp(shell_data->env[i], shell_data->splitted_prev_command[1], ft_strlen(shell_data->splitted_prev_command[1])))
			break ;
		i++;
	}
	if (!shell_data->env[i])
		return (0); // Variable non trouvée
	shell_data->env = remove_string_from_array(shell_data->env, i);
	return (0);
}
