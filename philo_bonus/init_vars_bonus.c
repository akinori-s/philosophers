/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 21:27:08 by asasada           #+#    #+#             */
/*   Updated: 2023/02/25 02:53:08 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_semaphore(t_ctl *ctl)
{
	sem_unlink("chairs");
	sem_unlink("forks");
	sem_unlink("printer");
	sem_unlink("dead");
	sem_unlink("finished");
	ctl->sem_chair = sem_open("chairs", O_CREAT, 0700, ctl->num_chairs);
	ctl->sem_fork = sem_open("forks", O_CREAT, 0700, ctl->pop);
	ctl->sem_print = sem_open("printer", O_CREAT, 0700, 1);
	ctl->sem_dead = sem_open("dead", O_CREAT, 0700, 1);
	ctl->sem_finished = sem_open("finished", O_CREAT, 0700, ctl->pop);
	if (ctl->sem_fork == NULL || \
		ctl->sem_print == NULL || \
		ctl->sem_dead == NULL || \
		ctl->sem_chair == NULL || \
		ctl->sem_finished == NULL || \
		init_philo_sems(ctl) == ERROR)
		return (ERROR);
	return (0);
}

int	destroy_semaphore(t_ctl *ctl)
{
	sem_post(ctl->sem_fork);
	sem_close(ctl->sem_fork);
	sem_post(ctl->sem_print);
	sem_close(ctl->sem_print);
	sem_post(ctl->sem_finished);
	sem_close(ctl->sem_finished);
	sem_post(ctl->sem_chair);
	sem_close(ctl->sem_chair);
	sem_post(ctl->sem_dead);
	sem_close(ctl->sem_dead);
	sem_unlink("forks");
	sem_unlink("printer");
	sem_unlink("dead");
	sem_unlink("finished");
	sem_unlink("chairs");
	destroy_philo_sems(ctl);
	return (0);
}

int	init_vars(t_ctl *ctl)
{
	int	i;

	ctl->pid = malloc(sizeof(int) * ctl->pop);
	if (ctl->pid == NULL)
		return (ERROR);
	ctl->num_chairs = ctl->pop / 2;
	if (ctl->pop == 1)
		ctl->num_chairs = 1;
	if (init_semaphore(ctl) == ERROR)
	{
		free(ctl->pid);
		ctl->pid = NULL;
		destroy_semaphore(ctl);
		return (ERROR);
	}
	ctl->time_start = ms_time();
	i = 0;
	while (i++ < ctl->pop)
		sem_wait(ctl->sem_finished);
	sem_wait(ctl->sem_dead);
	return (0);
}
