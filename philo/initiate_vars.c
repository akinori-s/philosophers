/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate_vars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 22:03:36 by asasada           #+#    #+#             */
/*   Updated: 2023/02/23 00:39:10 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	initiate_philos(t_ctl *ctl)
{
	int	i;

	ctl->philos = malloc(sizeof(t_philo) * ctl->pop);
	if (ctl->mtx == NULL)
		return (ERROR);
	i = 0;
	while (i < ctl->pop)
	{
		ctl->philos[i].idx = i;
		ctl->philos[i].times_eaten = 0;
		ctl->philos[i].time_last_eat = ctl->time_start;
		ctl->philos[i].ctl = ctl;
		ctl->philos[i].mtx = ctl->mtx;
		// if (ctl->philos[i].idx % 2 == 0)
		// {
		// 	ctl->philos[i].l_fork = ;
		// 	ctl->philos[i].r_fork = ;
		// }
		// else
		// {
		// 	ctl->philos[i].l_fork = ;
		// 	ctl->philos[i].r_fork = ;
		// }
		ctl->philos[i].l_fork = ((i % 2) + i) % ctl->pop;
		ctl->philos[i].r_fork = (((i + 1) % 2) + i) % ctl->pop;
		// printf("philo%d: %d, %d\n", i, ctl->philos[i].l_fork, ctl->philos[i].r_fork);
		i++;
	}
	// exit(0);
	return (0);
}

int	initiate_vars(t_ctl *ctl)
{
	int	i;
	int	error;

	error = 0;
	ctl->time_start = ms_time(&error);
	if (error == ERROR)
		return (ERROR);
	ctl->mtx = malloc(sizeof(pthread_mutex_t) * ctl->pop);
	if (ctl->mtx == NULL)
		return (ERROR);
	memset(ctl->mtx, 0, sizeof(pthread_mutex_t) * ctl->pop);
	ctl->pmtx = malloc(sizeof(pthread_mutex_t));
	if (ctl->pmtx == NULL)
		return (ERROR);
	memset(ctl->pmtx, 0, sizeof(pthread_mutex_t));
	i = 0;
	while (i < ctl->pop)
		if (pthread_mutex_init(&(ctl->mtx[i++]), NULL) != 0)
			return (ERROR);
	if (pthread_mutex_init(ctl->pmtx, NULL) != 0)
		return (ERROR);
	if (initiate_philos(ctl) == ERROR)
		return (ERROR);
	return (0);
}
