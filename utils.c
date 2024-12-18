/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:25:27 by pbumidan          #+#    #+#             */
/*   Updated: 2024/12/18 18:35:45 by pbumidan         ###   ########.fr       */
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

void	errorhandler(t_main *game, char *msg, bool fatal)
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
    char **arr = (char**)malloc(y * sizeof(char*));
    if (arr == NULL)
	{
        return NULL;
    }
    int i = 0;
    while (i < y) 
	{
        arr[i] = (char*)malloc(x + 1 * sizeof(char));
        if (arr[i] == NULL) 
		{
            int j = 0;
            while (j < i) {
                free(arr[j]);
                j++;
            }
            free(arr);
            return NULL;
        }
        i++;
    }
    return arr;
}
