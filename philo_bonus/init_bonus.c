/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:38:49 by chansjeo          #+#    #+#             */
/*   Updated: 2024/04/04 12:40:24 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
