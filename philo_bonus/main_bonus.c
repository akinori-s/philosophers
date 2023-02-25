/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 23:12:53 by asasada           #+#    #+#             */
/*   Updated: 2023/02/25 14:37:24 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	free_all(t_ctl *ctl, int status)
{
	if (ctl->pid != NULL)
		free(ctl->pid);
	destroy_semaphore(ctl);
	return (status);
}

void	kill_processes(t_ctl *ctl)
{
	int	i;

	i = 0;
	while (i < ctl->pop)
		if (ctl->pid[i] != 0)
			kill(ctl->pid[i++], SIGTERM);
}

void	*check_dead(void *p)
{
	t_ctl	*ctl;
	int		i;

	ctl = (t_ctl *)p;
	sem_wait(ctl->sem_dead);
	i = 0;
	while (i++ < ctl->pop)
		sem_post(ctl->sem_finished);
	kill_processes(ctl);
	return (NULL);
}

void	*check_finished(void *p)
{
	t_ctl	*ctl;
	int		i;

	ctl = (t_ctl *)p;
	i = 0;
	while (i++ < ctl->pop)
		sem_wait(ctl->sem_finished);
	sem_post(ctl->sem_dead);
	kill_processes(ctl);
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_ctl	ctl;
	int		i;

	ctl = (t_ctl){0};
	if (process_inputs(&ctl, argc, argv) == ERROR)
		return (ERROR);
	if (ctl.has_opt == TRUE && ctl.opt_count == 0)
		return (0);
	if (init_vars(&ctl) == ERROR)
		return (ERROR);
	if (start_process(&ctl) == ERROR)
		return (free_all(&ctl, ERROR));
	if (pthread_create(&(ctl.thread_dead), NULL, check_dead, &ctl) == ERROR)
		return (free_all(&ctl, ERROR));
	pthread_detach(ctl.thread_dead);
	if (pthread_create(&(ctl.thread_fin), NULL, check_finished, &ctl) == ERROR)
		return (free_all(&ctl, ERROR));
	pthread_detach(ctl.thread_fin);
	i = 0;
	while (i < ctl.pop)
		waitpid(ctl.pid[i++], NULL, 0);
	free_all(&ctl, 0);
	return (0);
}

/*
How to use semaphore

1. sem unlink
2. sem_open(O_CREATE)
3. sem_wait()
4. sem_post()
5. sem_close()
6. sem_unlink()
*/