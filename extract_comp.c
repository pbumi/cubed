/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_comp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:02:54 by pbumidan          #+#    #+#             */
/*   Updated: 2025/01/10 20:51:10 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static bool	fill_tmparr(t_data *game, char **tmp_arr)
{
    t_int_pt pt;
    
    pt.y = 0;
    while (pt.y < game->m.y)
    {
        tmp_arr[pt.y] = ft_strdup(game->map2d[pt.y]);
        if (!tmp_arr[pt.y])
        {
            while (pt.y > 0)
            {
                free(tmp_arr[pt.y - 1]);
                pt.y--;
            }
            free(tmp_arr);
            return false;
        }
        pt.y++;
    }
    tmp_arr[pt.y] = NULL;
    return true;
}

static bool check_fill(t_data *game)
{
    char **tmp_arr;

    tmp_arr = ft_calloc(game->m.y + 1, sizeof(char *));
    if (!tmp_arr)  
        return false;
    if (fill_tmparr(game, tmp_arr) == false)
    {
        free_arr(tmp_arr);
        return false;
    }
    if (check_floodfill(game, tmp_arr, game->m.y, game->m.x) == false)
    {
        free_arr(tmp_arr);
        return false;
    }
    free_arr(tmp_arr);
    return true;
}

static void	fill_player_position(t_data *game)
{
    t_int_pt pt;

    pt = (t_int_pt){0, 0};
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

static bool parse_contents(char *line, t_data *game)
{	
	if (game->w && game->s && game->w && game->e)
		game->wall = true;
	if (parse_rgb(line, "F ", game) == false)
        return false;
	if (parse_rgb(line, "C ", game) == false)
        return false;
    if (!parse_wall(line, "NO ", game, &game->n))
        return false;
    if (!parse_wall(line, "SO ", game, &game->s))
        return false;
    if (!parse_wall(line, "WE ", game, &game->w))
        return false;
    if (!parse_wall(line, "EA ", game, &game->e))
        return false;
	else
		return true;
}

bool	extract_components(int fd, char *line, t_data *game)
{
	if (parse_contents(line, game) == false)
        return false;
	if (game->wall && game->floor && game->ceil)
	{
		if (extract_map(fd, game) == false)
		{
            error_msg("* Map extraction failed *");
			return false;
		}
        else if (validate_map(game) == false)
            return false;
		else if (create_sqmap(game) == false)
		{
            error_msg("* Map creation failed *");
			return false;	
		}
		fill_player_position(game);
		if (check_fill(game) == false)
		{
			error_msg("* Invalid map borders/spaces *");
			return false;
		}
	}
	return true;
}
