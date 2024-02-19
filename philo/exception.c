/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeojung <yeojung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 15:41:50 by yeojung           #+#    #+#             */
/*   Updated: 2023/12/17 17:15:07 by yeojung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int err(t_mutex *mutex, t_philo *philo)
{
	if (mutex->fork != NULL)
		free(mutex->fork);
	if (mutex->last_eat_time_mutex != NULL)
		free(mutex->last_eat_time_mutex);
	if (philo != NULL)
		free(philo);
	printf("Error\n");
	return (ERROR);
}