/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 22:01:44 by asasada           #+#    #+#             */
/*   Updated: 2023/02/18 14:49:28 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ps_atoi(char *str, int *err)
{
	int		m_count;
	long	n;

	n = 0;
	m_count = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			m_count = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		n = (n * 10) + (*str - '0');
		if ((n > (long)INT_MAX && m_count == 1) || n * m_count < (long)INT_MIN)
		{
			*err += 1;
			return (0);
		}
		str++;
	}
	return ((int)(n * m_count));
}

bool	ps_isnumeric(char *str)
{
	size_t	numeric_count;

	numeric_count = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
		str++;
	while (*str != '\0')
	{
		if (*str >= '0' && *str <= '9')
		{
			numeric_count++;
			str++;
		}
		else
			return (1);
	}
	if (numeric_count == 0)
		return (false);
	return (true);
}

int	read_args(t_ctl *ctl, int argc, char **argv)
{
	int	i;
	int	err;

	err = 0;
	i = 1;
	while (i < argc)
		if (ps_isnumeric(argv[i++]) == false)
			return (ERROR);
	ctl->pop = ps_atoi(argv[1], &err);
	ctl->time_to_die = ps_atoi(argv[2], &err);
	ctl->time_to_eat = ps_atoi(argv[3], &err);
	ctl->time_to_sleep = ps_atoi(argv[4], &err);
	if (argc == 6)
	{
		ctl->opt_count = ps_atoi(argv[5], &err);
		ctl->has_opt = 1;
	}
	if (err > 0)
		return (ERROR);
	return (0);
}

int	process_inputs(t_ctl *ctl, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (ERROR);
	if (read_args(ctl, argc, argv) == ERROR)
		return (ERROR);
	if (ctl->pop < 0 || ctl->time_to_die < 0 || ctl->time_to_eat < 0 || \
		ctl->time_to_sleep < 0 || ctl->opt_count < 0)
		return (ERROR);
	return (0);
}
