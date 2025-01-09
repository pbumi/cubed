/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_fill.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 17:25:12 by pbumidan          #+#    #+#             */
/*   Updated: 2025/01/04 21:11:14 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cubed.h"

void mark_zeroes(char **array, int x, int y, int rows, int cols) 
{
    if (x < 0 || y < 0 || x >= cols || y >= rows || 
        (array[y][x] != '0' && array[y][x] != ' '))
    {
        return;
    }
    array[y][x] = 'X';
    mark_zeroes(array, x - 1, y, rows, cols); // left
    mark_zeroes(array, x + 1, y, rows, cols); // right
    mark_zeroes(array, x, y - 1, rows, cols); // up
    mark_zeroes(array, x, y + 1, rows, cols); // down
}

void mark_player(t_data *game, char **array, int rows, int cols)
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

void mark_borders(char **array, int rows, int cols)
{
    int y; 
    int x;
    
    y = 0;
    while (y < rows) //l_r 
    {
        if (array[y][0] == '0') 
            mark_zeroes(array, 0, y, rows, cols);  // Left border
        if (array[y][cols - 1] == '0') 
            mark_zeroes(array, cols - 1, y, rows, cols);  // Right border
        y++;
    }
    x = 0;
    while (x < cols) //t_b
    {
        if (array[0][x] == '0') 
            mark_zeroes(array, x, 0, rows, cols);  // Top border
        if (array[rows - 1][x] == '0') 
            mark_zeroes(array, x, rows - 1, rows, cols);  // Bottom border
        x++;
    }
}

void mark_spaces(char **array, int rows, int cols)
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

bool check_for_X(char **tmp_arr, int rows, int cols)
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

bool fill_tmparr(t_data *game, char **tmp_arr)
{
    t_int_pt pt;
    
    pt.y = 0;
    while (pt.y < game->m.y)
    {
        tmp_arr[pt.y] = ft_strdup(game->map2d[pt.y]);
        if (!tmp_arr[pt.y])  // Allocation failed
        {
            while (pt.y > 0)
            {
                free(tmp_arr[pt.y - 1]);
                pt.y--;
            }
            free(tmp_arr);  // Free the array itself
            return false;   // Return failure
        }
        pt.y++;
    }
    tmp_arr[pt.y] = NULL;  // Null-terminate the array
    return true;
}

bool check_fill(t_data *game)
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
