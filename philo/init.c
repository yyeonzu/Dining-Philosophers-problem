#include "philosopher.h"

t_arg init_argument(int argc, char **argv)
{
	t_arg arg;

	arg.num_of_philo = -1;
	if (argc != 5 && argc != 6)
		return (arg);
	arg.num_of_philo = ft_atoi(argv[1]);
	arg.time_to_die = ft_atoi(argv[2]);
	arg.time_to_eat = ft_atoi(argv[3]);
	arg.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		arg.must_eat_cnt = ft_atoi(argv[5]);
	else
		arg.must_eat_cnt = -1;
	return (arg);
}

t_mutex init_mutex(t_arg *arg)
{
	t_mutex mutex;
	int i;

	mutex.fork = malloc(sizeof(pthread_mutex_t) * arg->num_of_philo);
	mutex.last_eat_time_mutex = malloc(sizeof(pthread_mutex_t) * (arg->num_of_philo));
	if (!mutex.fork || !mutex.last_eat_time_mutex)
		return (mutex);
	i = 0;
	while (i < arg->num_of_philo)
	{
		pthread_mutex_init(&mutex.fork[i], NULL);
		pthread_mutex_init(&mutex.last_eat_time_mutex[i], NULL);
		i++;
	}
	pthread_mutex_init(&mutex.dead_mutex, NULL);
	mutex.dead = 0;
	return (mutex);
}

t_info init_info(t_arg *arg, int id)
{
	t_info info;

	info.left = id;
	info.right = (id + 1) % arg->num_of_philo;
	info.eat_cnt = 0;
	info.start_time = 0;
	info.last_eat_time = 0;
	return (info);
}

t_philo *init_philo(t_arg *arg, t_mutex *mutex)
{
	int i = 0;
	t_philo *philo;

	philo = malloc(sizeof(t_philo) * arg->num_of_philo);
	if (!philo)
		return (NULL);
	while (i < arg->num_of_philo)
	{
		philo[i].id = i;
		philo[i].arg = arg;
		philo[i].mutex = mutex;
		philo[i].info = init_info(arg, philo[i].id);
		i++;
	}
	return (philo);
}
