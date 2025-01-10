/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_fill.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 17:25:12 by pbumidan          #+#    #+#             */
/*   Updated: 2025/01/10 20:25:32 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cubed.h"

static void mark_zeroes(char **array, int x, int y, int rows, int cols) 
{
    if (x < 0 || y < 0 || x >= cols || y >= rows || 
        (array[y][x] != '0' && array[y][x] != ' '))
    {
        return;
    }
    array[y][x] = 'X';
    mark_zeroes(array, x - 1, y, rows, cols);
    mark_zeroes(array, x + 1, y, rows, cols);
    mark_zeroes(array, x, y - 1, rows, cols);
    mark_zeroes(array, x, y + 1, rows, cols);
}

static void mark_player(t_data *game, char **array, int rows, int cols)
{
    int x = game->p.x;
    int y = game->p.y;
    
    if ((y > 0 && array[y - 1][x] == ' ') ||
        (y < rows - 1 && array[y + 1][x] == ' ') ||
        (x > 0 && array[y][x - 1] == ' ') ||
        (x < cols - 1 && array[y][x + 1] == ' '))
    {
        array[y][x] = 'X';
    }
}

static void mark_borders(char **array, int rows, int cols)
{
    int y; 
    int x;
    
    y = 0;
    while (y < rows) //l_r 
    {
        if (array[y][0] == '0') 
            mark_zeroes(array, 0, y, rows, cols);
        if (array[y][cols - 1] == '0') 
            mark_zeroes(array, cols - 1, y, rows, cols);
        y++;
    }
    x = 0;
    while (x < cols) //t_b
    {
        if (array[0][x] == '0') 
            mark_zeroes(array, x, 0, rows, cols);
        if (array[rows - 1][x] == '0') 
            mark_zeroes(array, x, rows - 1, rows, cols);
        x++;
    }
}

static void mark_spaces(char **array, int rows, int cols)
{
    int y = 0;
    
    while (y < rows) 
    {
        int x = 0;
        while (x < cols) 
        {
            if (array[y][x] == '0') 
            {
                if ((y > 0 && array[y - 1][x] == ' ') ||
                    (y < rows - 1 && array[y + 1][x] == ' ') ||
                    (x > 0 && array[y][x - 1] == ' ') ||
                    (x < cols - 1 && array[y][x + 1] == ' ')) 
                {
                    mark_zeroes(array, x, y, rows, cols);
                }
            }
            x++;
        }
        y++;
    }
}

static bool check_for_X(char **tmp_arr, int rows, int cols)
{
    int y = 0, x;
    
    while (y < rows) 
    {
        x = 0;
        while (x < cols) 
        {
            if (tmp_arr[y][x] == 'X') 
                return true;
            x++;
        }
        y++;
    }
    return false;
}

bool check_floodfill(t_data *game, char **tmp_arr, int rows, int cols) 
{
    mark_borders(tmp_arr, rows, cols);
    mark_spaces(tmp_arr, rows, cols);
    mark_player(game, tmp_arr, rows, cols);
    if (check_for_X(tmp_arr, rows, cols))
    {
        return false;
    }
    return true;
}
