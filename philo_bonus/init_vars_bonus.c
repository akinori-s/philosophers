/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 21:27:08 by asasada           #+#    #+#             */
/*   Updated: 2023/02/25 14:27:27 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_semaphore(t_ctl *ctl)
{
	if (unlink_sems() == ERROR)
		return (ERROR);
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

int	unlink_sems(void)
{
	if (sem_unlink("forks") == ERROR || \
		sem_unlink("printer") == ERROR || \
		sem_unlink("dead") == ERROR || \
		sem_unlink("finished") == ERROR || \
		sem_unlink("chairs") == ERROR)
		return (0);
	return (0);
}

static int	destroy_semaphore_2(t_ctl *ctl)
{
	if (ctl->sem_fork != NULL)
	{
		sem_post(ctl->sem_fork);
		sem_close(ctl->sem_fork);
	}
	if (ctl->sem_print != NULL)
	{
		sem_post(ctl->sem_print);
		sem_close(ctl->sem_print);
	}
	return (0);
}

int	destroy_semaphore(t_ctl *ctl)
{
	destroy_semaphore_2(ctl);
	if (ctl->sem_finished != NULL)
	{
		sem_post(ctl->sem_finished);
		sem_close(ctl->sem_finished);
	}
	if (ctl->sem_chair != NULL)
	{
		sem_post(ctl->sem_chair);
		sem_close(ctl->sem_chair);
	}
	if (ctl->sem_dead != NULL)
	{
		sem_post(ctl->sem_dead);
		sem_close(ctl->sem_dead);
	}
	unlink_sems();
	destroy_philo_sems(ctl);
	return (0);
}

int	init_vars(t_ctl *ctl)
{
	int	i;

	ctl->pid = malloc(sizeof(int) * ctl->pop);
	if (ctl->pid == NULL)
		return (ERROR);
	memset(ctl->pid, 0, sizeof(int) * ctl->pop);
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
