/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 20:42:02 by chansjeo          #+#    #+#             */
/*   Updated: 2024/04/09 19:41:24 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <semaphore.h>
# include <pthread.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <signal.h>

# define INT_MAX 2147483647

typedef enum s_state
{
	PICKUP,
	EAT,
	SLEEP,
	THINK,
	DIED,	
	FULL
}	t_state;

typedef struct s_info	t_info;
typedef struct s_philo	t_philo;

typedef struct s_info
{
	long			philo_num;
	long			time_to_eat;
	long			time_to_die;
	long			time_to_sleep;
	long			must_eat;
	long			start_time;
	sem_t			*sem_fork;
	sem_t			*sem_print;
	sem_t			*sem_monitor;
	sem_t			*sem_flag;
	sem_t			*sem_time;
	pthread_t		monitor;
	t_philo			*philo;
}	t_info;

typedef struct s_philo
{
	int				id;
	long			last_eat_time;
	long			eat_cnt;
	int				full;
	t_info			*info;
}	t_philo;

void	*monitoring(void *data);
int		philo_died(t_philo *philo);
int		simulation_finished(t_info *info);

long	get_time(long start_time);
void	usleep_for_philo(long m_sec);

void	eat(t_philo *philo);
void	adjust_start_time(t_philo *philo);
void	routine(t_philo *philo);

int		ft_putstr_fd(char *str, int fd);
int		ft_strlen(const char *str);
int		is_digit(const char *str);
int		get_arg(t_info *info, char **argv);
long	ft_atol(const char *str);

void	*safe_calloc(size_t count, size_t size);
void	print_status(t_philo *philo, int status);
int		ft_error_msg(char *str);
void	wait_proc(t_info *info, pid_t *pid);
void	clear_all(t_info *info, pid_t *pid);

#endif
