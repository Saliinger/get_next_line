/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnoukan <alnoukan@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 20:29:01 by alnoukan          #+#    #+#             */
/*   Updated: 2026/11/18 20:29:03 by alnoukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char const *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		++i;
	}
	while (i < n)
	{
		dest[i] = '\0';
		++i;
	}
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*d;
	size_t	f;
	size_t	g;

	f = 0;
	g = 0;
	d = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!d)
		return (free(s1), NULL);
	while (s1[f])
	{
		d[f] = s1[f];
		++f;
	}
	while (s2[g])
	{
		d[f] = s2[g];
		++f;
		++g;
	}
	d[f] = '\0';
	free(s1);
	return (d);
}

int	ft_verify(char *stash)
{
	int	i;

	i = 0;
	while (stash[i])
	{
		if (stash[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
