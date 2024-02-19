#include "philosopher.h"

int print_act(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->mutex->dead_mutex);
	if (philo->mutex->dead == philo->arg->num_of_philo)
	{
		pthread_mutex_unlock(&philo->mutex->dead_mutex);
		return (FAIL);
	}
	printf("%d %d %s\n", get_time() - philo->info.start_time, philo->id + 1, str);
	pthread_mutex_unlock(&philo->mutex->dead_mutex);
	return (SUCCESS);
}