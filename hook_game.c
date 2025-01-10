/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:37:12 by pbumidan          #+#    #+#             */
/*   Updated: 2025/01/10 19:51:04 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	move_player(t_mlx *mlx, double move_x, double move_y)
{
    t_int_pt map;
    t_int_pt new;

	new.y = (int)(mlx->ply->plyr_y + move_y);
	new.x = (int)(mlx->ply->plyr_x + move_x);
	map.y = (new.y / TILE_SIZE);
	map.x = (new.x / TILE_SIZE);
	if (mlx->dt->map2d[map.y][map.x] != '1' && \
		(mlx->dt->map2d[map.y][mlx->ply->plyr_x / TILE_SIZE] != '1' && \
		mlx->dt->map2d[mlx->ply->plyr_y / TILE_SIZE][map.x] != '1'))
	{
		mlx->ply->plyr_y = new.y;
		mlx->ply->plyr_x = new.x;
	}
}

static void	set_player(t_mlx *mlx)
{
	t_dbl_pt move;

	move = (t_dbl_pt){0.0, 0.0};
	if (mlx->ply->l_r == 1)
	{
		move.x = -sin(mlx->ply->angle) * PLAYER_SPEED;
		move.y = cos(mlx->ply->angle) * PLAYER_SPEED;
	}
	if (mlx->ply->l_r == -1)
	{
		move.x = sin(mlx->ply->angle) * PLAYER_SPEED;
		move.y = -cos(mlx->ply->angle) * PLAYER_SPEED;
	}
	if (mlx->ply->u_d == 1)
	{
		move.x = cos(mlx->ply->angle) * PLAYER_SPEED;
		move.y = sin(mlx->ply->angle) * PLAYER_SPEED;
	}
	if (mlx->ply->u_d == -1)
	{
		move.x = -cos(mlx->ply->angle) * PLAYER_SPEED;
		move.y = -sin(mlx->ply->angle) * PLAYER_SPEED;
	}
	move_player(mlx, move.x, move.y);
}

static void	rotate_player(t_mlx *mlx, int i)
{
	if (i == 1)
	{
		mlx->ply->angle += ROTATION_SPEED;
		if (mlx->ply->angle > (2 * M_PI))
			mlx->ply->angle -= (2 * M_PI);
	}
	else
	{
		mlx->ply->angle -= ROTATION_SPEED;
		if (mlx->ply->angle < 0)
			mlx->ply->angle += (2 * M_PI);
	}
}

static void set_angle(t_mlx *mlx)
{
	if (mlx->ply->rot == 1)
		rotate_player(mlx, 1);
	if (mlx->ply->rot == -1)
		rotate_player(mlx, 0);
}

void	game_hook(void *ml)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)ml;
	if (mlx->img)
		mlx_delete_image(mlx->mlx_p, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx_p, S_W, S_H);
	if(!mlx->img)
	{
		error_msg("* mlx image creation failed *");
		end_the_game(mlx, EXIT_FAILURE);
	}
	ft_memset(mlx->img->pixels, 255, mlx->img->width * mlx->img->height * sizeof(int32_t));
	set_angle(mlx);
	set_player(mlx);
	cast_rays(mlx);
	mlx_image_to_window(mlx->mlx_p, mlx->img, 0, 0);
}
