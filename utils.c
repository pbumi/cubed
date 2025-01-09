/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:25:27 by pbumidan          #+#    #+#             */
/*   Updated: 2025/01/05 16:56:59 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cubed.h"

void    free_dt_exit(t_data *game, char *msg, int code)
{
    if (game)
	{
		free_data(game);
	}	
	if (msg)
	{
        error_msg(msg);
	}
	exit(code);
}
// void	error_exit(char *msg, bool fatal)
// {
// 	if (msg)
// 	{
// 		ft_putstr_fd("Error\n", 2);
// 		ft_putendl_fd(msg, 2);	
// 	}
// 	if (fatal)
// 	{
// 		exit(1);
// 	}
// }

void	error_msg(char *msg)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);	
}

void	errorhandler(t_data *game, char *msg, bool fatal)
{
	if (game)
	{
		free_data(game);
	}	
	if (msg)
	{
        error_msg(msg);
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
    int max;
    int i;
    
    max = arr[0];  // Assume the first element is the max initially
    i = 1;
    while (i < size)
    {
        if (arr[i] > max) 
        {
            max = arr[i];  // Update max if current element is greater
        }
        i++;
    }
    return max;
}
