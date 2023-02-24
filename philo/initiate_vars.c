/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate_vars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 22:03:36 by asasada           #+#    #+#             */
/*   Updated: 2023/02/25 00:31:48 by asasada          ###   ########.fr       */
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
		ctl->philos[i].time_last_eat = 0;
		ctl->philos[i].ctl = ctl;
		ctl->philos[i].mtx = ctl->mtx;
		ctl->philos[i].tmtx = ctl->tmtx + i;
		ctl->philos[i].l_fork = ((i % 2) + i) % ctl->pop;
		ctl->philos[i].r_fork = (((i + 1) % 2) + i) % ctl->pop;
		i++;
	}
	return (0);
}

int	initiate_tmtx(t_ctl *ctl)
{
	int	i;

	ctl->tmtx = malloc(sizeof(pthread_mutex_t) * ctl->pop);
	if (ctl->tmtx == NULL)
		return (ERROR);
	memset(ctl->tmtx, 0, sizeof(pthread_mutex_t) * ctl->pop);
	i = 0;
	while (i < ctl->pop)
		if (pthread_mutex_init(&(ctl->tmtx[i++]), NULL) != 0)
			return (ERROR);
	return (0);
}

void	free_tmtx(t_ctl *ctl)
{
	ctl->mtx_destroy = 0;
	if (ctl->tmtx != NULL)
	{
		while (ctl->mtx_destroy < ctl->pop)
			pthread_mutex_destroy(&(ctl->tmtx[ctl->mtx_destroy++]));
		free(ctl->tmtx);
		ctl->tmtx = NULL;
	}
}

int	initiate_vars(t_ctl *ctl)
{
	int	i;

	ctl->time_start = ms_time(NULL);
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
	if (initiate_tmtx(ctl) == ERROR)
		return (ERROR);
	if (initiate_philos(ctl) == ERROR)
		return (ERROR);
	return (0);
}
