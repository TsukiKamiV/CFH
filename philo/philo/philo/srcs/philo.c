
#include "../includes/philo.h"

int main(int argc, const char **argv)
{
	int				i;
	long			n;
	t_philo			*philo;
	t_simulation	*sim;
	
	if (check_args(argc, argv, &n) == 0)
		return (1);
	sim = malloc(sizeof(t_simulation));
	if (!sim)
		return (1);
	sim->philo_num = (int)n;
	philo = malloc(sizeof(t_philo) * sim->philo_num);
	if (!philo)
	{
		free_structs(philo, sim);
		return (1);
	}
	if (init_simulation(sim, argv, philo) == 1)
	{
		free_structs(philo, sim);
		return (1);
	}
	i = 0;
	while (i < sim->philo_num)
	{
		philo[i].sim_data = sim;
		i++;
	}
	if (init_philo(sim, philo) != 0)
	{
		free_structs(philo, sim);
		return (1);
	}
	if (sim->philo_num > 1)
		pthread_create(&sim->monitor_thread, NULL, monitor_sim_routine, sim);
	i = 0;
	while (i < sim->philo_num)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	if (sim->philo_num > 1)
		pthread_join(sim->monitor_thread, NULL);
	i = 0;
	free_structs(philo, sim);
	return (0);
}
