/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnoukan <alnoukan@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 20:29:24 by alnoukan          #+#    #+#             */
/*   Updated: 2026/11/18 20:29:26 by alnoukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

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
char	*ft_clean(char *stash);

#endif
