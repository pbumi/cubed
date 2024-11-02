/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:13:36 by pbumidan          #+#    #+#             */
/*   Updated: 2024/10/31 17:16:01 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cubed.h"

bool incorrect_mapcharacter(char *line)
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
			printf("Error\n");
			printf("* Invalid character : '%c' in x:%ld y:%ld *\n\n", line[x], x_count, y_count);
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

bool incorrect_mapsize(char *line)
{
	size_t x;
	size_t x_count;
	size_t y_count;
	
	x = 0;
	x_count = 0;
	y_count	= 0;
	while (line[x])
    {
        if (line[x] == '\n')
        {
			y_count++;
			if (x_count < 2 || x_count > 500) // MIN MAX X
			{
				return true;
			}
			x_count = -1;
		}
		x_count++;
        x++;
    }
	if (y_count < 2 || y_count > 500) // MIN MAX Y
	{
		return true;
	}
    return false; 
}

bool is_broken_map(char *line)
{
	size_t x;
	
	x = 0;
	while (line[x + 1])
    {
        if (line[x] == '\n' && line[x + 1] == '\n')
            return true;
        x++;
    }
    return false; 
}

bool	validate_map(t_main *game)
{
	if (is_empty_line(game->map) == true)
	{
		errorhandler(game, "* Empty MAP *", false);
		return false;
	}
	if (is_broken_map(game->map) == true)
	{
		errorhandler(game, "* Empty lines in MAP *", false);
		return false;
	}
	if (incorrect_mapsize(game->map) == true)
	{
		errorhandler(game, "* Incorrect MAP size *", false);
		return false;
	}
	if (incorrect_mapcharacter(game->map) == true)
	{
		errorhandler(game, "* Incorrect MAP character*", false);
		return false;	
	}
	return true;
}