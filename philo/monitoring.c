/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 16:31:29 by chansjeo          #+#    #+#             */
/*   Updated: 2024/06/17 15:07:24 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitoring(void *data)
{
	t_info	*info;
	int		i;

	info = (t_info *)data;
	if (info->philo_num == 0)
		return (0);
	while (get_bool(&info->info_mtx, &info->simul_start) != 1)
		;
	while (!simulation_finished(info))
	{
		i = 0;
		while (i < info->philo_num)
		{
			if (philo_died(&info->philos[i]))
			{
				print_status(&info->philos[i], DIED);
				set_bool(&info->info_mtx, &info->simul_end, 1);
			}
			i++;
			usleep(100);
		}
	}
	return (0);
}

int	philo_died(t_philo *philo)
{
	long	cur_time;
	long	pass_time;

	cur_time = get_time(philo->info->start_time);
	pass_time = cur_time - get_long(&philo->philo_mtx, &philo->last_eat_time);
	if (pass_time > philo->info->time_to_die)
		return (1);
	return (0);
}

int	simulation_finished(t_info *info)
{
	if (get_bool(&info->info_mtx, &info->simul_end) == 1)
		return (1);
	return (0);
}

