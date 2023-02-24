/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 23:13:51 by asasada           #+#    #+#             */
/*   Updated: 2023/02/25 02:54:06 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <sys/wait.h>
# include <signal.h>

# include <fcntl.h>
# include <semaphore.h>

# define ERROR -1
# define FORK 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DIED 4

# define FALSE 0
# define TRUE 1

# define THREAD_CREATION_BUFFER 20

typedef struct s_ctl
{
	int				pop;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				opt_count;
	int				has_opt;
	int				num_finished_eating;
	int				philo_dead;
	int				mtx_destroy;
	struct s_philo	*philos;
	int				*pid;
	pthread_t		*th;
	pthread_mutex_t	*mtx;
	pthread_mutex_t	*pmtx;
	unsigned long	time_start;

	pthread_t		thread_dead;
	pthread_t		thread_fin;

	sem_t			*sem_fork;
	sem_t			*sem_print;
	sem_t			*sem_dead;
	sem_t			*sem_finished;
	sem_t			*sem_chair;
	sem_t			**sem_philos;
	char			**sem_names;
	int				sem_name_count;
	int				num_chairs;
}	t_ctl;

typedef struct s_philo
{
	int				idx;
	int				times_eaten;
	struct s_ctl	*ctl;
	unsigned long	time_last_eat;
	pthread_t		thread;
}	t_philo;

// inputs_bonus.c
int				ps_atoi(char *str, int *err);
int				ps_isnumeric(char *str);
int				read_args(t_ctl *ctl, int argc, char **argv);
int				process_inputs(t_ctl *ctl, int argc, char **argv);

// utils_bonus.c
unsigned long	ms_time(void);
int				print_alive_messages(int message, t_philo *philo, \
unsigned long time_ms);
int				print_message(int message, t_philo *philo);
void			philo_sleep(unsigned long milli_secs);

// philo_bonus.c
int				philo_routine(t_philo *philo);
void			*monitor_philo(void *p);
int				philo_process(t_ctl *ctl, int i);
int				start_process(t_ctl *ctl);

// init_vars_bonus.c
int				init_semaphore(t_ctl *ctl);
int				destroy_semaphore(t_ctl *ctl);
int				init_vars(t_ctl *ctl);

// sem_philos.c
int				free_names(t_ctl *ctl, int i);
int				init_philo_sems(t_ctl *ctl);
int				destroy_philo_sems(t_ctl *ctl);

// libftstuff
size_t			ft_strlen(const char *s);
char			*ft_itoa(int n);
char			*ft_strjoin(char const *s1, char const *s2);

#endif
