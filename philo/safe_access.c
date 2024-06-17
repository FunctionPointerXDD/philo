/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_access.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:02:39 by chansjeo          #+#    #+#             */
/*   Updated: 2024/06/17 15:07:28 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_long(pthread_mutex_t *mtx, long *set, long data)
{
	pthread_mutex_lock(mtx);
	*set = data;
	pthread_mutex_unlock(mtx);
}

long	get_long(pthread_mutex_t *mtx, long *data)
{
	long	ret_data;

	pthread_mutex_lock(mtx);
	ret_data = *data;
	pthread_mutex_unlock(mtx);
	return (ret_data);
}

void	set_bool(pthread_mutex_t *mtx, int *set, int data)
{
	pthread_mutex_lock(mtx);
	*set = data;
	pthread_mutex_unlock(mtx);
}

int	get_bool(pthread_mutex_t *mtx, int *data)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(mtx);
	ret = *data;
	if (ret)
		ret = 1;
	pthread_mutex_unlock(mtx);
	return (ret);
}
