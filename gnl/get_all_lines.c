/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_all_lines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:05:50 by pbumidan          #+#    #+#             */
/*   Updated: 2024/10/20 16:42:09 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_all_lines(int fd)
{
	static char	*source;
	int			bytes_read;

	if (!source)
	{
		source = (char *)malloc(sizeof(char));
		if (!source)
			return (NULL);
		source[0] = '\0';
	}
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &source, 0) < 0)
	{
		return (ft_free(&source));
	}
	bytes_read = ft_read_source(fd, &source);
	while (bytes_read > 0)
	{
		bytes_read = ft_read_source(fd, &source);
	}
	if (bytes_read < 0 || *source == '\0')
	{
		return (ft_free(&source));
	}
	return (source);
}

char	*get_end_line(int fd, char	*source)
{
	int			bytes_read;

	if (!source)
	{
		source = (char *)malloc(sizeof(char));
		if (!source)
			return (NULL);
		source[0] = '\0';
	}
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &source, 0) < 0)
	{
		return (ft_free(&source));
	}
	bytes_read = ft_read_source(fd, &source);
	while (bytes_read > 0)
	{
		bytes_read = ft_read_source(fd, &source);
	}
	if (bytes_read < 0 || *source == '\0')
	{
		return (ft_free(&source));
	}
	return (source);
}