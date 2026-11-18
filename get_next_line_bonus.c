/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnoukan <alnoukan@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 20:58:33 by alnoukan          #+#    #+#             */
/*   Updated: 2026/11/18 20:59:22 by alnoukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	ft_clean(char *buffer)
{
	int	i;
	int	j;

	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\n')
		i++;
	j = 0;
	while (buffer[i])
		buffer[j++] = buffer[i++];
	buffer[j] = '\0';
}

static char	*ft_extract(char *stash)
{
	char	*line;
	int		len;

	len = 0;
	while (stash[len] != '\n' && stash[len] != '\0')
		len++;
	if (stash[len] == '\n')
		len++;
	line = malloc((len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	ft_strncpy(line, stash, len);
	line[len] = '\0';
	return (line);
}

static char	*get_next_line_2(char *stash, char *buffer, int fd)
{
	int	bytes_read;

	bytes_read = 1;
	while (!ft_verify(stash) && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (buffer[0] = '\0', free(stash), NULL);
		buffer[bytes_read] = '\0';
		stash = ft_strjoin(stash, buffer);
		if (!stash)
			return (buffer[0] = '\0', NULL);
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	buffer[1024][BUFFER_SIZE + 1];
	char		*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = malloc(sizeof(char));
	if (!stash)
		return (NULL);
	stash[0] = '\0';
	stash = ft_strjoin(stash, buffer);
	if (!stash)
		return (NULL);
	stash = get_next_line_2(stash, buffer, fd);
	if (!stash)
		return (NULL);
	if (stash[0] == '\0')
		return (free(stash), NULL);
	line = ft_extract(stash);
	free(stash);
	ft_clean(buffer);
	return (line);
}
