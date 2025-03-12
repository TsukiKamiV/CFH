#include "../minishell.h"

/**
 * @brief Unset builtin, supprime une variable d'environnement
 * @param shell_data La structure principale de minishell
 * @return 0 quoi qu'il arrive
 */

int	unset_builtin(t_shell_data *shell_data)
{
	t_token *token;
	int		i;
	char	*equal_sign;
	int		found;
	
	if (!shell_data->command_table->token_list->next)
		return (0); //rien ne se passe si commande sans argument
	/*if (shell_data->command_table->token_list->next->type != ARGUMENT)
	 return (0); // Rien ne se passe si l'argument n'est pas valide (à vérifier)
	 */
	token = shell_data->command_table->token_list->next;
	while (token)
	{
		i = 0;
		found = 0;
		//parcourir d'abord dans l'env
		while (shell_data->env[i])
		{
			equal_sign = ft_strchr(shell_data->env[i], '=');
			if (equal_sign && (size_t)(equal_sign - shell_data->env[i]) == ft_strlen(token->value) &&
				ft_strncmp(shell_data->env[i], token->value, ft_strlen(token->value)) == 0)
			{
				shell_data->env = remove_string_from_array(shell_data->env, i);
				found = 1;
				break;
			}
			i++;
		}
		//si l'argument n'exist pas dans l'env, il faut ensuite chercher dans exported_vars
		//car si on fait   export VAR   sans '=' et valeur en amont, VAR n'est pas ajouté dans l'env
		if (!found && shell_data->exported_vars)
		{
			i = 0;
			while (shell_data->exported_vars[i])
			{
				if (ft_strcmp(shell_data->exported_vars[i], token->value) == 0)
				{
					shell_data->exported_vars = remove_string_from_array(shell_data->exported_vars, i);
					break;
				}
				i++;
			}
		}
		token = token->next;
	}
	return (0);
}
