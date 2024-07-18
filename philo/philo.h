/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:46:31 by chansjeo          #+#    #+#             */
/*   Updated: 2024/06/27 13:52:47 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define INT_MAX 2147483647

typedef enum s_state
{
	PICKUP,
	EAT,
	SLEEP,
	THINK,
	DIED	
}	t_state;

typedef struct s_info	t_info;
typedef struct s_philo	t_philo;

typedef struct s_fork
{
	int				fork_id;
	pthread_mutex_t	fork;
}	t_fork;

typedef struct s_info
{
	long			philo_num;
	long			time_to_eat;
	long			time_to_die;
	long			time_to_sleep;
	long			must_eat;
	long			start_time;
	int				simul_start;
	int				simul_end;
	pthread_t		monitor;
	t_fork			*forks;
	t_philo			*philos;
	pthread_mutex_t	print_mtx;
	pthread_mutex_t	info_mtx;
}	t_info;

typedef struct s_philo
{
	int				id;
	pthread_t		thread_id;
	long			last_eat_time;
	long			eat_cnt;
	int				full;
	t_info			*info;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_mutex_t	philo_mtx;
}	t_philo;

/*init.c*/
int		get_arg(t_info *info, char **argv);
int		init_routine(t_info	*info, char **argv);
void	assign_value(t_info *info);
void	fork_position(t_philo *philo, t_fork *fork, int i);

/* routine.c */
void	eat(t_philo *philo);
void	usleep_for_philo(t_philo *philo, long m_sec);
long	get_time(long pass_time);
void	print_status(t_philo *philo, int status);
int		full_philos(t_philo *philo);
void	think(t_philo *philo);

/* monitoring */
void	*monitoring(void *data);
int		philo_died(t_philo *philo);
int		simulation_finished(t_info *info);

/* utils.c */
int		ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
long	ft_atol(const char *str);
int		ft_putstr_fd(char *str, int fd);
int		free_all(t_info *info, int cnt);

/* utils_2.c*/
void	clear_all(t_info *info);

/* safe_access.c */
void	set_long(pthread_mutex_t *mtx, long *set, long data);
long	get_long(pthread_mutex_t *mtx, long *data);
void	set_bool(pthread_mutex_t *mtx, int *set, int data);
int		get_bool(pthread_mutex_t *mtx, int *data);

#endif
