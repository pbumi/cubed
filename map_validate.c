/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:13:36 by pbumidan          #+#    #+#             */
/*   Updated: 2025/01/10 19:53:39 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cubed.h"

static bool duplicate_player(char *line)
{
	size_t x;
	int player;
	
	x = 0;
	player = 0;
	while (line[x])
    {
		if (ft_strchr("NSWE", line[x]))
		{
			player++;
		}
        x++;
    }
	if (player > 1 || player == 0)
	{	
		return true;
	}
    return false; 
}

static bool incorrect_mapcharacter(char *line)
{
	size_t x;
	size_t x_count;
	size_t y_count;
	
	x = 0;
	x_count = 0;
	y_count	= 0;
	while (line[x])
    {
		x_count++;
		if (!ft_strchr(" 01NSWE\n", line[x]))
		{
			return true;
		}
        if (line[x] == '\n')
        {
			y_count++;
			x_count = -1;
		}
        x++;
    }
    return false; 
}

static bool incorrect_mapsize(char *line)
{
	t_int_pt count;
	size_t x;
	
	x = 0;
	count = (t_int_pt){0, 0};
	while (line[x])
    {
        if (line[x] == '\n')
        {
			count.y++;
			if (count.x < 2 || count.x > 500)
			{
				return true;
			}
			count.x = -1;
		}
		count.x++;
        x++;
    }
	if (count.y < 2 || count.y > 500)
	{
		return true;
	}
    return false; 
}

static bool is_broken_or_empty_line(char *line)
{
    size_t x; 
	x = 0;
    while (line[x]) 
    {
        if (line[x] == '\n' && line[x + 1] == '\n')
        {
            return true;
        }
        x++;
    }
    x = 0; 
    while (line[x]) 
    {
        if (!(line[x] == 32 || (line[x] >= 9 && line[x] <= 13)) && line[x] != '\n')
            return false;
        x++;
    }
    return true;
}

bool validate_map(t_data *game)
{
	if (is_broken_or_empty_line(game->map))
		error_msg("* Empty MAP or Broken MAP *");
	else if (incorrect_mapsize(game->map))
		error_msg("* Invalid MAP size *");
	else if (incorrect_mapcharacter(game->map))
		error_msg("* Invalid character in MAP *");
	else if (duplicate_player(game->map))
		error_msg("* Multiple/No players in map *");
	else
	{
		return true;
	}
	return false;
}
