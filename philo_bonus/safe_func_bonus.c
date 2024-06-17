/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_func_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:09:52 by chansjeo          #+#    #+#             */
/*   Updated: 2024/04/09 19:42:36 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*safe_calloc(size_t count, size_t size)
{
	void	*addr;

	if (count != 0 && size > (size_t)(-1) / count)
		return (0);
	addr = malloc(count * size);
	if (!addr)
	{
		ft_error_msg("malloc_fail\n");
		exit(-1);
	}
	memset(addr, 0, (count * size));
	return (addr);
}

void	print_status(t_philo *philo, int status)
{
	long	cur_time;

	cur_time = get_time(philo->info->start_time);
	sem_wait(philo->info->sem_print);
	if (status == PICKUP)
		printf("%ld %d has taken a fork\n", cur_time, philo->id);
	else if (status == EAT)
		printf("%ld %d is eating\n", cur_time, philo->id);
	else if (status == SLEEP)
		printf("%ld %d is sleeping\n", cur_time, philo->id);
	else if (status == THINK)
		printf("%ld %d is thinking\n", cur_time, philo->id);
	else if (status == DIED)
		printf("%ld %d died\n", cur_time, philo->id);
	sem_post(philo->info->sem_print);
}

void	clear_all(t_info *info, pid_t *pid)
{
	int	i;

	i = 0;
	while (i < info->philo_num)
		kill(pid[i++], SIGKILL);
	free(pid);
	sem_close(info->sem_fork);
	sem_close(info->sem_print);
	sem_close(info->sem_time);
	sem_close(info->sem_flag);
	sem_close(info->sem_monitor);
	sem_unlink("/sem_fork");
	sem_unlink("/sem_print");
	sem_unlink("/sem_time");
	sem_unlink("/sem_flag");
	sem_unlink("/sem_monitor");
	free(info->philo);
}

void	wait_proc(t_info *info, pid_t *pid)
{
	pid_t	w_pid;
	int		wstatus;
	int		i;

	while (1)
	{
		w_pid = waitpid(-1, &wstatus, 0);
		if (w_pid <= 0)
			break ;
		if (WIFEXITED(wstatus))
		{
			if (WEXITSTATUS(wstatus) == DIED)
			{
				i = 0;
				while (pid[i++] != w_pid)
					;
				info->philo->id = i;
				print_status(info->philo, DIED);
				clear_all(info, pid);
			}
			else if (WEXITSTATUS(wstatus) == FULL)
				clear_all(info, pid);
			break ;
		}
	}
}
