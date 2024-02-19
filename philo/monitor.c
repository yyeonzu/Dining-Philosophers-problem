#include "philosopher.h"

int is_dead(t_philo philo)
{
	pthread_mutex_lock(philo.mutex->last_eat_time_mutex);
	int cur_time = get_time();
	if (cur_time - philo.info.last_eat_time > philo.arg->time_to_die)
	{
		pthread_mutex_unlock(philo.mutex->last_eat_time_mutex);
		pthread_mutex_lock(&philo.mutex->dead_mutex);
		philo.mutex->dead = philo.arg->num_of_philo;
		printf("%d %d died\n", cur_time - philo.info.start_time, philo.id + 1);
		pthread_mutex_unlock(&philo.mutex->dead_mutex);
		return (TRUE);
	}
	pthread_mutex_unlock(philo.mutex->last_eat_time_mutex);
	return (FALSE);
}

int is_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex->dead_mutex);
	if (philo->mutex->dead == philo->arg->num_of_philo)
	{
		pthread_mutex_unlock(&philo->mutex->dead_mutex);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->mutex->dead_mutex);
	return (FALSE);
}

void monitor(t_philo *philo)
{
	int i;
	while (1)
	{
		i = 0;
		// printf("monitor while\n");
		if (is_full(philo))
			return;
		// printf("monitor while2\n");
		while (i < philo->arg->num_of_philo)
		{
			if (is_dead(philo[i]))
				return;
			i++;
		}
	}
}