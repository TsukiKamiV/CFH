#include "../minishell.h"

/**
 * @brief Gestion du comportement des signaux (CTRL+C, CTRL+/)
 * @param signal_code Le code du signal reçu
 */
void	sig_handling(int signal_code)
{
	if (signal_code == SIGINT)
	{
		printf("Signal SIGINT (CTRL+C) detected. Exiting...\n"); // Pas le bon comportement pour l'instant (interrompt le programme et non le processus)
		exit(0);
	}
	else if (signal_code == SIGQUIT)
	{
		printf("Signal SIGQUIT (CTRL + \\) detected.\n");
		rl_replace_line("", 0); // Clear readline
		rl_on_new_line(); // Creer une nouvelle ligne
		rl_redisplay(); // Redisplay la nouvelle ligne
	}
	else
		printf("Unknown signal\n");
}

/**
* @brief Initialize and config sigaction structure
* @return The sigaction struct ready to use
* @todo Penser a ranger les fonctions pour les signaux proprement
*/
struct sigaction	signal_launching(void)
{
	struct sigaction sig_config;
	sigset_t signal_set;

	sig_config.sa_handler = sig_handling;
	sig_config.sa_flags = 0;

	sigemptyset(&signal_set);
	sigaddset(&signal_set, SIGINT); // CTRL + C
	sigaddset(&signal_set, SIGQUIT); // CTRL + backslash
	// sigaddset(&signal_set, SIGTERM); // CTRL + D
	sig_config.sa_mask = signal_set;
	return (sig_config);
}
