/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:22:44 by asasada           #+#    #+#             */
/*   Updated: 2023/01/05 15:22:44 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <stdbool.h>

# define ERROR -1
# define FORK 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DIED 4

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
	pthread_t		*th;
	pthread_mutex_t	*mtx;
	pthread_mutex_t	*pmtx;
	pthread_mutex_t	*tmtx;
	unsigned long	time_start;
}	t_ctl;

typedef struct s_philo
{
	int				idx;
	int				l_fork;
	int				r_fork;
	int				times_eaten;
	struct s_ctl	*ctl;
	pthread_mutex_t	*mtx;
	pthread_mutex_t	*tmtx;
	unsigned long	time_last_eat;
}	t_philo;

// philo.c
int				start_threads(t_ctl *ctl);
int				join_threads(t_ctl *ctl);
int				monitor_philos(t_ctl *ctl);
void			free_return(t_ctl *ctl);

// utils.c
unsigned long	ms_time(int *error);
int				print_alive_messages(int *msg, t_philo *p, unsigned long time);
int				print_message(int message, t_philo *philo);
void			philo_sleep(unsigned long milli_secs);
void			*routine(void *phil);

// inputs.c
int				ps_atoi(char *str, int *err);
bool			ps_isnumeric(char *str);
int				read_args(t_ctl *ctl, int argc, char **argv);
int				process_inputs(t_ctl *ctl, int argc, char **argv);

// initiate_vars.c
int				initiate_philos(t_ctl *ctl);
int				initiate_vars(t_ctl *ctl);
int				initiate_tmtx(t_ctl *ctl);
void			free_tmtx(t_ctl *ctl);

#endif
