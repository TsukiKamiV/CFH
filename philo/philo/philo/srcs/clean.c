#include "../includes/philo.h"


void	cleanup_simulation(t_simulation *sim, int flags)
{
	if (sim == NULL)
		return ;
	if ((flags & CLEAN_FORKS) && sim->forks)
		free (sim->forks);
	if (flags & CLEAN_END_MUTEX)
		pthread_mutex_destroy(&sim->end_mutex);
	if (flags & CLEAN_PRINT_MUTEX)
		pthread_mutex_destroy(&sim->print_mutex);
}
