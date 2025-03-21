/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 19:16:49 by pbumidan          #+#    #+#             */
/*   Updated: 2025/03/11 16:45:59 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	free_arr(char **arr)
{
	int	i;

	if (arr == NULL)
		return ;
	i = 0;
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

int	x_isdigit(char c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}

long	ft_atol(char *str)
{
	long		nb;
	int			i;

	nb = 0;
	i = 0;
	while (str[i] == ' ')
		i++;
	while (x_isdigit(str[i]))
	{
		nb = (nb * 10) + (str[i] - '0');
		i++;
	}
	return (nb);
}
