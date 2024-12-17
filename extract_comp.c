/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_comp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:02:54 by pbumidan          #+#    #+#             */
/*   Updated: 2024/12/17 18:25:30 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cubed.h"

bool check_range(char **colors)
{
	t_pt pt;

	pt.x = 0;
	while (colors[(int)pt.x])
	{
		pt.y = 0;
		while (colors[(int)pt.x][(int)pt.y])
		{
			if (ft_isdigit(colors[(int)pt.x][(int)pt.y]) == 0)
			{
				return false;
			}
			pt.y++;
		}
		if (ft_atoi(colors[(int)pt.x]) < 0 || ft_atoi(colors[(int)pt.x]) > 255)
		{
			return false;
		}
		pt.x++;
	}
    return true;
}

bool get_rgb2(char *line, t_fc *fc)
{
    char **colors;
	colors = ft_split(line, ',');
    if (!colors)
    {
		errorhandler(NULL,"* Memory allocation failed for colors *", false);
        // ft_putstr_fd("Error\n* Memory allocation failed for colors *\n\n", 2);
        return false;
    }
	if (remove_spaces(colors) == false)
	{
		return false;
	}
    if ((arr_size(colors) != 3) || (check_range(colors) == false))
    {
		errorhandler(NULL ,"* Invalid parmeters for colors *", false);
        // ft_putstr_fd("Error\n* Invalid parmeters for colors *\n\n", 2);
        free_arr(colors);
		colors = NULL;
        return false;
    }
	else 
	{
		fc->R = ft_atoi(colors[0]);
		fc->G = ft_atoi(colors[1]);
		fc->B = ft_atoi(colors[2]);
		fc->OK = true;
	}
    free_arr(colors);
	colors = NULL;
	return (true);
}

bool get_rgb1(char *line, char *str, t_fc *fc, t_main *game)
{
	(void)game;
    if (ft_strncmp(line, str, 1) == 0 && is_space(line[1]) == true)
    {
        char *sub = remove_wspace(line, 2);
        if (get_rgb2(sub, fc) == true)
        {
            free(sub);  // Clean up substring memory
            sub = NULL;
			return true;  // Return false if RGB extraction fails
        }
        free(sub);
		sub = NULL;  // Clean up substring memory
        return false;  // Return true if successful
    }
    return true;  // Return false if the line doesn't match
}

bool check_wall_component(char *line, char *identifier, char **wall_ptr)
{
	char *tmp;
	tmp = NULL;
    if (ft_strncmp(line, identifier, 2) == 0 && !(*wall_ptr))
    {
        if (is_space(line[2]) == true)
        {
			tmp = remove_wspace(line, 3);
			if (is_empty_line(tmp) == false)
			{
				*wall_ptr = tmp;
				return true;
			}
			free(tmp);
			tmp = NULL;
        }
        ft_putstr_fd("Error\n* Invalid format for ", 2);
        ft_putstr_fd(identifier, 2);
        ft_putstr_fd(" wall *\n", 2);
        return false;
    }
    return true;
}

bool check_contents(char *line, t_main *game)
{
	if (game->walls->NO && game->walls->SO && game->walls->WE && game->walls->EA)
		game->walls->walls_OK = true;
	if (get_rgb1(line, "F", game->floor, game) == false)
        return false;
	else if (get_rgb1(line, "C", game->ceil, game) == false)
        return false;
    else if (!check_wall_component(line, "NO", &game->walls->NO))
        return false;
    else if (!check_wall_component(line, "SO", &game->walls->SO))
        return false;
    else if (!check_wall_component(line, "WE", &game->walls->WE))
        return false;
    else if (!check_wall_component(line, "EA", &game->walls->EA))
        return false;
	else
		return true;
}

bool	create_sqmap(t_main *game)
{
	t_pt pt;
	
	game->sq_map = allocate2DCharArray(game->h_map + 1, game->w_map);
	pt.y = 0;
	while(pt.y < game->h_map)
	{
		pt.x = 0;
		while (pt.x < game->w_map)
		{
			if (pt.x < game->wx_map[(int)pt.y])
			{
				game->sq_map[(int)pt.y][(int)pt.x] = game->map_arr[(int)pt.y][(int)pt.x];
			}
			else
			{
				game->sq_map[(int)pt.y][(int)pt.x] = '_';
			}
			pt.x++;
		}
		game->sq_map[(int)pt.y][(int)pt.x] = '\0';
		pt.y++;
	}
	game->sq_map[(int)pt.y] = NULL;
	return true;
}

bool	extract_components(int fd, char *line, t_main *game)
{
	if (check_contents(line, game) == false)
        return false;
	if (game->walls->walls_OK == true && game->floor->OK && game->ceil->OK)
	{
		if (extract_map1(fd, game) == false)
		{
			return false;
    	}
		if (check_fill(game) == false)
		{
			errorhandler(game,"* Invalid map *", false);
			return false;
		}
		if (create_sqmap(game) == false)
		{
			return false;	
		}
	}
	return true;
}
