/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:50:32 by pbumidan          #+#    #+#             */
/*   Updated: 2025/02/22 19:08:26 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static size_t	arr_size(char **arr)
{
	size_t	count;

	count = 0;
	while (arr[count] != NULL)
	{
		count++;
	}
	return (count);
}

static bool	check_range(char **color)
{
	t_int_pt	pt;
	int			x;

	pt.y = 0;
	while (color[pt.y])
	{
		x = 0;
		while (color[pt.y][x] == ' ')
			x++;
		if (color[pt.y][x] == '\0')
			return (false);
		pt.x = 0;
		while (color[pt.y][pt.x])
		{
			if (ft_isdigit(color[pt.y][pt.x]) == 0 && color[pt.y][pt.x] != ' ')
			{
				return (false);
			}
			pt.x++;
		}
		if (ft_atoi(color[pt.y]) < 0 || ft_atol(color[pt.y]) > 255)
			return (false);
		pt.y++;
	}
	return (true);
}

static void	set_color(t_data *game, char *str, char **colors)
{
	int	r;
	int	g;
	int	b;

	r = (ft_atoi(colors[0]));
	g = (ft_atoi(colors[1]));
	b = (ft_atoi(colors[2]));
	if (ft_strncmp(str, "F", 1) == 0)
	{
		game->floor_color = ((b << 24) | (g << 16) | (r << 8) | 0xFF);
		game->floor = true;
	}
	else if (ft_strncmp(str, "C ", 1) == 0)
	{
		game->ceil_color = ((b << 24) | (g << 16) | (r << 8) | 0xFF);
		game->ceil = true;
	}
}

static bool	get_rgb(char *line, t_data *game, char *str)
{
	char	**colors;

	colors = ft_split(line, ',');
	if (!colors)
	{
		error_msg("* rgb2: Memory allocation failed for colors *");
		return (false);
	}
	if (arr_size(colors) != 3 || check_range(colors) == false)
	{
		error_msg("* Invalid parameters for colors *");
		free_arr(colors);
		colors = NULL;
		return (false);
	}
	set_color(game, str, colors);
	free_arr(colors);
	colors = NULL;
	return (true);
}

bool	parse_rgb(char *line, char *str, t_data *game)
{
	char	*sub;

	if (ft_strncmp(line, str, 2) == 0)
	{
		sub = remove_wspace(line, 2);
		if (!sub)
		{
			error_msg("* Memory allocation failed for colors *");
			return (false);
		}
		if (get_rgb(sub, game, str))
		{
			free(sub);
			return (true);
		}
		free(sub);
		return (false);
	}
	return (true);
}
