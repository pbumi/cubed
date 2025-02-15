/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:03:11 by pbumidan          #+#    #+#             */
/*   Updated: 2025/02/15 19:33:53 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static int	inter_check(float angle, float *inter, float *step, int is_horizon)
{
	if (is_horizon)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2))
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

static int	wall_hit(float x, float y, t_mlx *mlx)
{
	t_int_pt	map;

	map = (t_int_pt){0, 0};
	if (x < 0 || y < 0)
		return (0);
	map.y = (int)(y / TILE_SIZE);
	map.x = (int)(x / TILE_SIZE);
	if ((map.y >= mlx->dt->m.y || map.x >= mlx->dt->m.x))
		return (0);
	if (mlx->dt->map2d[map.y] && map.x <= mlx->dt->m.x)
	{
		if (mlx->dt->map2d[map.y][map.x] == '1')
			return (0);
	}
	return (1);
}

static float	get_h_inter(t_mlx *mlx, float angl)
{
	float	h_x;
	float	h_y;
	float	x_step;
	float	y_step;
	int		pixel;

	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(angl);
	h_y = (int)(mlx->ply->pos.y / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angl, &h_y, &y_step, 1);
	h_x = mlx->ply->pos.x + (h_y - mlx->ply->pos.y) / tan(angl);
	if ((unit_circle(angl, 'y') && x_step > 0)
		|| (!unit_circle(angl, 'y') && x_step < 0))
		x_step *= -1;
	while (wall_hit(h_x, h_y - pixel, mlx))
	{
		h_x += x_step;
		h_y += y_step;
	}
	mlx->ray->horiz.x = h_x;
	mlx->ray->horiz.y = h_y;
	return (sqrt(pow(h_x - mlx->ply->pos.x, 2) \
		+ pow(h_y - mlx->ply->pos.y, 2)));
}

static float	get_v_inter(t_mlx *mlx, float angl)
{
	float	v_x;
	float	v_y;
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = TILE_SIZE;
	y_step = TILE_SIZE * tan(angl);
	v_x = (int)(mlx->ply->pos.x / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angl, &v_x, &x_step, 0);
	v_y = mlx->ply->pos.y + (v_x - mlx->ply->pos.x) * tan(angl);
	if ((unit_circle(angl, 'x') && y_step < 0)
		|| (!unit_circle(angl, 'x') && y_step > 0))
		y_step *= -1;
	while (wall_hit(v_x - pixel, v_y, mlx))
	{
		v_x += x_step;
		v_y += y_step;
	}
	mlx->ray->vert.x = v_x;
	mlx->ray->vert.y = v_y;
	return (sqrt(pow(v_x - mlx->ply->pos.x, 2) \
		+ pow(v_y - mlx->ply->pos.y, 2)));
}

void	cast_rays(t_mlx *mlx)
{
	double	h_inter;
	double	v_inter;

	mlx->ray->index = 0;
	mlx->ray->r_angle = mlx->ply->angle - (mlx->ply->pov / 2);
	while (mlx->ray->index < S_W)
	{
		mlx->ray->wall_hit = false;
		h_inter = get_h_inter(mlx, nor_angle(mlx->ray->r_angle));
		v_inter = get_v_inter(mlx, nor_angle(mlx->ray->r_angle));
		if (v_inter <= h_inter)
			mlx->ray->dist = v_inter;
		else
		{
			mlx->ray->dist = h_inter;
			mlx->ray->wall_hit = true;
		}
		render_ray(mlx, mlx->ray->index);
		mlx->ray->index++;
		mlx->ray->r_angle += (mlx->ply->pov / S_W);
	}
}
