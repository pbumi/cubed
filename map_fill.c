/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_fill.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 17:25:12 by pbumidan          #+#    #+#             */
/*   Updated: 2024/12/02 15:49:19 by pbumidan         ###   ########.fr       */
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
    mark_zeroes(array, x - 1, y, rows, cols);
    mark_zeroes(array, x + 1, y, rows, cols);
    mark_zeroes(array, x, y - 1, rows, cols);
    mark_zeroes(array, x, y + 1, rows, cols);
}

void mark_borders(char **array, int rows, int *cols)
{
    int x;
    int y;
    
    // Check left and right borders
    y = 0;
    while (y < rows)
    {
        // Ensure the row has valid columns before accessing
        if (cols[y] > 0 &&array[y] != NULL) // Ensure we are within bounds for this row
        {
            if (array[y][0] == '0') // Check the left border
                mark_zeroes(array, 0, y, rows, cols[y]);
            if (array[y][cols[y] - 1] == '0') // Check the right border
                mark_zeroes(array, cols[y] - 1, y, rows, cols[y]);
        }
        y++;
    }
    // Check top and bottom borders
    if (rows > 0 && cols[0] > 0) 
    {
        x = 0;
        while (x < cols[0])
        {
            // Ensure top and bottom rows are valid and not empty
            if (array[0] != NULL && array[rows - 1] != NULL)
            {
                if (array[0][x] == '0') // Check the top border
                    mark_zeroes(array, x, 0, rows, cols[0]);
                if (array[rows - 1][x] == '0') // Check the bottom border
                    mark_zeroes(array, x, rows - 1, rows, cols[0]);
            }
            x++;
        }
    }
}


// void mark_borders(char **array, int rows, int *cols)
// {
//     int x;
//     int y;
    
//     y = 0;
//     while (y < rows)
//     {
//         if (cols[y] > 0) // Ensure we are within bounds
//         {
//             if (array[y][0] == '0') // Check the left and right borders
//                 mark_zeroes(array, 0, y, rows, cols[y]);
//             if (array[y][cols[y] - 1] == '0')
//                 mark_zeroes(array, cols[y] - 1, y, rows, cols[y]);
//         }
//         y++;
//     }
//     x = 0;
//     while (x < cols[0])
//     {
//         if (rows > 0 && cols[0] > 0) // Check top and bottom borders, ensuring valid row length
//         {
//             if (array[0][x] == '0')
//                 mark_zeroes(array, x, 0, rows, cols[0]);
//             if (array[rows - 1][x] == '0')
//                 mark_zeroes(array, x, rows - 1, rows, cols[0]);
//         }
//         x++;
//     }
// }

void   mark_spaces(char **array, int rows, int *cols)
{
    int y;
    int x;
    y = 0;
    while (y < rows)
    {
        x = 0;
        while (x < cols[y])
        {
            // If a '0' is adjacent to a space, mark it
            if (array[y][x] == '0')
            {
                if ((y > 0 && array[y - 1][x] == ' ') ||
                    (y < rows - 1 && array[y + 1][x] == ' ') ||
                    (x > 0 && array[y][x - 1] == ' ') ||
                    (x < cols[y] - 1 && array[y][x + 1] == ' ')) 
                {
                    mark_zeroes(array, x, y, rows, cols[y]);
                }
            }
            x++;
        }
        y++;
    }
}

bool    check_for_X(char **tmp_arr, int rows, int *cols)
{
    int y;
    int x;
    y = 0;
    while (y < rows) 
    {
        x = 0;
        while (x < cols[y])
        {
            if (tmp_arr[y][x] == 'X')
            {
                return true;
            }
            x++;
        }
        y++;
    }
    return false;
}


// Main function to check the floodfill and update the map
bool check_floodfill(char **tmp_arr, int rows, int* cols) 
{
    mark_borders(tmp_arr, rows, cols);
    mark_spaces(tmp_arr, rows, cols);
    return !check_for_X(tmp_arr, rows, cols); 
    // if (check_for_X(tmp_arr, rows, cols) == true)
    //     return false;
    // // printf("After marking border and space-connected '0's:\n");
    // // for (int i = 0; i < rows; i++) {
    // //     printf("%s\n", tmp_arr[i]);
    // // }
    // return true;
}

bool	check_fill(t_main *game)
{
	char *tmp;
	char **tmp_arr;

	tmp = ft_strdup(game->map);
	tmp_arr = ft_split(tmp,'\n');
    free(tmp);
    // for (int i = 0; tmp_arr[i] != NULL; i++)
    // {
    //     printf("%s\n", tmp_arr[i]);
    // }
    int rows;
    rows = 0;
    while (tmp_arr[rows] != NULL)
    {
        rows++;
    }
    int *cols;
    cols = malloc(sizeof(int) * rows);
    int y;
    y = 0;
    while (y < rows)
    {
        cols[y] = ft_strlen(tmp_arr[y]);
        y++;
    }
    if (check_floodfill(tmp_arr, rows, cols) == false)
    {
        free(cols);
        //free_arr(tmp_arr);
        return false;
    }
    free(cols);
    //free_arr(tmp_arr);
    return true;
}
