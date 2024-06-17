/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 16:00:25 by chansjeo          #+#    #+#             */
/*   Updated: 2024/06/17 15:06:55 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clear_all(t_info *info)
{
	int	i;
	int	philo_nbr;

	philo_nbr = info->philo_num;
	i = 0;
	while (i < philo_nbr)
	{
		pthread_mutex_destroy(&info->philos[i].philo_mtx);
		pthread_mutex_destroy(&info->forks[i].fork);
		i++;
	}
	pthread_mutex_destroy(&info->print_mtx);
	pthread_mutex_destroy(&info->info_mtx);
	free(info->forks);
	free(info->philos);
}

