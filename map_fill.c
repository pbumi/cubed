/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_fill.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 17:25:12 by pbumidan          #+#    #+#             */
/*   Updated: 2024/12/21 16:49:15 by pbumidan         ###   ########.fr       */
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

void mark_lrborders(char **array, int rows, int cols)
{
    int y = 0;
    
    // Mark '0's connected to the left and right borders
    while (y < rows) 
    {
        if (array[y][0] == '0') 
            mark_zeroes(array, 0, y, rows, cols);  // Left border
        if (array[y][cols - 1] == '0') 
            mark_zeroes(array, cols - 1, y, rows, cols);  // Right border
        y++;
    }
}


void mark_tbborders(char **array, int rows, int cols)
{
    int x = 0;
    
    // Mark '0's connected to the top and bottom borders
    while (x < cols) 
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
    
    // Mark '0's connected to spaces
    while (y < rows) 
    {
        int x = 0;
        while (x < cols) 
        {
            if (array[y][x] == '0') 
            {
                // Check if adjacent to a space
                if ((y > 0 && array[y - 1][x] == ' ') ||
                    (y < rows - 1 && array[y + 1][x] == ' ') ||
                    (x > 0 && array[y][x - 1] == ' ') ||
                    (x < cols - 1 && array[y][x + 1] == ' ')) 
                {
                    mark_zeroes(array, x, y, rows, cols);  // Mark the '0' connected to a space
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
    
    // Check if any 'X' exists in the array
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
    // Print array before marking
    // printf("Before marking border and space-connected '0's:\n");
    // for (int i = 0; i < rows; i++) 
    // {
    //     printf("%s\n", tmp_arr[i]);
    // }

    // Mark the borders and space-connected '0's
    mark_lrborders(tmp_arr, rows, cols);
    mark_tbborders(tmp_arr, rows, cols);
    mark_spaces(tmp_arr, rows, cols);
    mark_player(game, tmp_arr, rows, cols);

    // // Print array after marking
    // printf("After marking border and space-connected '0's:\n");
    // for (int i = 0; i < rows; i++) 
    // {
    //     printf("%s\n", tmp_arr[i]);
    // }

    // If any 'X' was marked, return false
    if (check_for_X(tmp_arr, rows, cols)) 
        return false;

    return true;
}

bool check_fill(t_data *game)
{
    char **tmp_arr;
    t_int_pt pt;
    
    tmp_arr = malloc(sizeof(char *) * (game->m.y + 1));
    if (!tmp_arr)
    {
        return false;
    }
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
    if (check_floodfill(game, tmp_arr, game->m.y, game->m.x) == false)
    {
        free_arr(tmp_arr);
        return false;
    }
    free_arr(tmp_arr);
    return true;
}
