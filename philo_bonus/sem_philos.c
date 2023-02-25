/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_philos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 02:52:57 by asasada           #+#    #+#             */
/*   Updated: 2023/02/25 13:19:31 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	free_names(t_ctl *ctl, int i)
{
	while (i >= 0)
	{
		if (ctl->sem_names[i] != NULL)
		{
			free(ctl->sem_names[i]);
			ctl->sem_names[i] = NULL;
		}
		i--;
	}
	free(ctl->sem_names);
	return (ERROR);
}

static int	malloc_sem_philos(t_ctl *ctl)
{
	ctl->sem_philos = malloc(sizeof(sem_t *) * ctl->pop);
	if (ctl->sem_philos == NULL)
		return (ERROR);
	ctl->sem_names = malloc(sizeof(char *) * ctl->pop);
	if (ctl->sem_names == NULL)
		return (ERROR);
	memset(ctl->sem_names, 0, sizeof(char *) * ctl->pop);
	return (0);
}

int	init_philo_sems(t_ctl *ctl)
{
	int		i;
	char	*num;

	if (malloc_sem_philos(ctl) == ERROR)
		return (ERROR);
	i = 0;
	while (i < ctl->pop)
	{
		num = ft_itoa(i);
		if (num == NULL)
			return (ERROR);
		ctl->sem_names[i] = ft_strjoin("philo", num);
		free(num);
		if (ctl->sem_names[i] == NULL)
			return (ERROR);
		sem_unlink(ctl->sem_names[i]);
		ctl->sem_philos[i] = sem_open(ctl->sem_names[i], O_CREAT, 0700, 1);
		if (ctl->sem_philos[i] == NULL)
			return (ERROR);
		ctl->sem_name_count = ++i;
	}
	return (0);
}

int	destroy_philo_sems(t_ctl *ctl)
{
	int	i;

	i = 0;
	while (i < ctl->pop)
	{
		if (ctl->sem_philos[i] != NULL)
		{
			sem_post(ctl->sem_philos[i]);
			sem_close(ctl->sem_philos[i]);
		}
		sem_unlink(ctl->sem_names[i]);
		i++;
	}
	free(ctl->sem_philos);
	if (ctl->sem_names != NULL)
		free_names(ctl, ctl->sem_name_count - 1);
	return (0);
}
