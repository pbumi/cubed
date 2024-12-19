/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:47:50 by pbumidan          #+#    #+#             */
/*   Updated: 2024/12/19 14:50:00 by pbumidan         ###   ########.fr       */
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
    
    old_dirX = cub->pdir.x;
    cub->pdir.x = cub->pdir.x * cos(THETA) - cub->pdir.y * sin(THETA);
    cub->pdir.y = old_dirX * sin(THETA) + cub->pdir.y * cos(THETA);
    old_planeX = cub->pplane.x;
    cub->pplane.x = cub->pplane.x * cos(THETA) - cub->pplane.y * sin(THETA);
    cub->pplane.y = old_planeX * sin(THETA) + cub->pplane.y * cos(THETA);
}

void    left_key(t_main *cub)
{

    double  old_dirX;
    double  old_planeX;
    
    old_dirX = cub->pdir.x;
    cub->pdir.x = cub->pdir.x * cos(-THETA) - cub->pdir.y * sin(-THETA);
    cub->pdir.y = old_dirX * sin(-THETA) + cub->pdir.y * cos(-THETA);
    old_planeX = cub->pplane.x;
    cub->pplane.x = cub->pplane.x * cos(-THETA) - cub->pplane.y * sin(-THETA);
    cub->pplane.y = old_planeX * sin(-THETA) + cub->pplane.y * cos(-THETA);
}

void    move_up(t_main *cub)
{

   double x;
    double y;
    
    
    x = cub->ppos.x + cub->pdir.x * PLAYER_SPEED;
    y = cub->ppos.y + cub->pdir.y * PLAYER_SPEED;
    printf("press up\n");
    printf("Current position: (%f, %f)\n", cub->ppos.x, cub->ppos.y);
    printf("Next position: (%f, %f)\n", x, y);
    if (cub->sq_map[(int)(cub->ppos.y)][(int)(x)] == '0')
        cub->ppos.x = x;
    if (cub->sq_map[(int)(y)][(int)(cub->ppos.x)] == '0')
        cub->ppos.y = y;
    printf("New position: (%f, %f)\n", x, y);

}

void    move_down(t_main *cub)
{

   double x;
    double y;
    
    x = cub->ppos.x - cub->pdir.x * PLAYER_SPEED;
    y = cub->ppos.y - cub->pdir.y * PLAYER_SPEED;
    printf("press down\n");
    printf("Current position: (%f, %f)\n", cub->ppos.x, cub->ppos.y);
    printf("Next position: (%f, %f)\n", x, y);
    if (cub->sq_map[(int)(cub->ppos.y)][(int)(x)] == '0')
    {
        printf("XXX");
        cub->ppos.x = x;
    }
    if (cub->sq_map[(int)(y)][(int)(cub->ppos.x)] == '0')
    {
         printf("XXX");
        cub->ppos.y = y;
    }
    printf("New position: (%f, %f)\n", x, y);
}

void    move_left(t_main *cub)
{

    double x;
    double y;
    
    x = cub->ppos.x - cub->pplane.x * PLAYER_SPEED;
    y = cub->ppos.y - cub->pplane.y * PLAYER_SPEED;

    printf("press left\n");
    printf("Current position: (%f, %f)\n", cub->ppos.x, cub->ppos.y);
    printf("Next position: (%f, %f)\n", x, y);
    printf("Map value now: %c\n", cub->sq_map[(int)x][(int)cub->ppos.y]);
    if (cub->sq_map[(int)(cub->ppos.y)][(int)(x)] == '0')
        cub->ppos.x = x;
    if (cub->sq_map[(int)(y)][(int)(cub->ppos.x)] == '0')
        cub->ppos.y = y;
    printf("New position: (%f, %f)\n", x, y);
}

void    move_right(t_main *cub)
{
    double x;
    double y;
    
    
    x = cub->ppos.x + cub->pplane.x * PLAYER_SPEED;
    y = cub->ppos.y + cub->pplane.y * PLAYER_SPEED;
    printf("press right\n");
    printf("Current position: (%f, %f)\n", cub->ppos.x, cub->ppos.y);
    printf("Next position: (%f, %f)\n", x, y);
    if (cub->sq_map[(int)(cub->ppos.y)][(int)(x)] == '0')
        cub->ppos.x = x;
    if (cub->sq_map[(int)(y)][(int)(cub->ppos.x)] == '0')
        cub->ppos.y = y;
    printf("New position: (%f, %f)\n", x, y);
}

