/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:13:35 by chansjeo          #+#    #+#             */
/*   Updated: 2024/06/17 15:23:47 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->fork);
	philo->right_fork->fork_id++;
	philo->right_fork->fork_id--;
	print_status(philo, PICKUP);
	pthread_mutex_lock(&philo->left_fork->fork);
	philo->left_fork->fork_id++;
	philo->left_fork->fork_id--;
	print_status(philo, PICKUP);
	set_long(&philo->philo_mtx, &philo->last_eat_time, \
					get_time(philo->info->start_time));
	print_status(philo, EAT);
	philo->eat_cnt += 1;
	if (philo->eat_cnt == get_long(&philo->philo_mtx, &philo->info->must_eat))
		philo->full = 1;
	usleep_for_philo(philo, philo->info->time_to_eat);
	pthread_mutex_unlock(&philo->left_fork->fork);
	pthread_mutex_unlock(&philo->right_fork->fork);
}

void	print_status(t_philo *philo, int status)
{
	long	cur_time;

	pthread_mutex_lock(&philo->info->print_mtx);
	cur_time = get_time(philo->info->start_time);
	if (status == PICKUP && !simulation_finished(philo->info))
		printf("%ld %d has taken a fork\n", cur_time, philo->id);
	else if (status == EAT && !simulation_finished(philo->info))
		printf("%ld %d is eating\n", cur_time, philo->id);
	else if (status == SLEEP && !simulation_finished(philo->info))
		printf("%ld %d is sleeping\n", cur_time, philo->id);
	else if (status == THINK && !simulation_finished(philo->info))
		printf("%ld %d is thinking\n", cur_time, philo->id);
	else if (status == DIED && !simulation_finished(philo->info))
		printf("%ld %d died\n", cur_time, philo->id);
	pthread_mutex_unlock(&philo->info->print_mtx);
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

void	usleep_for_philo(t_philo *philo, long m_sec)
{
	long	cur_time;

	cur_time = get_time(0);
	if (m_sec == 0)
		usleep(1);
	while (m_sec > get_time(cur_time))
	{
		if (get_bool(&philo->info->info_mtx, &philo->info->simul_end))
			break ;
		usleep(200);
	}
}
