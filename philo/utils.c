/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 21:58:43 by asasada           #+#    #+#             */
/*   Updated: 2023/02/23 00:34:37 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	ms_time(int *error)
{
	unsigned long	sec;
	unsigned long	micro_sec;
	unsigned long	ret;
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		if (error == NULL)
			return (0);
		*error = ERROR;
		return (0);
	}
	sec = time.tv_sec;
	micro_sec = time.tv_usec;
	ret = sec * 1000;
	ret += micro_sec / 1000;
	return (ret);
}

int	print_alive_messages(int message, t_philo *philo, unsigned long time_ms)
{
	if (message == FORK)
		printf("%lu\t %d has taken a fork\n", time_ms, philo->idx + 1);
	if (message == EAT)
		printf("%lu\t %d is eating\n", time_ms, philo->idx + 1);
	if (message == SLEEP)
		printf("%lu\t %d is sleeping\n", time_ms, philo->idx + 1);
	if (message == THINK)
		printf("%lu\t %d is thinking\n", time_ms, philo->idx + 1);
	return (0);
}

int	print_message(int message, t_philo *philo)
{
	int				ret;
	unsigned long	time_ms;

	ret = 0;
	pthread_mutex_lock(philo->ctl->pmtx);
	time_ms = ms_time(&ret) - philo->ctl->time_start;
	if (ret == ERROR || philo->ctl->philo_dead == 1)
		ret = ERROR;
	else if (philo->ctl->philo_dead == 0)
	{
		print_alive_messages(message, philo, time_ms);
		if (message == DIED)
		{
			printf("%lu\t %d died\n", time_ms, philo->idx + 1);
			philo->ctl->philo_dead = 1;
		}
	}
	pthread_mutex_unlock(philo->ctl->pmtx);
	return (ret);
}

void	philo_sleep(unsigned long milli_secs)
{
	unsigned long	start_time;
	int				err;

	err = 0;
	start_time = ms_time(&err);
	while (ms_time(&err) - start_time < milli_secs)
		usleep(500);
}

void	*routine(void *phil)
{
	t_philo	*p;

	p = (t_philo *)phil;
	while (1)
	{
		pthread_mutex_lock(&(p->mtx[p->l_fork]));
		print_message(FORK, p);
		if (p->ctl->pop == 1)
			return ((void *)(long)pthread_mutex_unlock(&(p->mtx[p->idx])));
		pthread_mutex_lock(&(p->mtx[p->r_fork]));
		print_message(FORK, p);
		print_message(EAT, p);
		philo_sleep(p->ctl->time_to_eat);
		if (++p->times_eaten == p->ctl->opt_count && p->ctl->has_opt)
			p->ctl->num_finished_eating++;
		pthread_mutex_unlock(&(p->mtx[(p->idx + 1) % p->ctl->pop]));
		pthread_mutex_unlock(&(p->mtx[p->idx]));
		p->time_last_eat = ms_time(NULL);
		print_message(SLEEP, p);
		philo_sleep(p->ctl->time_to_sleep);
		print_message(THINK, p);
		if (p->ctl->philo_dead == 1)
			break ;
	}
	return (0);
}
