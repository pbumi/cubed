/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:16:51 by pbumidan          #+#    #+#             */
/*   Updated: 2025/01/02 17:38:20 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cubed.h"

void safe_free(void **ptr)
{
    if (*ptr)
    {
        free(*ptr);
        *ptr = NULL;
    }
}

void safe_free_arr(char **arr)
{
    if (arr == NULL) // Check if the array is NULL to avoid dereferencing a NULL pointer
        return;
    
    int i = 0;
    while (arr[i] != NULL) // Loop through the array of strings
    {
        safe_free((void **)&arr[i]); // Use safe_free for each element to safely free it
        i++;
    }
    safe_free((void **)&arr); // Free the array itself (pointer to the array) safely
}

void free_arr(char **arr)
{
    if (arr == NULL) // Check if the array is NULL to avoid dereferencing a NULL pointer
        return;
    int i = 0;
    while (arr[i] != NULL)   // Loop through the array of strings
    {
        free(arr[i]);         // Free each string (element) in the array
        i++;
    }
    free(arr);                 // Free the array itself (pointer to the array)
}



void free_struct(t_data *game)
{
	if (game)
	{
		free(game->NO);
		free(game->SO);
		free(game->WE);
		free(game->EA);
		free(game->map);
		free_arr(game->map2d);
        game->NO = NULL;
        game->SO = NULL;
        game->WE = NULL;
        game->EA = NULL;
        game->map = NULL;
        game->map2d = NULL;
	}
}

void free_and_close(char *line, int fd)
{
    if (line)
    {
        free(line);
        line = NULL;
    }
    if (fd >= 0)
        close(fd);
}