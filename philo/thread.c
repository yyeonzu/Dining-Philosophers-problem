#include "philosopher.h"

int philo_thread_join(pthread_t *thread, t_philo *philo)
{
	int i;

	i = 0;
	while (i < philo->arg->num_of_philo)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
	return (0);
}

int philo_thread_create(t_philo *philo)
{
	int i;
	int msec;
	pthread_t *thread;

	thread = malloc(sizeof(pthread_t) * philo->arg->num_of_philo);
	if (!thread)
		return (FAIL);
	i = 0;
	while (i < philo->arg->num_of_philo)
	{
		msec = get_time();
		philo[i].info.start_time = msec;
		philo[i].info.last_eat_time = msec;
		pthread_create(&thread[i], NULL, dining, &philo[i]);
		i++;
	}
	monitor(philo);
	philo_thread_join(thread, philo);
	free(thread);
	return (0);
}