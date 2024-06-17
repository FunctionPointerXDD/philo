/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 20:36:26 by chansjeo          #+#    #+#             */
/*   Updated: 2024/04/09 19:43:33 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_error_msg(char *str)
{
	ft_putstr_fd(str, 2);
	exit (-1);
}

int	init_info(t_info *info, char **argv)
{
	long	fork_num;

	if (get_arg(info, argv) < 0)
		return (ft_error_msg("Invalid argument!\n"));
	info->philo = safe_calloc(1, sizeof(t_philo));
	memset(info->philo, 0, sizeof(t_philo));
	info->philo->info = info;
	fork_num = info->philo_num;
	sem_unlink("/sem_fork");
	sem_unlink("/sem_print");
	sem_unlink("/sem_monitor");
	sem_unlink("/sem_flag");
	sem_unlink("/sem_time");
	info->sem_fork = sem_open("/sem_fork", O_CREAT | O_EXCL, 0644, fork_num);
	info->sem_print = sem_open("/sem_print", O_CREAT | O_EXCL, 0644, 1);
	info->sem_monitor = sem_open("/sem_monitor", O_CREAT | O_EXCL, 0644, 1);
	info->sem_time = sem_open("/sem_time", O_CREAT | O_EXCL, 0644, 1);
	info->sem_flag = sem_open("/sem_flag", O_CREAT | O_EXCL, 0644, 0);
	if (info->sem_fork == SEM_FAILED || info->sem_print == SEM_FAILED || \
		info->sem_monitor == SEM_FAILED || info->sem_flag == SEM_FAILED || \
		info->sem_time == SEM_FAILED)
		return (ft_error_msg("semaphore_failed\n"));
	return (0);
}

size_t	create_philo(t_info *info, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid > 0)
		return (pid);
	else if (pid < 0)
	{
		ft_error_msg("fork() failed\n");
		kill(0, SIGKILL);
	}
	info->philo->id = i;
	sem_wait(info->sem_flag);
	pthread_create(&info->monitor, 0, monitoring, info);
	pthread_detach(info->monitor);
	routine(info->philo);
	return (0);
}

void	philosopher(t_info *info)
{
	pid_t	*pid;
	int		i;
	long	philo_num;

	philo_num = info->philo_num;
	if (philo_num > 200)
		philo_num = 200;
	pid = safe_calloc(philo_num, sizeof(pid_t));
	memset(pid, 0, sizeof(pid_t) * philo_num);
	info->start_time = get_time(0);
	i = -1;
	while (++i < philo_num)
		pid[i] = create_philo(info, i + 1);
	i = -1;
	while (++i < philo_num)
		sem_post(info->sem_flag);
	wait_proc(info, pid);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc != 5 && argc != 6)
		return (ft_error_msg("Invalid argument\n"));
	init_info(&info, argv);
	philosopher(&info);
	return (0);
}
