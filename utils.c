/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:16:51 by pbumidan          #+#    #+#             */
/*   Updated: 2025/01/10 19:56:48 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cubed.h"

float	nor_angle(float angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

char *remove_wspace(char *line, int start)
{
    char *substr = NULL;
    int x = start;
    int end;

    while (line[x] && (line[x] == ' ' || (line[x] >= 9 && line[x] <= 13)))
    {
        x++;
    }
    end = ft_strlen(line) - 1;
    while (end > x && (line[end] == ' ' || (line[end] >= 9 && line[end] <= 13)))
    {
        end--;
    }
    substr = ft_substr(line, x, (end - x) + 1);
    if (!substr)
    {
        return NULL;
    }
    return substr;
}

void free_arr(char **arr)
{
    if (arr == NULL)
        return;
    int i = 0;
    while (arr[i] != NULL)
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

void	free_all(t_mlx *mlx)
{
    free(mlx->dt->map);
    mlx->dt->map = NULL;
	free_arr(mlx->dt->map2d);
    mlx->dt->map2d = NULL;
    if (mlx->dt->ea_t)
		mlx_delete_texture(mlx->dt->ea_t);
    if (mlx->dt->we_t)
        mlx_delete_texture(mlx->dt->we_t);
    if (mlx->dt->no_t)
        mlx_delete_texture(mlx->dt->no_t);
    if (mlx->dt->so_t)
        mlx_delete_texture(mlx->dt->so_t);
    mlx->dt->no_t = NULL;
    mlx->dt->so_t = NULL;
    mlx->dt->we_t = NULL;
    mlx->dt->ea_t = NULL;
	if (mlx->ply)
		free(mlx->ply);
	if (mlx->ray)
		free(mlx->ray);
	mlx->dt = NULL;
	mlx->ply = NULL;
	mlx->ray = NULL;
}

void	error_msg(char *msg)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);	
}
