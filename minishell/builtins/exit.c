#include "../minishell.h"
#include <limits.h>

/**
* @brief Convertit la chaîne str en long long en vérifiant qu'elle est entièrement numérique
* et qu'elle ne dépasse pas les bornes de long long min/max.
* - Si la conversion est correcte, la valeur est stockée dans *result et la fonction retourne 1.
* - Sinon, la fonction retourne 0.
* Pour la vérification d'overflow, on utilise les macros LLONG_MAX et LLONG_MIN.
* On travaille sur des unsigned long long pour faciliter le calcul.
*
* @warning Il y a encore readline à gérer pour les exits ?
*/
static int	ft_atoll_checked(const char *str, long long *result)
{
	int					sign = 1;
	int					i = 0;
	unsigned long long	res = 0;
	unsigned long long	max; // Limite en fonction du signe
	int					digit;

	/* Gestion éventuelle du signe */
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	/* S'il n'y a aucun chiffre après le signe, on considère que c'est invalide */
	if (!str[i])
		return (0);
	/* Choix de la limite en fonction du signe */
	if (sign == 1)
		max = LLONG_MAX;
	else
		// LLONG_MIN = -LLONG_MAX - 1
		max = (unsigned long long)LLONG_MAX + 1;
	/* Parcours de la chaîne et conversion */
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		digit = str[i] - '0';
		// Si res > (max - digit) / 10, alors le prochain calcul débordera
		if (res > (max - digit) / 10)
			return (0);
		res = res * 10 + digit;
		i++;
	}
	/* Application du signe et stockage du résultat */
	if (sign == -1)
		*result = -(long long)res;
	else
		*result = (long long)res;
	return (1);
}

static void exit_error_numeric(long long status, t_shell_data *shell_data)
{
	(void)status;
	ft_putstr_fd("exit: ", STDERR_FILENO);
	ft_putstr_fd(shell_data->command_table->parsed_command[1], STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	free_shell_data(shell_data);
	exit(2);
}

/**
 * @brief Builtin exit pour minishell.
 *
 * Comportement :
 * - Si aucun argument n'est fourni, on quitte avec le status actuel (ici 0 par défaut).
 * - Si un seul argument est fourni et est numérique, on quitte avec (unsigned char) la valeur.
 * - Si un seul argument est fourni et n'est pas numérique (ou dépasse LLONG_MAX/LLONG_MIN),
 *   on affiche une erreur, libère les ressources et on quitte avec le status 2.
 * - Si plusieurs arguments sont fournis, on affiche une erreur et on retourne 1 sans quitter.
 *
 * @param shell_data Structure contenant toutes les données du shell.
 * @return 0 si tout s'est bien passé, 1 si trop d'arguments.
 */
int	exit_builtin(t_shell_data *shell_data)
{
	int			status = 0;
	char		**args = shell_data->command_table->parsed_command;
	int			i;
	long long	conv;

	// ft_putendl_fd("exit", STDERR_FILENO);

	// Si un la commande est juste 'exit' sans argument, on quitte avec le status du dernier processus
	if (!args[1])
	{
		status = shell_data->exit_status;
		free_shell_data(shell_data);
		exit(status);
	}
	else if (args[1])
	{
		// Si plus d'un argument est fourni, on affiche une erreur et on ne quitte pas
		if (args[2])
			return (ft_putendl_fd("exit: too many arguments", STDERR_FILENO), 1);
		// Vérification que l'argument est bien numérique (on autorise un signe '+' ou '-')
		i = 0;
		if (args[1][i] == '-' || args[1][i] == '+')
			i++;
		if (args[1][i] == '\0')
			exit_error_numeric(status, shell_data);
		while (args[1][i])
		{
			if (!ft_isdigit(args[1][i]))
				exit_error_numeric(status, shell_data);
			i++;
		}
		// Conversion avec vérification d'overflow / underflow
		if (!ft_atoll_checked(args[1], &conv))
			exit_error_numeric(status, shell_data);
		// exit 256 -> 0, -1 -> 255, 255 -> 255)
		status = (unsigned char)conv;
	}
	rl_clear_history();
	free_shell_data(shell_data);
	rl_clear_history();
	exit(status);
	return (0);  // Jamais atteint
}
