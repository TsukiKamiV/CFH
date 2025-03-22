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
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	// pas beosin de gerer les autres ?
}


/**
 * @brief Ignore les signaux SIGINT et SIGQUIT dans le processus parent
 * @param old_sigint Pointeur vers la structure de sigaction pour SIGINT
 * @param old_sigquit Pointeur vers la structure de sigaction pour SIGQUIT
 */
// void ignore_signals_in_parent(struct sigaction *old_sigint, struct sigaction *old_sigquit)
// {
// 	struct sigaction sa_ignore;

// 	sa_ignore.sa_handler = SIG_IGN;
// 	sa_ignore.sa_flags = 0;
// 	sigemptyset(&sa_ignore.sa_mask);

// 	sigaction(SIGINT, &sa_ignore, old_sigint);
// 	sigaction(SIGQUIT, &sa_ignore, old_sigquit);
// }


// Ignorer les signaux SIGINT et SIGQUIT pendant le waitpid du parent
// Sauvegarde des handlers pr"cédents (old_sa_int et old_sa_quit = SIGINT et SIGQUIT)
void ignore_signals_in_parent(struct sigaction *old_sa_int, struct sigaction *old_sa_quit)
{
	struct sigaction sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	sigaction(SIGINT, NULL, old_sa_int);
	sigaction(SIGQUIT, NULL, old_sa_quit);

	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

// Restaurer les handlers des signaux SIGINT et SIGQUIT après les avoir save avec ignore
// "const" pour éviter de modifier les structures originales
void restore_signals_in_parent(const struct sigaction *old_sa_int, const struct sigaction *old_sa_quit)
{
	sigaction(SIGINT, (struct sigaction *)old_sa_int, NULL);
	sigaction(SIGQUIT, (struct sigaction *)old_sa_quit, NULL);
}


/**
 * @brief Gestion du comportement des signaux (CTRL+C, CTRL+/)
 * @param signal_code Le code du signal reçu
 *
 * Ce handler est utilisé lorsque le shell est en mode interactif (aucun enfant en cours).
 */
// void sig_handling(int signal_code)
// {
// 	if (signal_code == SIGINT)
// 	{
// 		sig_interrupt_flag = 130; // Indique qu'un CTRL+C a été reçu
// 		// Utilisation de write() car async-safe
// 		write(STDOUT_FILENO, "\n", 1);
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 		rl_redisplay();
// 	}
// 	else if (signal_code == SIGQUIT)
// 	{
// 		// Pour SIGQUIT, on affiche un message et on rafraîchit le prompt
// 		// Ne réagit pas encore parfaitement (devrait refresh le prompt si parent et "core dump" si enfant)
// 		write(STDOUT_FILENO, "Signal SIGQUIT (CTRL+\\) detected.\n", 35);
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 		rl_redisplay();
// 	}
// }

/**
* @brief Initialize and config sigaction structure
* @return The sigaction struct ready to use
*/
// struct sigaction	signal_launching(void)
// {
// 	struct sigaction sig_config;
// 	sigset_t signal_set;

// 	sig_interrupt_flag = 0;

// 	sigemptyset(&signal_set);
// 	sigaddset(&signal_set, SIGINT); // CTRL + C
// 	sigaddset(&signal_set, SIGQUIT); // CTRL + backslash
// 	// sigaddset(&signal_set, SIGTERM); // CTRL + D

// 	sig_config.sa_handler = sig_handling; // On associe la fonction de gestion des signaux
// 	sig_config.sa_flags = 0; // On remet les flags à 0 (les flags permettent de modifier le comportement de sigaction)
// 	sig_config.sa_mask = signal_set; // On associe le masque de signaux à la structure sigaction (les signaux masqués ne seront pas pris en compte donc on peut les intercepter)
// 	return (sig_config);
// }



static void sig_handling(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		sig_interrupt_flag = 130;
		// Trouver comment gérer l'exit status !!
	}
	else if (sig == SIGQUIT)
	{
		// Aucune réaction en cas de CTRL+backslash
		// write(STDOUT_FILENO, "Signal SIGQUIT (CTRL+\\) detected.\n", 35);
		return ;
	}
}

struct sigaction signal_launching(void)
{
	struct sigaction sa;

	sa.sa_handler = &sig_handling;
	// RESTART permet de relancer les appels systèmes interrompus par un signal comme read, mettre 0 si on ne souhaite pas ce comportement
	// Ca peut être préférable pour que readline retourne null et qu'on le relance dans la mainloop ?
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);

	return sa;
}
