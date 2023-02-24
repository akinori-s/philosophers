/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 01:38:50 by asasada           #+#    #+#             */
/*   Updated: 2023/02/25 02:06:04 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdint.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

static char	*ft_strdup(const char *src)
{
	char	*str;
	size_t	i;

	str = malloc((ft_strlen(src) + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;

	i = 0;
	if (dst)
	{
		while (dst[i] != '\0' && i < dstsize)
			i++;
	}
	dst_len = i;
	dst += i;
	i = 0;
	if (dst_len < dstsize && dst)
	{
		while (i < dstsize - dst_len - 1 && src[i] != '\0' && dstsize != 0)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (dst_len + ft_strlen(src));
}

static size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (i < dstsize - 1 && src[i] != '\0' && dstsize != 0)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize != 0)
		dst[i] = '\0';
	i = 0;
	while (src[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (SIZE_MAX - s1_len < s2_len + 1)
		return (NULL);
	joined = malloc(s1_len + s2_len + 1);
	if (!joined)
		return (NULL);
	ft_strlcpy(joined, s1, s1_len + 1);
	ft_strlcat(joined, s2, s1_len + s2_len + 1);
	return (joined);
}
