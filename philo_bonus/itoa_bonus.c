/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 01:37:58 by asasada           #+#    #+#             */
/*   Updated: 2023/02/25 01:44:50 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	rev_str(char *str)
{
	char	tmp;
	int		i;
	int		len;

	len = ft_strlen(str);
	i = 0;
	while (i < len / 2)
	{
		tmp = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = tmp;
		i++;
	}
}

static int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}

static int	num_len(int n)
{
	int	len;

	len = 1;
	if (n < 0)
		len++;
	while (n / 10 != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;

	str = (char *)malloc(num_len(n) + 1);
	if (!str)
		return (NULL);
	if (n == 0)
		str[0] = '0';
	if (n < 0)
		str[num_len(n) - 1] = '-';
	i = 0;
	while (n != 0)
	{
		str[i] = '0' + ft_abs(n % 10);
		i++;
		n /= 10;
	}
	rev_str(str);
	return (str);
}
