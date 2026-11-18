/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnoukan <alnoukan@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:20:10 by anoukan           #+#    #+#             */
/*   Updated: 2026/11/18 20:41:44 by alnoukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_clean(char *stash)
{
	int		i;
	char	*tmp;

	tmp = malloc(ft_strlen(stash) + 1);
	if (!tmp)
		return ;
	i = 0;
	while (stash[i] != '\n' && stash[i] != '\0')
		i++;
	if (stash[i] == '\n')
		i++;
	ft_strncpy(tmp, stash + i, ft_strlen(stash + i));
	tmp[ft_strlen(stash + i)] = '\0';
	ft_strncpy(stash, tmp, ft_strlen(tmp));
	free(tmp);
}

static char	*get_next_line_2(char **stash, char *buffer, int *bytes_read, int fd)
{
	char	*result;
	size_t	len;

	while (!ft_verify(*stash))
	{
		*bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (*bytes_read <= 0)
			break ;
		buffer[*bytes_read] = '\0';
		*stash = ft_strjoin(*stash, buffer);
	}
	len = 0;
	while ((*stash)[len] != '\n' && (*stash)[len] != '\0')
		len++;
	if ((*stash)[len] != '\0')
		len++;
	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (free(*stash), NULL);
	if ((*stash)[0] == '\n' && len == 0)
		result[len++] = '\n';
	ft_strncpy(result, *stash, len);
	result[len] = '\0';
	ft_clean(buffer);
	return (result);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*stash;
	int			bytes_read;

	if (fd < 0)
		return (free(stash), stash = NULL, NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
		return (free(stash), stash = NULL, NULL);
	buffer[bytes_read] = '\0';
	if (!stash)
	{
		stash = malloc(sizeof(char));
		if (!stash)
			return (NULL);
		*stash = '\0';
	}
	stash = ft_strjoin(stash, buffer);
	if (stash[0] == '\0')
		return (free(stash), stash = NULL, NULL);
	return (get_next_line_2(&stash, &buffer, &bytes_read, fd));
}

int	main(void)
{
	char	*test;
	int		fd;
	int		i;

	fd = open("./test.txt", O_RDONLY);
	test = get_next_line(fd);
	i = 0;
	printf("%s\n", test[i]);
	close(fd);
	return (0);
}
