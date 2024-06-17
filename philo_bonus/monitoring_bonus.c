/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:14:03 by chansjeo          #+#    #+#             */
/*   Updated: 2024/04/09 19:43:59 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitoring(void *data)
{
	t_info	*info;

	info = (t_info *)data;
	if (info->philo_num == 0)
		return (0);
	while (1)
	{
		sem_wait(info->sem_monitor);
		if (philo_died(info->philo))
		{
			sem_post(info->sem_monitor);
			exit(DIED);
		}
		sem_post(info->sem_monitor);
		usleep(1000);
	}
	return (0);
}

int	philo_died(t_philo *philo)
{
	long	cur_time;
	long	pass_time;

	cur_time = get_time(philo->info->start_time);
	sem_wait(philo->info->sem_time);
	pass_time = cur_time - philo->last_eat_time;
	sem_post(philo->info->sem_time);
	if (pass_time > philo->info->time_to_die)
		return (1);
	return (0);
}

long	get_time(long start_time)
{
	struct timeval	timestamp;
	long			cur_time;

	cur_time = 0;
	gettimeofday(&timestamp, 0);
	cur_time = (timestamp.tv_sec * 1000 + \
				timestamp.tv_usec / 1000) - start_time;
	return (cur_time);
}

void	usleep_for_philo(long m_sec)
{
	long	cur_time;

	cur_time = get_time(0);
	if (m_sec == 0)
		usleep(1);
	while (m_sec > get_time(cur_time))
		usleep(400);
}
