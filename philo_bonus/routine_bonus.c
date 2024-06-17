/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 22:17:04 by chansjeo          #+#    #+#             */
/*   Updated: 2024/04/09 19:41:58 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eat(t_philo *philo)
{
	sem_wait(philo->info->sem_fork);
	print_status(philo, PICKUP);
	sem_wait(philo->info->sem_fork);
	print_status(philo, PICKUP);
	sem_wait(philo->info->sem_time);
	philo->last_eat_time = get_time(philo->info->start_time);
	sem_post(philo->info->sem_time);
	print_status(philo, EAT);
	philo->eat_cnt += 1;
	if (philo->eat_cnt == philo->info->must_eat)
		philo->full = 1;
	usleep_for_philo(philo->info->time_to_eat);
	sem_post(philo->info->sem_fork);
	sem_post(philo->info->sem_fork);
}

void	adjust_start_time(t_philo *philo)
{
	long	delay;

	delay = philo->info->time_to_eat;
	if (delay <= 10)
		delay = 11;
	if (philo->info->philo_num % 2 != 0)
	{
		if (philo->id == 1)
		{
			delay += 10;
			usleep_for_philo(delay);
		}
		else if (philo->id % 2 != 0)
			usleep_for_philo(delay);
	}
	else
	{
		if (philo->id % 2 != 0)
			usleep_for_philo(delay);
	}
}

void	routine(t_philo *philo)
{
	sem_wait(philo->info->sem_time);
	philo->last_eat_time = get_time(philo->info->start_time);
	sem_post(philo->info->sem_time);
	if (philo->id % 2 != 0)
		adjust_start_time(philo);
	while (1)
	{
		eat(philo);
		if (philo->id == 1 && philo->full == 1)
			exit(FULL);
		print_status(philo, SLEEP);
		usleep_for_philo(philo->info->time_to_sleep);
		print_status(philo, THINK);
	}
}
