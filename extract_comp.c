/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_comp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:02:54 by pbumidan          #+#    #+#             */
/*   Updated: 2025/01/04 21:01:55 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cubed.h"

bool check_range(char **colors)
{
	t_int_pt pt;

	pt.y = 0;
	while (colors[pt.y])
	{
		pt.x = 0;
		while (colors[pt.y][pt.x])
		{
			if (ft_isdigit(colors[pt.y][pt.x]) == 0 && colors[pt.y][pt.x] != ' ')
            {
                return false;
            }
			pt.x++;
		}
        if (ft_atoi(colors[pt.y]) < 0 || ft_atoi(colors[pt.y]) > 255)
		{
			return false;
		}
		pt.y++;
	}
    return true;
}

void set_color(t_data *game, char *str, char **colors)
{
    int r;
    int g;
    int b;

    r = (ft_atoi(colors[0]));
    g = (ft_atoi(colors[1]));
    b = (ft_atoi(colors[2]));
    if (ft_strncmp(str, "F", 1) == 0)
    {
        game->Fcolor = ((b << 24) | (g << 16) | (r << 8) | 0xFF);
        game->F = true;
    }
    else if (ft_strncmp(str, "C", 1) == 0)
    {
        game->Ccolor = ((b << 24) | (g << 16) | (r << 8) | 0xFF);
        game->C = true;
    }
}

bool get_rgb2(char *line, t_data *game, char *str)
{
    char **colors;
    colors = ft_split(line, ',');
    if (!colors)
    {
        error_msg("* Memory allocation failed for colors *");
        return false;
    }
    if (arr_size(colors) != 3 || check_range(colors) == false)
    {
        error_msg("* Invalid parameters for colors *");
        free_arr(colors); 
        colors = NULL;
        return false;
    }
    set_color(game, str, colors);
    free_arr(colors);
    colors = NULL;
    return true;
}

bool get_rgb1(char *line, char *str, t_data *game)
{
    char *sub;
    
    if (ft_strncmp(line, str, 1) == 0 && is_space(line[1]) == true)
    {
        sub = remove_wspace(line, 2);
        if (!sub)
        {
            error_msg("* Malloc error");
            return false;
        }
        if (get_rgb2(sub, game, str))
        {
            free(sub);
            return true;
        }
        free(sub);
        return false;
    }
    return true;
}

// bool get_rgb1(char *line, char *str, t_fc *fc, t_data *game)
// {
// 	(void)game;
//     if (ft_strncmp(line, str, 1) == 0 && is_space(line[1]) == true)
//     {
//         char *sub = remove_wspace(line, 2);
//         if (get_rgb2(sub, fc) == true)
//         {
//             free(sub);  // Clean up substring memory
//             sub = NULL;
// 			return true;  // Return false if RGB extraction fails
//         }
//         free(sub);
// 		sub = NULL;  // Clean up substring memory
//         return false;  // Return true if successful
//     }
//     return true;  // Return false if the line doesn't match
// }

// bool check_wall_component(char *line, char *identifier, char **wall_ptr)
// {
//     char *tmp = NULL;
//     if (ft_strncmp(line, identifier, 3) == 0 && wall_ptr == NULL)
//     {
//         tmp = remove_wspace(line, 3);  // Remove leading and trailing spaces from the line starting from index 3
//         if (tmp && !is_empty_line(tmp))  // If not an empty line after trimming
//         {
//            *wall_ptr = ft_strdup(tmp);
//             free(tmp);
//             tmp = NULL;
//             return true;  // Successfully set the wall component
//         }
//         else
//         {
//             free(tmp);
//             tmp = NULL;
//         }
//         ft_putstr_fd("Error\n* Invalid format for wall: ", 2);
//         ft_putstr_fd(identifier, 2);
//         return (false);
//     }
//     return (true);  // Return true if the wall component was already set or the line is valid
// }

bool check_wall_component(char *line, char *identifier, char **wall_ptr)
{
	char *tmp;
    
    if (ft_strncmp(line, identifier, 3) == 0 && *wall_ptr == NULL) // && *wall_ptr[0] != '\0')
    {
		tmp = remove_wspace(line, 3);
		if (is_empty_line(tmp) == false)
		{
			*wall_ptr = tmp;
			return true;
		}
        else
        {
		    free(tmp);
		    tmp = NULL;
            ft_putstr_fd("Error\n* Invalid format for ", 2);
            ft_putstr_fd(identifier, 2);
            ft_putstr_fd(" wall *\n", 2);
            return false;
        }
    }
    return true;
}

bool check_contents(char *line, t_data *game)
{
	if (game->NO && game->SO && game->WE && game->EA)
		game->W = true;
	if (get_rgb1(line, "F", game) == false)
        return false;
	if (get_rgb1(line, "C", game) == false)
        return false;
    if (!check_wall_component(line, "NO ", &game->NO))
        return false;
    if (!check_wall_component(line, "SO ", &game->SO))
        return false;
    if (!check_wall_component(line, "WE ", &game->WE))
        return false;
    if (!check_wall_component(line, "EA ", &game->EA))
        return false;
	else
		return true;
}

void fill_player_position(t_data *game)
{
    t_int_pt pt;

    pt.x = 0;
    pt.y = 0;
    while (game->map2d[pt.y] != NULL)
    {
        while (game->map2d[pt.y][pt.x] != '\0')
        {
            if (ft_strchr("NSWE", game->map2d[pt.y][pt.x]))
            {
                game->p.x = pt.x;
                game->p.y = pt.y;
                return;  
            }
            pt.x++;
        }
        pt.y++;
        pt.x = 0;
    }
}

void fill_maparray(t_data *game, int *tmp_wx, char **tmp_arr)
{
	t_int_pt pt;
	pt.y = 0;
	while(pt.y < game->m.y)
	{
		pt.x = 0;
		while (pt.x < game->m.x)
		{
			if (pt.x < tmp_wx[pt.y])
			{
				game->map2d[pt.y][pt.x] = tmp_arr[pt.y][pt.x];
			}
			else
			{
				game->map2d[pt.y][pt.x] = ' ';
			}
			pt.x++;
		}
		game->map2d[pt.y][pt.x] = '\0';
		pt.y++;
	}
	game->map2d[game->m.y] = NULL;
}

void get_widthx(t_data *game, char **tmp_arr, int *tmp_wx)
{
	int x;
    x = 0;
    while (x < game->m.y)
    {
        tmp_wx[x] = ft_strlen(tmp_arr[x]);  // Store the width of each row
        x++;
    }
    game->m.x = find_max(tmp_wx, game->m.y);
}

void get_height(t_data *game, char **tmp_arr)
{
	int y;
	y = 0;
	while (tmp_arr[y] != NULL) // Iterate until NULL (end of array)
    {
        y++;
    }
    game->m.y = y;
}

bool create_sqmap(t_data *game)
{
    char **tmp_arr;
    int *tmp_wx;
    
    tmp_arr = ft_split(game->map, '\n');
    if (!tmp_arr) 
        return false;
    get_height(game, tmp_arr);
    tmp_wx = ft_calloc(game->m.y, sizeof(int));
    if (tmp_wx == NULL)
    {
        free_arr(tmp_arr);  // Make sure to free tmp_arr before returning
        return false;  
    }
    get_widthx(game, tmp_arr, tmp_wx);
    game->map2d = allocate2DCharArray(game->m.y, game->m.x);
    if (!game->map2d)
    {
        free_arr(tmp_arr);  // Free tmp_arr on failure
        free(tmp_wx);       // Free tmp_wx on failure
        return false;
    }
    fill_maparray(game, tmp_wx, tmp_arr);
    free_arr(tmp_arr);
    free(tmp_wx);
    return true;
}

bool	extract_components(int fd, char *line, t_data *game)
{
	if (check_contents(line, game) == false)
        return false;
	if (game->W && game->F && game->C)
	{
		if (extract_map1(fd, game) == false)
		{
            error_msg("* Map extraction failed *");
			return false;
		}
		if (create_sqmap(game) == false)
		{
            error_msg("* Map creation failed *");
			return false;	
		}
		fill_player_position(game);
		if (check_fill(game) == false)
		{
			error_msg("* Invalid map *");
			return false;
		}
	}
	return true;
}
