/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_extract.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:08:22 by pbumidan          #+#    #+#             */
/*   Updated: 2024/12/07 17:36:05 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cubed.h"

void fill_map_dimensions(t_main *game)
{
    t_pt pt;
    pt.y = 0;
    while (game->map_arr[(int)pt.y] != NULL) // Iterate until NULL (end of array)
    {
        pt.y++;
    }
    game->h_map = pt.y;
    game->w_map = malloc(sizeof(int) * game->h_map);
    if (game->w_map == NULL) 
    {
        return;
    }
    pt.x = 0;
    while (pt.x < game->h_map)
    {
        game->w_map[(int)pt.x] = ft_strlen(game->map_arr[(int)pt.x]);  // Store the width of each row
        pt.x++;
    }
}

void fill_player_position(t_main *game)
{
    t_pt pt;

    pt.x = 0;
    pt.y = 0;
    while (game->map_arr[(int)pt.y] != NULL)
    {
        while (game->map_arr[(int)pt.y][(int)pt.x] != '\0')
        {
            if (ft_strchr("NSWE", game->map_arr[(int)pt.y][(int)pt.x]))
            {
                game->p_x = pt.x;  // Set the x-coordinate of the player
                game->p_y = pt.y;  // Set the y-coordinate of the player
                return;  // Player position found, exit the function
            }
            pt.x++;  // Move to the next character in the current row
        }
        pt.y++;
        pt.x = 0;
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
        fill_player_position(game);
	}
    return true;
}

