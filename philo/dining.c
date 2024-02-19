#include "philosopher.h"

int eating(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex->last_eat_time_mutex);
	philo->info.last_eat_time = get_time();
	pthread_mutex_unlock(philo->mutex->last_eat_time_mutex);
	if (print_act(philo, "is eating") == FAIL)
		return (FAIL);
	philo->info.eat_cnt++;
	if (philo->info.eat_cnt == philo->arg->must_eat_cnt)
	{
		pthread_mutex_lock(&philo->mutex->dead_mutex);
		philo->mutex->dead++;
		pthread_mutex_unlock(&philo->mutex->dead_mutex);
	}
	int end_time = philo->info.last_eat_time + philo->arg->time_to_eat;
	a_few_moments_later(end_time);
	return (SUCCESS);
}

int sleeping(t_philo *philo)
{
	if (print_act(philo, "is sleeping") == FAIL)
		return (FAIL);
	int end_time = philo->info.last_eat_time + philo->arg->time_to_eat + philo->arg->time_to_sleep;
	a_few_moments_later(end_time);
	return (SUCCESS);
}

int thinking(t_philo *philo)
{
	if (print_act(philo, "is thinking") == FAIL)
		return (FAIL);
	return (SUCCESS);
}

int pick_up_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex->fork[philo->info.left]);
	if (print_act(philo, "has taken a fork") == FAIL || philo->arg->num_of_philo == 1)
	{
		pthread_mutex_unlock(&philo->mutex->fork[philo->info.left]);
		return (FAIL);
	}

	pthread_mutex_lock(&philo->mutex->fork[philo->info.right]);
	if (print_act(philo, "has taken a fork") == FAIL)
	{
		pthread_mutex_unlock(&philo->mutex->fork[philo->info.right]);
		pthread_mutex_unlock(&philo->mutex->fork[philo->info.left]);
		return (FAIL);
	}
	return (SUCCESS);
}

void put_down_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->mutex->fork[philo->info.left]);
	pthread_mutex_unlock(&philo->mutex->fork[philo->info.right]);
	return;
}

void *dining(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 1)
		usleep(200);
	while (1)
	{
		if (pick_up_fork(philo) == FAIL)
			break;
		if (eating(philo) == FAIL)
			break;
		put_down_fork(philo);
		if (sleeping(philo) == FAIL)
			break;
		if (thinking(philo) == FAIL)
			break;
	}
	return (NULL);
}