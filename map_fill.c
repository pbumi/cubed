/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_fill.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 17:25:12 by pbumidan          #+#    #+#             */
/*   Updated: 2025/02/15 19:37:41 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	mark_zeroes(char **array, int x, int y, t_int_pt rc)
{
	if (x < 0 || y < 0 || x >= rc.x || y >= rc.y
		|| (array[y][x] != '0' && array[y][x] != ' '))
	{
		return ;
	}
	array[y][x] = 'X';
	mark_zeroes(array, x - 1, y, rc);
	mark_zeroes(array, x + 1, y, rc);
	mark_zeroes(array, x, y - 1, rc);
	mark_zeroes(array, x, y + 1, rc);
}

static void	mark_player(t_data *game, char **array, int rows, int cols)
{
	int	x;
	int	y;

	x = game->p.x;
	y = game->p.y;
	if ((y > 0 && array[y - 1][x] == ' ') ||
		(y < rows - 1 && array[y + 1][x] == ' ') ||
		(x > 0 && array[y][x - 1] == ' ') ||
		(x < cols - 1 && array[y][x + 1] == ' '))
	{
		array[y][x] = 'X';
	}
}

static void	mark_borders(char **array, t_int_pt rc)
{
	int	y;
	int	x;

	y = 0;
	while (y < rc.y)
	{
		if (array[y][0] == '0')
			mark_zeroes(array, 0, y, rc);
		if (array[y][rc.x - 1] == '0')
			mark_zeroes(array, rc.x - 1, y, rc);
		y++;
	}
	x = 0;
	while (x < rc.x)
	{
		if (array[0][x] == '0')
			mark_zeroes(array, x, 0, rc);
		if (array[rc.y - 1][x] == '0')
			mark_zeroes(array, x, rc.y - 1, rc);
		x++;
	}
}

static void	mark_spaces(char **array, t_int_pt rc)
{
	int	y;
	int	x;

	y = 0;
	while (y < rc.y)
	{
		x = 0;
		while (x < rc.x)
		{
			if (array[y][x] == '0')
			{
				if ((y > 0 && array[y - 1][x] == ' ') ||
					(y < rc.y - 1 && array[y + 1][x] == ' ') ||
					(x > 0 && array[y][x - 1] == ' ') ||
					(x < rc.x - 1 && array[y][x + 1] == ' '))
				{
					mark_zeroes(array, x, y, rc);
				}
			}
			x++;
		}
		y++;
	}
}

bool	check_floodfill(t_data *game, char **tmp_arr, int rows, int cols)
{
	t_int_pt	rc;
	int			y;
	int			x;

	rc.x = cols;
	rc.y = rows;
	mark_borders(tmp_arr, rc);
	mark_spaces(tmp_arr, rc);
	mark_player(game, tmp_arr, rows, cols);
	y = 0;
	while (y < rows)
	{
		x = 0;
		while (x < cols)
		{
			if (tmp_arr[y][x] == 'X')
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}
