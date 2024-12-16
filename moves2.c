/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:47:50 by pbumidan          #+#    #+#             */
/*   Updated: 2024/12/16 15:51:12 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

# define THETA 0.045 // angle theta in radians about 3 deg.

/* this uses the 2D rotation formula
x′= x⋅cos(θ)−y⋅sin(θ)
y′= x⋅sin(θ)+y⋅cos(θ)
where θ is in radians, 
degrees = rad x (180/pi)
THETA 0.045 rads about 3 deg
*/
void    right_key(t_main *cub)
{
    double  old_dirX;
    double  old_planeX;
    
    old_dirX = cub->dir.x;
    cub->dir.x = cub->dir.x * cos(THETA) - cub->dir.y * sin(THETA);
    cub->dir.y = old_dirX * sin(THETA) + cub->dir.y * cos(THETA);
    old_planeX = cub->plane.x;
    cub->plane.x = cub->plane.x * cos(THETA) - cub->plane.y * sin(THETA);
    cub->plane.y = old_planeX * sin(THETA) + cub->plane.y * cos(THETA);
}

void    left_key(t_main *cub)
{

    double  old_dirX;
    double  old_planeX;
    
    old_dirX = cub->dir.x;
    cub->dir.x = cub->dir.x * cos(-THETA) - cub->dir.y * sin(-THETA);
    cub->dir.y = old_dirX * sin(-THETA) + cub->dir.y * cos(-THETA);
    old_planeX = cub->plane.x;
    cub->plane.x = cub->plane.x * cos(-THETA) - cub->plane.y * sin(-THETA);
    cub->plane.y = old_planeX * sin(-THETA) + cub->plane.y * cos(-THETA);
}

void    move_up(t_main *cub)
{

    double next_x;
    double next_y;
    
    next_x = cub->p_x + cub->dir.x * PLAYER_SPEED;
    next_y = cub->p_y + cub->dir.y * PLAYER_SPEED;
    if (cub->map_arr[(int)(next_x)][(int)(cub->p_y)] == '0')
        cub->p_x = next_x;
    if (cub->map_arr[(int)(cub->p_x)][(int)(next_y)] == '0')
        cub->p_y = next_y;

}

void    move_down(t_main *cub)
{

    double prev_x;
    double prev_y;
    
    prev_x = cub->p_x - cub->dir.x * PLAYER_SPEED;
    prev_y = cub->p_y - cub->dir.y * PLAYER_SPEED;
    if (cub->map_arr[(int)(prev_x)][(int)(cub->p_y)] == '0')
        cub->p_x = prev_x;
    if (cub->map_arr[(int)(cub->p_x)][(int)(prev_y)] == '0')
        cub->p_y = prev_y;
}

void    move_left(t_main *cub)
{

    double left_x;
    double left_y;
    
    left_x = cub->p_x - cub->plane.x * PLAYER_SPEED;
    left_y = cub->p_y - cub->plane.y * PLAYER_SPEED;
    if (cub->map_arr[(int)(left_x)][(int)(cub->p_y)] == '0')
        cub->p_x = left_x;
    if (cub->map_arr[(int)(cub->p_x)][(int)(left_y)] == '0')
        cub->p_y = left_y;
}

void    move_right(t_main *cub)
{
    double right_x;
    double right_y;
    
    right_x = cub->p_x + cub->plane.x * PLAYER_SPEED;
    right_y = cub->p_y + cub->plane.y * PLAYER_SPEED;
    if (cub->map_arr[(int)(right_x)][(int)(cub->p_y)] == '0')
        cub->p_x = right_x;
    if (cub->map_arr[(int)(cub->p_x)][(int)(right_y)] == '0')
        cub->p_y = right_y;
}


void	key_hook_slow(mlx_key_data_t keydata, void *param)
{
	t_main	*game;

	game = (t_main *)param;

	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		mlx_close_window(game->mlx_ptr);
	else if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_A))
		move_left(game);
	else if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_D))
		move_right(game);
	else if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_W))
		move_up(game);
	else if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_S))
		move_down(game);
}