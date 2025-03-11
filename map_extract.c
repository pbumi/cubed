/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_extract.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:08:22 by pbumidan          #+#    #+#             */
/*   Updated: 2025/02/15 19:42:43 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static char	*extract_loop(char *map_content, int fd)
{
	char	*line;
	char	*tmp;

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line[0] != '\0')
		{
			tmp = ft_strjoin(map_content, line);
			free(map_content);
			if (!tmp)
			{
				free(line);
				map_content = NULL;
				return (NULL);
			}
			map_content = tmp;
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (map_content);
}

bool	extract_map(int fd, t_data *game)
{
	char	*map_content;

	map_content = ft_strdup("");
	if (!map_content)
		return (false);
	map_content = extract_loop(map_content, fd);
	if (!map_content)
		return (false);
	game->map = ft_strtrim(map_content, "\n");
	if (!game->map)
	{
		free(map_content);
		return (false);
	}
	else
	{
		free(map_content);
		map_content = NULL;
	}
	return (true);
}
