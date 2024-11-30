/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_extract.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:08:22 by pbumidan          #+#    #+#             */
/*   Updated: 2024/11/30 18:05:38 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cubed.h"

void    fill_map_dimensions(t_main *game)
{
    size_t x;
    size_t y;
    
    x = 0;
    y = 0;
    game->w_map = ft_strlen(game->map_arr[y]);
    while (game->map_arr[y])
    {
        while (game->map_arr[y][x])
        {
            if (ft_strchr("NSWE", game->map_arr[y][x]))
            {
                game->p_x = x;
                game->p_y = y;
            }
            x++;
        }
        y++;
        game->h_map = y;
        x = 0;
    }
}

void	change_space_to1(char *str)
{
	size_t x;

	x = 0;
	while(str[x])
	{
		if (str[x] == ' ')
		{
			str[x] = '0';
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
    game->map = ft_strtrim(map_content,"\n");
	free(map_content);
	map_content = NULL;
	//change_space_to1(game->map);
	if (!validate_map(game))
		return false;
	else
	{
		game->map_arr = ft_split(game->map, '\n');
		if (!game->map_arr)
		{
			return false;
		}
        fill_map_dimensions(game);
	}
    return true;
}
