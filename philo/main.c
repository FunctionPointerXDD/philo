/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 20:59:59 by chansjeo          #+#    #+#             */
/*   Updated: 2024/06/17 15:05:44 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	adjust_start_time(t_philo *philo)
{
	long	delay;
	long	philo_id;

	delay = philo->info->time_to_eat;
	philo_id = philo->id;
	if (delay <= 10)
		delay = 11;
	if (philo->info->philo_num % 2 != 0)
	{
		if (philo_id == philo->info->philo_num)
		{
			delay -= 10;
			usleep_for_philo(philo, delay);
			return ;
		}
		else if (philo_id % 2 != 0)
			usleep_for_philo(philo, delay);
	}
	else
	{
		if (philo_id % 2 != 0)
			usleep_for_philo(philo, delay);
	}
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->info->must_eat == 0)
		return (0);
	while (get_bool(&philo->info->info_mtx, &philo->info->simul_start) != 1)
		;
	set_long(&philo->philo_mtx, &philo->last_eat_time, \
					get_time(philo->info->start_time));
	adjust_start_time(philo);
	while (simulation_finished(philo->info) != 1)
	{
		eat(philo);
		if (philo->id == 1 && philo->full == 1)
		{
			set_bool(&philo->info->info_mtx, &philo->info->simul_end, 1);
			break ;
		}
		print_status(philo, SLEEP);
		usleep_for_philo(philo, philo->info->time_to_sleep);
		print_status(philo, THINK);
	}
	return (0);
}

void	*lonely_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->info->must_eat == 0)
		return (0);
	while (get_bool(&philo->info->info_mtx, &philo->info->simul_start) != 1)
		;
	set_long(&philo->philo_mtx, &philo->last_eat_time, \
						get_time(philo->info->start_time));
	while (1)
	{
		if (simulation_finished(philo->info))
			break ;
		pthread_mutex_lock(&philo->left_fork->fork);
		print_status(philo, PICKUP);
		pthread_mutex_unlock(&philo->left_fork->fork);
		usleep_for_philo(philo, philo->info->time_to_die + 10);
	}
	return (0);
}

void	philosopher(t_info *info)
{
	int	i;

	i = 0;
	if (info->philo_num == 0)
		return ;
	if (info->philo_num == 1)
		pthread_create(&info->philos[i].thread_id, 0, \
						lonely_philo, &info->philos[i]);
	else
	{
		while (i < info->philo_num)
		{
			pthread_create(&info->philos[i].thread_id, 0, \
								routine, &info->philos[i]);
			i++;
		}
	}
	pthread_create(&info->monitor, 0, monitoring, info);
	set_long(&info->info_mtx, &info->start_time, get_time(0));
	set_bool(&info->info_mtx, &info->simul_start, 1);
	i = 0;
	while (i < info->philo_num)
		pthread_join(info->philos[i++].thread_id, 0);
	set_bool(&info->info_mtx, &info->simul_end, 1);
	pthread_join(info->monitor, 0);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("invalid argv!\n", 2);
		return (1);
	}
	if (init_routine(&info, argv) < 0)
		return (1);
	philosopher(&info);
	clear_all(&info);
	return (0);
}

