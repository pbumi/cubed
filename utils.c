/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:25:27 by pbumidan          #+#    #+#             */
/*   Updated: 2025/01/03 17:40:20 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cubed.h"

void	error_exit(char *msg, bool fatal)
{
	if (msg)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putendl_fd(msg, 2);	
	}
	if (fatal)
	{
		exit(1);
	}
}

void	errorhandler(t_data *game, char *msg, bool fatal)
{
	if (game)
	{
		free_struct(game);
	}	
	if (msg)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putendl_fd(msg, 2);	
	}
	if (fatal)
	{
		exit(1);
	}
}

size_t  arr_size(char **arr)
{
    size_t count;
    
    count = 0;
    while (arr[count] != NULL)
    {
        count++;
    }
    return (count);
}

char** allocate2DCharArray(int y, int x)
{
    char **arr;
    t_int_pt pt;
    
    pt.x = 0;
    arr = ft_calloc(y + 1, sizeof(char *));
    if (arr == NULL)
        return NULL; // Memory allocation failed
    while (pt.x < y)
    {
        arr[pt.x] = ft_calloc(x + 1, sizeof(char)); // Allocate memory for each row
        if (arr[pt.x] == NULL)
        {
            pt.y = 0;
            while (pt.y < pt.x)
            {
                free(arr[pt.y]);
                pt.y++;
            }
            free(arr);
            return NULL; // Return NULL to indicate failure
        }
        pt.x++;
    }
    return arr; // Return the 2D array
}



int find_max(int *arr, int size)
{
    int max = arr[0];  // Assume the first element is the max initially

    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];  // Update max if current element is greater
        }
    }
    return max;
}
