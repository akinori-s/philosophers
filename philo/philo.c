/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:24:52 by asasada           #+#    #+#             */
/*   Updated: 2023/01/05 15:24:52 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_threads(t_ctl *ctl)
{
	int	i;

	i = 0;
	ctl->th = malloc(sizeof(pthread_t) * ctl->pop);
	if (ctl->th == NULL)
		return (ERROR);
	memset(ctl->th, 0, sizeof(pthread_t) * ctl->pop);
	while (i < ctl->pop)
	{
		if (pthread_create(&(ctl->th[i]), NULL, routine, &(ctl->philos[i]))
			!= 0)
			return (ERROR);
		usleep(THREAD_CREATION_BUFFER);
		i += 2;
	}
	i = 1;
	while (i < ctl->pop)
	{
		if (pthread_create(&(ctl->th[i]), NULL, routine, &(ctl->philos[i]))
			!= 0)
			return (ERROR);
		usleep(THREAD_CREATION_BUFFER);
		i += 2;
	}
	return (0);
}

int	join_threads(t_ctl *ctl)
{
	int	i;

	i = 0;
	while (i < ctl->pop)
	{
		if (ctl->th[i] != 0)
			pthread_join(ctl->th[i], NULL);
		i++;
	}
	return (0);
}

int	monitor_philos(t_ctl *ctl)
{
	int				i;
	unsigned long	time_ms;
	unsigned long	last_eat;

	i = 0;
	while (1)
	{
		if (ctl->num_finished_eating >= ctl->pop)
		{
			pthread_mutex_lock(ctl->pmtx);
			ctl->philo_dead = 1;
			pthread_mutex_unlock(ctl->pmtx);
			break ;
		}
		pthread_mutex_lock(&(ctl->tmtx[i]));
		last_eat = ctl->philos[i].time_last_eat;
		pthread_mutex_unlock(&(ctl->tmtx[i]));
		time_ms = ms_time(NULL) - ctl->time_start;
		if (time_ms - last_eat > (unsigned long)ctl->time_to_die && \
			(last_eat < time_ms))
			return (print_message(DIED, &(ctl->philos[i])));
		i = (i + 1) % ctl->pop;
	}
	return (0);
}

void	free_return(t_ctl *ctl)
{
	ctl->mtx_destroy = 0;
	if (ctl->philos != NULL)
	{
		free(ctl->philos);
		ctl->philos = NULL;
	}
	if (ctl->th != NULL)
	{
		free(ctl->th);
		ctl->th = NULL;
	}
	if (ctl->mtx != NULL)
	{
		while (ctl->mtx_destroy < ctl->pop)
			pthread_mutex_destroy(&(ctl->mtx[ctl->mtx_destroy++]));
		free(ctl->mtx);
		ctl->mtx = NULL;
	}
	free_tmtx(ctl);
	if (ctl->pmtx != NULL)
	{
		pthread_mutex_destroy(ctl->pmtx);
		free(ctl->pmtx);
		ctl->pmtx = NULL;
	}
}

int	main(int argc, char **argv)
{
	t_ctl	ctl;

	ctl = (t_ctl){0};
	if (process_inputs(&ctl, argc, argv) == ERROR)
		return (ERROR);
	if (initiate_vars(&ctl) == ERROR)
	{
		free_return(&ctl);
		return (ERROR);
	}
	if (start_threads(&ctl) == ERROR)
	{
		pthread_mutex_lock(ctl.pmtx);
		ctl.philo_dead = 1;
		pthread_mutex_unlock(ctl.pmtx);
		join_threads(&ctl);
		free_return(&ctl);
		return (ERROR);
	}
	monitor_philos(&ctl);
	join_threads(&ctl);
	free_return(&ctl);
	return (0);
}
