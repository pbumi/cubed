/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:03:11 by pbumidan          #+#    #+#             */
/*   Updated: 2025/02/28 16:32:55 by pbumidan         ###   ########.fr       */
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

	map.x = 0;
	map.y = 0;
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
	t_flt_pt	h_ray;
	t_flt_pt	step;
	int			pixel;

	step.y = TILE_SIZE;
	step.x = TILE_SIZE / tan(angl);
	h_ray.y = (int)(mlx->ply->pos.y / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angl, &h_ray.y, &step.y, 1);
	h_ray.x = mlx->ply->pos.x + (h_ray.y - mlx->ply->pos.y) / tan(angl);
	if ((unit_circle(angl, 'y') && step.x > 0)
		|| (!unit_circle(angl, 'y') && step.x < 0))
		step.x *= -1;
	while (wall_hit(h_ray.x, h_ray.y - pixel, mlx))
	{
		h_ray.x += step.x;
		h_ray.y += step.y;
	}
	mlx->ray->horiz.x = h_ray.x;
	mlx->ray->horiz.y = h_ray.y;
	return (sqrt(pow(h_ray.x - mlx->ply->pos.x, 2) \
		+ pow(h_ray.y - mlx->ply->pos.y, 2)));
}

static float	get_v_inter(t_mlx *mlx, float angl)
{
	t_flt_pt	v_ray;
	t_flt_pt	step;
	int			pixel;

	step.x = TILE_SIZE;
	step.y = TILE_SIZE * tan(angl);
	v_ray.x = (int)(mlx->ply->pos.x / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angl, &v_ray.x, &step.x, 0);
	v_ray.y = mlx->ply->pos.y + (v_ray.x - mlx->ply->pos.x) * tan(angl);
	if ((unit_circle(angl, 'x') && step.y < 0)
		|| (!unit_circle(angl, 'x') && step.y > 0))
		step.y *= -1;
	while (wall_hit(v_ray.x - pixel, v_ray.y, mlx))
	{
		v_ray.x += step.x;
		v_ray.y += step.y;
	}
	mlx->ray->vert.x = v_ray.x;
	mlx->ray->vert.y = v_ray.y;
	return (sqrt(pow(v_ray.x - mlx->ply->pos.x, 2) \
		+ pow(v_ray.y - mlx->ply->pos.y, 2)));
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
		{
			mlx->ray->dist = v_inter;
		}
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
