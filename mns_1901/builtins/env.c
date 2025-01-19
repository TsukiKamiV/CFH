#include "../minishell.h"

/**
 * @brief Env builtin, affiche l'environnement. N'affiche rien et retourne 0 si l'environnement est vide
 * @param env L'environnement de minishell en l'état pendant l'utilisation (et non celui passé au lancement)
 * @return 0 si l'environnement est vide, 1 si non
 * @details Si paramètre fourni exécuter la commande système env avec le paramètre ? Si oui env systeme != env minishell ?
 */
int	env_builtin(t_shell_data *shell_data)
{
	int	i;

	i = 0;
	if (!shell_data->env || !*shell_data->env)
		return (0);
	while (shell_data->env[i])
		printf("%s\n", shell_data->env[i++]);
	return (0);
}
