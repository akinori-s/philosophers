/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:22:22 by asasada           #+#    #+#             */
/*   Updated: 2023/02/25 13:31:33 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	philo_routine(t_philo *philo)
{
	while (1)
	{
		sem_wait(philo->ctl->sem_chair);
		sem_wait(philo->ctl->sem_fork);
		print_message(FORK, philo);
		sem_wait(philo->ctl->sem_fork);
		print_message(FORK, philo);
		print_message(EAT, philo);
		philo_sleep(philo->ctl->time_to_eat);
		philo->times_eaten++;
		sem_post(philo->ctl->sem_fork);
		sem_post(philo->ctl->sem_fork);
		sem_post(philo->ctl->sem_chair);
		print_message(SLEEP, philo);
		philo_sleep(philo->ctl->time_to_sleep);
		print_message(THINK, philo);
	}
	return (0);
}

void	*monitor_philo(void *p)
{
	t_philo			*philo;
	unsigned long	a;
	unsigned long	b;

	philo = (t_philo *)p;
	while (1)
	{
		if (philo->times_eaten >= philo->ctl->opt_count && philo->ctl->has_opt)
		{
			sem_post(philo->ctl->sem_finished);
			break ;
		}
		sem_wait(philo->ctl->sem_philos[philo->idx]);
		b = philo->time_last_eat;
		sem_post(philo->ctl->sem_philos[philo->idx]);
		a = ms_time() - philo->ctl->time_start;
		if (a - b > (unsigned long)philo->ctl->time_to_die)
		{
			print_message(DIED, philo);
			sem_post(philo->ctl->sem_dead);
			break ;
		}
	}
	return (NULL);
}

int	philo_process(t_ctl *ctl, int i)
{
	t_philo	philo;

	philo.ctl = ctl;
	philo.idx = i;
	philo.time_last_eat = ms_time() - ctl->time_start;
	philo.times_eaten = 0;
	if (pthread_create(&(philo.thread), NULL, monitor_philo, &philo) == ERROR)
		return (ERROR);
	philo_routine(&philo);
	pthread_join((philo.thread), NULL);
	return (0);
}

int	start_process(t_ctl *ctl)
{
	int	i;

	i = 0;
	while (i < ctl->pop)
	{
		ctl->pid[i] = fork();
		if (ctl->pid[i] == 0)
		{
			philo_process(ctl, i);
			return (0);
		}
		if (ctl->pid[i] == ERROR)
		{
			kill_processes(ctl);
			return (ERROR);
		}
		i++;
		usleep(50);
	}
	return (0);
}
