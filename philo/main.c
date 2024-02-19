#include "philosopher.h"

void f()
{
	system("leaks philo");
}

int main(int argc, char **argv)
{
	t_philo *philo;
	t_arg arg;
	t_mutex mutex;

	atexit(f);
	arg = init_argument(argc, argv);
	if (arg.num_of_philo == -1)
		return (err(NULL, NULL));
	mutex = init_mutex(&arg);
	if (mutex.fork == NULL || mutex.last_eat_time_mutex == NULL)
		return (err(NULL, NULL));
	philo = init_philo(&arg, &mutex);
	if (philo == NULL)
		return (err(&mutex, NULL));
	if (philo_thread_create(philo) == FAIL)
		return (err(&mutex, philo));
	free(mutex.fork);
	free(mutex.last_eat_time_mutex);
	free(philo);
	return 0;
}