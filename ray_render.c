/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:30:03 by pbumidan          #+#    #+#             */
/*   Updated: 2025/02/15 19:33:53 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	draw_floor_ceiling(t_mlx *mlx, int ray, int t_pix, int b_pix)
{
	int		i;

	i = b_pix;
	while (i < S_H)
	{
		mlx_put_pixel(mlx->img, ray, i, mlx->dt->floor_color);
		i++;
	}
	i = 0;
	while (i < t_pix)
	{
		mlx_put_pixel(mlx->img, ray, i, mlx->dt->ceil_color);
		i++;
	}
}

static mlx_texture_t	*get_texture(t_mlx *mlx)
{
	mlx->ray->r_angle = nor_angle(mlx->ray->r_angle);
	if (mlx->ray->wall_hit == false)
	{
		if (mlx->ray->r_angle > M_PI / 2 && mlx->ray->r_angle < 3 * (M_PI / 2))
			return (mlx->dt->we_t);
		else
			return (mlx->dt->ea_t);
	}
	else
	{
		if (mlx->ray->r_angle > 0 && mlx->ray->r_angle < M_PI)
			return (mlx->dt->no_t);
		else
			return (mlx->dt->so_t);
	}
}

static double	set_pixeldata(mlx_texture_t *texture, t_mlx *mlx)
{
	double	pixel;

	if (mlx->ray->wall_hit == true)
		pixel = (int)(mlx->ray->horiz.x * (texture->width / TILE_SIZE))
			% texture->width;
	else
		pixel = (int)(mlx->ray->vert.y * (texture->width / TILE_SIZE))
			% texture->width;
	return (pixel);
}

static void	draw_wall(t_mlx *mlx, int t_pix, int b_pix, double wall_h)
{
	t_dbl_pt		pix;
	mlx_texture_t	*texture;
	uint32_t		*arr;
	double			factor;

	pix = (t_dbl_pt){0.0, 0.0};
	texture = get_texture(mlx);
	arr = (uint32_t *)texture->pixels;
	factor = (double)texture->height / wall_h;
	pix.x = set_pixeldata(texture, mlx);
	pix.y = (t_pix - (S_H / 2) + (wall_h / 2)) * factor;
	if (pix.y < 0)
		pix.y = 0;
	while (t_pix < b_pix)
	{
		if (t_pix >= 0 && t_pix < S_H)
		{
			mlx_put_pixel(mlx->img, mlx->ray->index, t_pix, \
			get_pixeldata(arr[(int)pix.y * texture->width + (int)pix.x]));
		}
		pix.y += factor;
		t_pix++;
	}
}

void	render_ray(t_mlx *mlx, int ray)
{
	double	wall_h;
	double	b_pix;
	double	t_pix;

	mlx->ray->dist *= cos(nor_angle(mlx->ray->r_angle - mlx->ply->angle));
	wall_h = (TILE_SIZE / mlx->ray->dist) \
		* ((S_W / 2) / tan(mlx->ply->pov / 2));
	b_pix = (S_H / 2) + (wall_h / 2);
	t_pix = (S_H / 2) - (wall_h / 2);
	if (b_pix > S_H)
		b_pix = S_H;
	if (t_pix < 0)
		t_pix = 0;
	mlx->ray->index = ray;
	draw_wall(mlx, t_pix, b_pix, wall_h);
	draw_floor_ceiling(mlx, ray, t_pix, b_pix);
}
