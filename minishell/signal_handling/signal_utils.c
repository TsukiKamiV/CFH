#include "../minishell.h"

// int	g_interrupted;
volatile sig_atomic_t sig_interrupt_flag;
// Volatile permet d'éviter que le compilateur "optimise" la variable en la mettant en cache. Evite apparemment les modifs asynchrones
// sig_atomic_t permet de garantir que l'écriture de la variable est "atomique" (pas de lecture/écriture simultanée) car signaux asynchrones ou autres

void heredoc_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		sig_interrupt_flag = 130;
		write(STDOUT_FILENO, "\n", 1);
		// Dans le contexte du heredoc, pas beosin de réafficher le prompt, à vérifier pour cas spécifiques
	}
	else if (sig == SIGQUIT)
	{
		write(STDOUT_FILENO, "Signal SIGQUIT (CTRL+\\) detected.\n", 35);
	}
}


/**
 * @brief Ignore les signaux SIGINT et SIGQUIT dans le processus parent
 * @param old_sigint Pointeur vers la structure de sigaction pour SIGINT
 * @param old_sigquit Pointeur vers la structure de sigaction pour SIGQUIT
 */
void ignore_signals_in_parent(struct sigaction *old_sigint, struct sigaction *old_sigquit)
{
	struct sigaction sa_ignore;

	sa_ignore.sa_handler = SIG_IGN;
	sa_ignore.sa_flags = 0;
	sigemptyset(&sa_ignore.sa_mask);

	sigaction(SIGINT, &sa_ignore, old_sigint);
	sigaction(SIGQUIT, &sa_ignore, old_sigquit);
}

/**
 * @brief Restaure les handlers de signaux précédents dans le processus parent
 */
void restore_signals_in_parent(struct sigaction *old_sigint, struct sigaction *old_sigquit)
{
	sigaction(SIGINT, old_sigint, NULL);
	sigaction(SIGQUIT, old_sigquit, NULL);
}

/**
 * @brief Gestion du comportement des signaux (CTRL+C, CTRL+/)
 * @param signal_code Le code du signal reçu
 *
 * Ce handler est utilisé lorsque le shell est en mode interactif (aucun enfant en cours).
 */
void sig_handling(int signal_code)
{
	if (signal_code == SIGINT)
	{
		sig_interrupt_flag = 130; // Indique qu'un CTRL+C a été reçu
		// Utilisation de write() car async-safe
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signal_code == SIGQUIT)
	{
		// Pour SIGQUIT, on affiche un message et on rafraîchit le prompt
		// Ne réagit pas encore parfaitement (devrait refresh le prompt si parent et "core dump" si enfant)
		write(STDOUT_FILENO, "Signal SIGQUIT (CTRL+\\) detected.\n", 35);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

/**
* @brief Initialize and config sigaction structure
* @return The sigaction struct ready to use
*/
struct sigaction	signal_launching(void)
{
	struct sigaction sig_config;
	sigset_t signal_set;

	sig_interrupt_flag = 0;

	sigemptyset(&signal_set);
	sigaddset(&signal_set, SIGINT); // CTRL + C
	sigaddset(&signal_set, SIGQUIT); // CTRL + backslash
	// sigaddset(&signal_set, SIGTERM); // CTRL + D

	sig_config.sa_handler = sig_handling; // On associe la fonction de gestion des signaux
	sig_config.sa_flags = 0; // On remet les flags à 0 (les flags permettent de modifier le comportement de sigaction)
	sig_config.sa_mask = signal_set; // On associe le masque de signaux à la structure sigaction (les signaux masqués ne seront pas pris en compte donc on peut les intercepter)
	return (sig_config);
}
