/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:24:57 by pbumidan          #+#    #+#             */
/*   Updated: 2025/01/10 19:52:41 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void fill_maparray(t_data *game, int *tmp_wx, char **tmp_arr)
{
	t_int_pt pt;
    
	pt.y = 0;
	while(pt.y < game->m.y)
	{
		pt.x = 0;
		while (pt.x < game->m.x)
		{
			if (pt.x < tmp_wx[pt.y])
			{
				game->map2d[pt.y][pt.x] = tmp_arr[pt.y][pt.x];
			}
			else
			{
				game->map2d[pt.y][pt.x] = ' ';
			}
			pt.x++;
		}
		game->map2d[pt.y][pt.x] = '\0';
		pt.y++;
	}
	game->map2d[game->m.y] = NULL;
}

sttaic void get_width(t_data *game, char **tmp_arr, int *tmp_wx)
{
	int max;
    int x;
    int i;

    x = 0;
    while (x < game->m.y)
    {
        tmp_wx[x] = ft_strlen(tmp_arr[x]);
        x++;
    }
    max = tmp_wx[0];
    i = 1;
    while (i < game->m.y)
    {
        if (tmp_wx[i] > max) 
        {
            max = tmp_wx[i];
        }
        i++;
    }
    game->m.x = max;
}

static void get_height(t_data *game, char **tmp_arr)
{
	int y;
	y = 0;
	while (tmp_arr[y] != NULL)
    {
        y++;
    }
    game->m.y = y;
}

static char    **AllocateArray(int y, int x)
{
    char **arr;
    t_int_pt pt;
    
    pt.x = 0;
    arr = ft_calloc(y + 1, sizeof(char *));
    if (arr == NULL)
        return NULL;
    while (pt.x < y)
    {
        arr[pt.x] = ft_calloc(x + 1, sizeof(char));
        if (arr[pt.x] == NULL)
        {
            pt.y = 0;
            while (pt.y < pt.x)
            {
                free(arr[pt.y]);
                pt.y++;
            }
            free(arr);
            return NULL;
        }
        pt.x++;
    }
    return (arr);
}

bool create_sqmap(t_data *game)
{
    char **tmp_arr;
    int *tmp_wx;
    
    tmp_arr = ft_split(game->map, '\n');
    if (!tmp_arr) 
        return false;
    get_height(game, tmp_arr);
    tmp_wx = ft_calloc(game->m.y, sizeof(int));
    if (tmp_wx == NULL)
    {
        free_arr(tmp_arr);
        return false;  
    }
    get_width(game, tmp_arr, tmp_wx);
    game->map2d = AllocateArray(game->m.y, game->m.x);
    if (!game->map2d)
    {
        free_arr(tmp_arr);
        free(tmp_wx);
        return false;
    }
    fill_maparray(game, tmp_wx, tmp_arr);
    free_arr(tmp_arr);
    free(tmp_wx);
    return true;
}
