/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:14:20 by anarama           #+#    #+#             */
/*   Updated: 2024/09/18 22:36:40 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# ifndef MAX_FD
#  define MAX_FD 1024
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <fcntl.h>
# include <stddef.h>

void	*ft_calloc_gnl(size_t num, size_t size);
void	*ft_memcpy_gnl(void *dest, const void *src, size_t n);
size_t	ft_strlen_gnl(const char *str);
char	*ft_strchr_gnl(char *str, char c);
char	*ft_strjoin_gnl(char *s1, char *s2, int *flag);
char	*ft_strdup_gnl(const char *s, int *flag);
void	ft_free_gnl(char **str);
char	*get_next_line(int fd, int *flag);

#endif