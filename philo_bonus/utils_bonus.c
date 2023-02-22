/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 19:49:10 by asasada           #+#    #+#             */
/*   Updated: 2023/02/18 17:37:01 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

unsigned long	ms_time(void)
{
	unsigned long	sec;
	unsigned long	micro_sec;
	unsigned long	ret;
	struct timeval	time;

	if (gettimeofday(&time, NULL) == ERROR)
		return (0);
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
	unsigned long	time_ms;

	sem_wait(philo->ctl->sem_print);
	time_ms = ms_time() - philo->ctl->time_start;
	if (philo->ctl->philo_dead == 0)
	{
		print_alive_messages(message, philo, time_ms);
		if (message == DIED)
		{
			printf("%lu\t %d died\n", time_ms, philo->idx + 1);
			philo->ctl->philo_dead = 1;
		}
	}
	if (philo->ctl->philo_dead != 1)
		sem_post(philo->ctl->sem_print);
	return (0);
}

void	philo_sleep(unsigned long milli_secs)
{
	unsigned long	start_time;

	start_time = ms_time();
	while (ms_time() - start_time < milli_secs)
		usleep(500);
}
