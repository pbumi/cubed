/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:16:51 by pbumidan          #+#    #+#             */
/*   Updated: 2024/12/17 17:55:11 by pbumidan         ###   ########.fr       */
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

void free_arr(char **arr)
{
    if (!arr)
        return;
    size_t x = 0;
    while (arr[x])
    {
        safe_free((void **)&arr[x]);  // Use safe_free for each element
        x++;
    }
    safe_free((void **)&arr);  // Free the array itself
}

void free_struct(t_main *game)
{
	if (game)
	{
		safe_free((void **)&game->walls->NO);
		safe_free((void **)&game->walls->SO);
		safe_free((void **)&game->walls->WE);
		safe_free((void **)&game->walls->EA);
		safe_free((void **)&game->walls);
		safe_free((void **)&game->floor);
		safe_free((void **)&game->ceil);
		safe_free((void **)&game->map);
		safe_free((void **)&game->wx_map);
		free_arr(game->map_arr);
		free_arr(game->sq_map);
	}
}

void free_and_close(char *line, int fd)
{
	free (line);
	line = get_next_line(-1);
	close(fd);
}