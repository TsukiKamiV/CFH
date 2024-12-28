#include "../includes/philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;
	
	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		pthread_mutex_lock(&philo->right_fork->mutex);
		printf("Philosopher %d has eaten.\n", philo->philo_id);
		pthread_mutex_unlock(&philo->left_fork->mutex);
		pthread_mutex_unlock(&philo->right_fork->mutex);
		printf("Philosopher %d has finished eating.\n", philo->philo_id);
		printf("Philosopher %d is sleeping.\n", philo->philo_id);
		usleep(1000000); // Simulate sleeping (1 second)
		
		// Thinking
		printf("Philosopher %d is thinking.\n", philo->philo_id);
		usleep(1000000); // Simulate thinking (1 second)
	}
	return (NULL);
}
