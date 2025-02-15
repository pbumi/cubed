/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:39:06 by pbumidan          #+#    #+#             */
/*   Updated: 2025/02/15 19:30:33 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	ft_reles(mlx_key_data_t keydata, t_mlx *mlx)
{
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE))
		mlx->ply->east_west = 0;
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE))
		mlx->ply->east_west = 0;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_RELEASE))
		mlx->ply->north_south = 0;
	else if (keydata.key == MLX_KEY_W && (keydata.action == MLX_RELEASE))
		mlx->ply->north_south = 0;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		mlx->ply->right_left = 0;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		mlx->ply->right_left = 0;
}

void	key_hook(mlx_key_data_t keydata, void *ml)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)ml;
	if (keydata.key == MLX_KEY_ESCAPE
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		mlx_close_window(mlx->mlx_p);
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS))
		mlx->ply->east_west = -1;
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS))
		mlx->ply->east_west = 1;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS))
		mlx->ply->north_south = -1;
	else if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		mlx->ply->north_south = 1;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		mlx->ply->right_left = -1;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		mlx->ply->right_left = 1;
	ft_reles(keydata, mlx);
}
