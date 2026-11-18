/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnoukan <alnoukan@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 20:29:48 by alnoukan          #+#    #+#             */
/*   Updated: 2026/11/18 20:39:26 by alnoukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
//# include <stdarg.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

// Buffer
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

// base function
char	*get_next_line(int fd);

// utils function
int		ft_strlen(char const *s);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
char	*ft_strjoin(char *s1, char *s2);
int		ft_verify(char *stash);

#endif
