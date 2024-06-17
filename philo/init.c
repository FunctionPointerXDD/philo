/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 16:27:42 by chansjeo          #+#    #+#             */
/*   Updated: 2024/06/17 15:06:45 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_arg(t_info *info, char **argv)
{
	info->philo_num = ft_atol(argv[1]);
	if (info->philo_num < 0)
		return (-1);
	info->time_to_die = ft_atol(argv[2]);
	if (info->time_to_eat < 0)
		return (-1);
	info->time_to_eat = ft_atol(argv[3]);
	if (info->time_to_die < 0)
		return (-1);
	info->time_to_sleep = ft_atol(argv[4]);
	if (info->time_to_sleep < 0)
		return (-1);
	if (argv[5])
		info->must_eat = ft_atol(argv[5]);
	else
		info->must_eat = INT_MAX;
	if (info->must_eat < 0)
		return (-1);
	return (0);
}

void	fork_position(t_philo *philo, t_fork *fork, int i)
{
	long	philo_num;

	philo_num = philo->info->philo_num;
	philo->left_fork = &fork[i];
	philo->right_fork = &fork[(i + 1) % philo_num];
	/*
	if (i % 2 != 0)
	{
		philo->left_fork = &fork[(i + 1) % philo_num];
		philo->right_fork = &fork[i];
	}
	*/
}

void	assign_value(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->philo_num)
	{
		pthread_mutex_init(&info->forks[i].fork, 0);
		info->forks[i].fork_id = i + 1;
		i++;
	}
	i = 0;
	while (i < info->philo_num)
	{
		info->philos[i].id = i + 1;
		info->philos[i].full = 0;
		pthread_mutex_init(&info->philos[i].philo_mtx, 0);
		info->philos[i].info = info;
		fork_position(&info->philos[i], info->forks, i);
		i++;
	}
	pthread_mutex_init(&info->print_mtx, 0);
	pthread_mutex_init(&info->info_mtx, 0);
}

int	init_routine(t_info	*info, char **argv)
{
	if (get_arg(info, argv) < 0)
		return (-1);
	info->philos = malloc(sizeof(t_philo) * info->philo_num);
	if (!info->philos)
		return (-1);
	info->forks = malloc(sizeof(t_fork) * info->philo_num);
	if (!info->forks)
		return (-1);
	memset(info->philos, 0, sizeof(t_philo) * info->philo_num);
	memset(info->forks, 0, sizeof(t_fork) * info->philo_num);
	assign_value(info);
	info->simul_end = 0;
	info->simul_start = 0;
	return (0);
}

