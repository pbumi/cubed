/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_extract.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:08:22 by pbumidan          #+#    #+#             */
/*   Updated: 2024/10/31 17:13:17 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cubed.h"

void	change_space_to1(char *str)
{
	size_t x;

	x = 0;
	while(str[x])
	{
		if (str[x] == ' ')
		{
			str[x] = '1';
		}
		x++; 
	}
}

char *extract_loop(char *map_content, int fd)
{
    char *line;
    char *tmp;

    while ((line = get_next_line(fd)) != NULL)
    {
        if (line[0] != '\0')
        {
            tmp = map_content;
            map_content = gnl_strjoin(tmp, line);
            free(tmp);
            if (!map_content)
            {
                free(line);
                return NULL;
            }
        }
        free(line);
    }
    return map_content;
}

bool extract_map1(int fd, t_main *game)
{
    char *map_content;
	map_content = ft_strdup("");
    if (!map_content)
        return false;
    map_content = extract_loop(map_content, fd);
    if (!map_content)
        return false;
    game->map = remove_wspace(map_content, 0);
	free(map_content);
	map_content = NULL;
	change_space_to1(game->map);
	if (!validate_map(game))
		return false;
	else
	{
		game->map_arr = ft_split(game->map, '\n');
		if (!game->map_arr)
		{
			return false;
		}
	}
    return true;
}