// void    right_key(t_main *cub)
// {
//     printf("right key pressed\n");
//     double  old_dirX;
//     double  old_planeX;
    
//     old_dirX = cub->dir.x;
//     cub->dir.x = cub->dir.x * cos(THETA)
//                             - cub->dir.y * sin(THETA);
//     cub->dir.y = old_dirX * sin(THETA) + cub->dir.y
//                             *cos(THETA);
//     old_planeX = cub->plane.x;
//     cub->plane.x = cub->plane.x * cos(THETA) 
//                             - cub->plane.y * sin(THETA);
//     cub->plane.y = old_planeX * sin(THETA) 
//                             + cub->plane.y * cos(THETA);
// }

// void    left_key(t_main *cub)
// {
//     printf("left key pressed\n");

//     double  old_dirX;
//     double  old_planeX;
    
//     old_dirX = cub->dir.x;
//     cub->dir.x = cub->dir.x * cos(-THETA)
//                             - cub->dir.y * sin(-THETA);
//     cub->dir.y = old_dirX * sin(-THETA) + cub->dir.y
//                             *cos(-THETA);
//     old_planeX = cub->plane.x;
//     cub->plane.x = cub->plane.x * cos(-THETA) 
//                             - cub->plane.y * sin(-THETA);
//     cub->plane.y = old_planeX * sin(-THETA) 
//                             + cub->plane.y * cos(-THETA);
// }

// void    move_up(t_main *cub)
// {
//     printf("w key pressed\n");

//     double next_x;
//     double next_y;
    
//     next_x = cub->p_x + cub->dir.x * PLAYER_SPEED;
//     next_y = cub->p_y + cub->dir.y * PLAYER_SPEED;
    
//     printf("Next position: (%f, %f)\n", next_x, next_y);
//     printf("Map value at next_x: %c\n", cub->sq_map[(int)next_x][(int)cub->p_y]);
//     printf("Map value at next_y: %c\n", cub->sq_map[(int)cub->p_x][(int)next_y]);

//     if (cub->sq_map[(int)(next_x)][(int)(cub->p_y)] == '0')
//         cub->p_x = next_x;
//     if (cub->sq_map[(int)(cub->p_x)][(int)(next_y)] == '0')
//         cub->p_y = next_y;

//     printf("Updated position: (%f, %f)\n", cub->p_x, cub->p_y);

// }

// void    move_down(t_main *cub)
// {
//     printf("s key pressed\n");

//     double prev_x;
//     double prev_y;
    
//     prev_x = cub->p_x - cub->dir.x * PLAYER_SPEED;
//     prev_y = cub->p_y - cub->dir.y * PLAYER_SPEED;
//     if (cub->sq_map[(int)(prev_x)][(int)(cub->p_y)] == '0')
//         cub->p_x = prev_x;
//     if (cub->sq_map[(int)(cub->p_x)][(int)(prev_y)] == '0')
//         cub->p_y = prev_y;
// }

// void    move_left(t_main *cub)
// {
//     printf("a key pressed\n");

//     double left_x;
//     double left_y;
    
//     left_x = cub->p_x - cub->plane.x * PLAYER_SPEED;
//     left_y = cub->p_y - cub->plane.y * PLAYER_SPEED;
//     if (cub->sq_map[(int)(left_x)][(int)(cub->p_y)] == '0')
//         cub->p_x = left_x;
//     if (cub->sq_map[(int)(cub->p_x)][(int)(left_y)] == '0')
//         cub->p_y = left_y;
// }

// void    move_right(t_main *cub)
// {
//     printf("d key pressed\n");

//     double right_x;
//     double right_y;
    
//     right_x = cub->p_x + cub->plane.x * PLAYER_SPEED;
//     right_y = cub->p_y + cub->plane.y * PLAYER_SPEED;
//     if (cub->sq_map[(int)(right_x)][(int)(cub->p_y)] == '0')
//         cub->p_x = right_x;
//     if (cub->sq_map[(int)(cub->p_x)][(int)(right_y)] == '0')
//         cub->p_y = right_y;
// }

void	key_hook_slow(void *param)
{
	t_main	*game;

	game = (t_main *)param;

    if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_ESCAPE))
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