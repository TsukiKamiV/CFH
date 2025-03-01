#include "../minishell.h"

/**
 * @brief Env builtin, affiche l'environnement. N'affiche rien et retourne 0 si l'environnement est vide
 * @param env L'environnement de minishell en l'état pendant l'utilisation (et non celui passé au lancement)
 * @return -1 si l'environnement est vide, 1 si un argument est fourni, 0 si tout s'est bien passé
 * @details Si paramètre fourni exécuter la commande système env avec le paramètre ? Si oui env systeme != env minishell ?
 */
#include "../minishell.h"

int	env_builtin(t_shell_data *shell_data)
{
	t_command_table	*cmd;
	int				i;

	cmd = shell_data->command_table;
	i = 0;

	// Si un argument est fourni, on ne le gère pas -> message d'erreur
	if (cmd->parsed_command[1])
	{
		ft_putendl_fd("env: Argument and options not handled.", STDERR);
		shell_data->exit_status = 2; // Code de retour en cas d'erreur
		return (shell_data->exit_status);
	}

	// Si l'environnement est vide
	if (!shell_data->env || !*shell_data->env)
	{
		shell_data->exit_status = 1;
		return (shell_data->exit_status);
	}

	// Affichage de chaque variable d'environnement
	// ATTENTION: Seulement les variables d'env avec '=' doivent être affichées
	while (shell_data->env[i])
	{
		if (ft_strchr(shell_data->env[i], '='))
			ft_putendl_fd(shell_data->env[i], cmd->fd_out);
		i++;
	}
	shell_data->exit_status = 0;
	return (shell_data->exit_status);
}
