/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:21:46 by anarama           #+#    #+#             */
/*   Updated: 2024/09/18 22:30:22 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../libft/libft.h"

void	*ft_calloc_gnl(size_t num, size_t size)
{
	char	*mem;
	char	*temp_mem;
	size_t	total_size;

	total_size = size * num;
	if (num == 0 || size == 0)
		total_size = 0;
	if (SIZE_MAX / num < size)
		return (NULL);
	mem = (char *)malloc(total_size);
	if (!mem)
		return (NULL);
	temp_mem = mem;
	while (total_size > 0)
	{
		*mem++ = 0;
		total_size--;
	}
	return ((void *)temp_mem);
}

char	*ft_strchr_gnl(char *str, char c)
{
	if (str == NULL)
		return (NULL);
	while (*str)
	{
		if (*str == c)
			return (str);
		str++;
	}
	if (c == '\0')
		return (str);
	return (NULL);
}

char	*ft_strjoin_gnl(char *s1, char *s2, int *flag)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*cat_result;
	char	*temp_cat_result;

	if (s1 == NULL)
	{
		cat_result = ft_strdup_gnl(s2, flag);
		return (ft_free_gnl(&s2), cat_result);
	}
	len_s1 = ft_strlen_gnl(s1);
	len_s2 = ft_strlen_gnl(s2);
	cat_result = (char *)ft_calloc_gnl((len_s1 + len_s2) + 1, 1);
	if (!cat_result)
		return (ft_free_gnl(&s1), ft_free_gnl(&s2), *flag = 1, NULL);
	temp_cat_result = cat_result;
	ft_memcpy_gnl(cat_result, s1, len_s1);
	cat_result += len_s1;
	ft_memcpy_gnl(cat_result, s2, len_s2);
	return (ft_free_gnl(&s1), ft_free_gnl(&s2), temp_cat_result);
}

char	*ft_strdup_gnl(const char *s, int *flag)
{
	size_t	len_s;
	char	*dup_s;
	char	*temp_dup_s;

	if (s == NULL)
		return (*flag = 1, NULL);
	len_s = ft_strlen_gnl(s);
	dup_s = (char *)malloc(sizeof(char) * (len_s + 1));
	if (!dup_s)
		return (*flag = 1, NULL);
	temp_dup_s = dup_s;
	while (*s)
		*dup_s++ = *s++;
	*dup_s = '\0';
	return (temp_dup_s);
}

void	*ft_memcpy_gnl(void *dest, const void *src, size_t n)
{
	if (dest == NULL || src == NULL)
		return (NULL);
	return (ft_memmove(dest, src, n));
}
