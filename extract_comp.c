/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_comp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:02:54 by pbumidan          #+#    #+#             */
/*   Updated: 2024/12/21 16:48:23 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cubed.h"

bool check_range(char **colors)
{
	t_int_pt pt;

	pt.x = 0;
	while (colors[pt.x])
	{
		pt.y = 0;
		while (colors[pt.x][pt.y])
		{
			if (ft_isdigit(colors[pt.x][pt.y]) == 0)
			{
				return false;
			}
			pt.y++;
		}
		if (ft_atoi(colors[pt.x]) < 0 || ft_atoi(colors[pt.x]) > 255)
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
        errorhandler(NULL, "* Memory allocation failed for colors *", false);
        return false;
    }
    if (remove_spaces(colors) == false)
    {
        free_arr(colors);  // Free memory before returning on failure
        return false;
    }
    if (arr_size(colors) != 3 || check_range(colors) == false)
    {
        errorhandler(NULL, "* Invalid parameters for colors *", false);
        free_arr(colors);  // Free memory before returning on failure
        return false;
    }
    fc->R = ft_atoi(colors[0]);
    fc->G = ft_atoi(colors[1]);
    fc->B = ft_atoi(colors[2]);
    fc->OK = true;
    free_arr(colors);
    return true;
}
bool get_rgb1(char *line, char *str, t_fc *fc, t_data *game)
{
    (void)game;  // Unused parameter, can be kept for future use or removed if not needed.

    // Check if the line starts with the expected string and has a space after it
    if (ft_strncmp(line, str, 1) == 0 && is_space(line[1]) == true)
    {
        // Remove whitespace from the start and end
        char *sub = remove_wspace(line, 2);
        if (!sub)  // If removing whitespace failed
        {
            return false;
        }

        // Now extract RGB values using get_rgb2
        if (get_rgb2(sub, fc))  // If RGB extraction succeeds
        {
            free(sub);  // Free the substring memory
            return true;  // Successfully extracted RGB
        }

        // If RGB extraction fails, free the memory and return false
        free(sub);
        return false;
    }

    // If the line does not match the expected format, return true
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

bool check_wall_component(char *line, char *identifier, char **wall_ptr)
{
    char *tmp = NULL;

    // Check if line starts with the identifier and if wall_ptr is NULL (i.e., not yet assigned)
    if (ft_strncmp(line, identifier, 2) == 0 && !(*wall_ptr))
    {
        // Check if the next character is a space
        if (is_space(line[2]) == true)
        {
            tmp = remove_wspace(line, 3);  // Remove leading and trailing spaces from the line starting from index 3
            if (tmp && !is_empty_line(tmp))  // If not an empty line after trimming
            {
                *wall_ptr = tmp;  // Assign the trimmed string to the wall pointer
                return true;  // Successfully set the wall component
            }

            // If the line is empty or incorrectly formatted, free tmp and return false
            free(tmp);
            tmp = NULL;
        }

        // Error message for invalid format
        ft_putstr_fd("Error\n* Invalid format for ", 2);
        ft_putstr_fd(identifier, 2);
        ft_putstr_fd(" wall *\n", 2);
        return false;  // Return false if the wall component is not valid
    }

    return true;  // Return true if the wall component was already set or the line is valid
}

// bool check_wall_component(char *line, char *identifier, char **wall_ptr)
// {
// 	char *tmp;
// 	tmp = NULL;
//     if (ft_strncmp(line, identifier, 2) == 0 && !(*wall_ptr))
//     {
//         if (is_space(line[2]) == true)
//         {
// 			tmp = remove_wspace(line, 3);
// 			if (is_empty_line(tmp) == false)
// 			{
// 				*wall_ptr = tmp;
// 				return true;
// 			}
// 			free(tmp);
// 			tmp = NULL;
//         }
//         ft_putstr_fd("Error\n* Invalid format for ", 2);
//         ft_putstr_fd(identifier, 2);
//         ft_putstr_fd(" wall *\n", 2);
//         return false;
//     }
//     return true;
// }

bool check_contents(char *line, t_data *game)
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

// void    fill_plane_dir(t_data *game)
// {
//     game->pdir.x = 1.0;
//     game->pdir.y = 0.0;
//     game->pplane.x = 0.0;
//     game->pplane.y = 0.66;
    
//     if (game->map2d[(int)game->ppos.y][(int)game->ppos.x] == 'N')
//     {
//         game->pdir.x = 0.0;
//         game->pdir.y = -1.0;
//         game->pplane.x = 0.66;
//         game->pplane.y = 0.0;
//     }
//     else if (game->map2d[(int)game->ppos.y][(int)game->ppos.x] == 'S')
//     {
//         game->pdir.x = 0.0;
//         game->pdir.y = 1.0;
//         game->pplane.x = -0.66;
//         game->pplane.y = 0.0;
//     }
//     else if (game->map2d[(int)game->ppos.y][(int)game->ppos.x] == 'W')
//     {
//         game->pdir.x = -1.0;
//         game->pplane.y = -0.66;
//     }
// }

// void    fill_plane_dir(t_data *game)
// {
//     if (game->map2d[(int)game->ppos.y][(int)game->ppos.x] == 'N')
//     {
//         game->pdir.x = 0.0;
//         game->pdir.y = -1.0;
//         game->pplane.x = 0.66;
//         game->pplane.y = 0.0;
//     }
//     else if (game->map2d[(int)game->ppos.y][(int)game->ppos.x] == 'S')
//     {
//         game->pdir.x = 0.0;
//         game->pdir.y = 1.0;
//         game->pplane.x = -0.66;
//         game->pplane.y = 0.0;
//     }
//     else if (game->map2d[(int)game->ppos.y][(int)game->ppos.x] == 'E')
//     {
//         game->pdir.x = 1.0;
//         game->pdir.y = 0.0;
//         game->pplane.x = 0.0;
//         game->pplane.y = 0.66;
//     }
//     else if (game->map2d[(int)game->ppos.y][(int)game->ppos.x] == 'W')
//     {
//         game->pdir.x = -1.0;
//         game->pdir.y = 0.0;
//         game->pplane.x = 0.0;
//         game->pplane.y = -0.66;
//     }
// }


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
                game->p.x = pt.x;  // Set the x-coordinate of the player
                game->p.y = pt.y;  // Set the y-coordinate of the player
                return;  // Player position found, exit the function
            }
            pt.x++;  // Move to the next character in the current row
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
	printf("pty %d,g_h %d\n", pt.y, game->m.y);
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
    {
        return false;
    }
    get_height(game, tmp_arr);
    tmp_wx = malloc(sizeof(int) * game->m.y);
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
	tmp_arr = NULL;
    free(tmp_wx);
	tmp_wx = NULL;
    return true;
}

bool	extract_components(int fd, char *line, t_data *game)
{
	if (check_contents(line, game) == false)
        return false;
	if (game->walls->walls_OK == true && game->floor->OK && game->ceil->OK)
	{
		if (extract_map1(fd, game) == false)
		{
			return false;
		}
		if (create_sqmap(game) == false)
		{
			return false;	
		}
		fill_player_position(game);
		// fill_plane_dir(game);
		if (check_fill(game) == false)
		{
			errorhandler(game,"* Invalid map *", false);
			return false;
		}
	}
	return true;
}
