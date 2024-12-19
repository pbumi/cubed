/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:47:50 by pbumidan          #+#    #+#             */
/*   Updated: 2024/12/19 16:00:56 by pbumidan         ###   ########.fr       */
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
void    rotate_right(t_main *game)
{
    double  old_dirX;
    double  old_planeX;
    
    old_dirX = game->pdir.x;
    game->pdir.x = game->pdir.x * cos(THETA) - game->pdir.y * sin(THETA);
    game->pdir.y = old_dirX * sin(THETA) + game->pdir.y * cos(THETA);
    old_planeX = game->pplane.x;
    game->pplane.x = game->pplane.x * cos(THETA) - game->pplane.y * sin(THETA);
    game->pplane.y = old_planeX * sin(THETA) + game->pplane.y * cos(THETA);
}

void    rotate_left(t_main *game)
{

    double  old_dirX;
    double  old_planeX;
    
    old_dirX = game->pdir.x;
    game->pdir.x = game->pdir.x * cos(-THETA) - game->pdir.y * sin(-THETA);
    game->pdir.y = old_dirX * sin(-THETA) + game->pdir.y * cos(-THETA);
    old_planeX = game->pplane.x;
    game->pplane.x = game->pplane.x * cos(-THETA) - game->pplane.y * sin(-THETA);
    game->pplane.y = old_planeX * sin(-THETA) + game->pplane.y * cos(-THETA);
}

void    move_up(t_main *game)
{

   double x;
    double y;
    
    
    x = game->ppos.x + game->pdir.x * PLAYER_SPEED;
    y = game->ppos.y + game->pdir.y * PLAYER_SPEED;

    if (game->sq_map[(int)(x)][(int)(game->ppos.y)] == '0')
        game->ppos.x = x;
    if (game->sq_map[(int)(game->ppos.x)][(int)(y)] == '0')
        game->ppos.y = y;
    printf("New position: (%f, %f)\n", x, y);

}

void    move_down(t_main *game)
{

   double x;
    double y;
    
    x = game->ppos.x - game->pdir.x * PLAYER_SPEED;
    y = game->ppos.y - game->pdir.y * PLAYER_SPEED;
    printf("press down\n");
    printf("Current position: (%f, %f)\n", game->ppos.x, game->ppos.y);
    printf("Next position: (%f, %f)\n", x, y);
    if (game->sq_map[(int)(x)][(int)(game->ppos.y)] == '0')
    {
        printf("XXX");
        game->ppos.x = x;
    }
    if (game->sq_map[(int)(game->ppos.x)][(int)(y)] == '0')
    {
         printf("XXX");
        game->ppos.y = y;
    }
    printf("New position: (%f, %f)\n", x, y);
}

void    move_left(t_main *game)
{

    double x;
    double y;
    
    x = game->ppos.x - game->pplane.x * PLAYER_SPEED;
    y = game->ppos.y - game->pplane.y * PLAYER_SPEED;

    printf("press left\n");
    printf("Current position: (%f, %f)\n", game->ppos.x, game->ppos.y);
    printf("Next position: (%f, %f)\n", x, y);
    printf("Map value now: %c\n", game->sq_map[(int)x][(int)game->ppos.y]);
    if (game->sq_map[(int)(x)][(int)(game->ppos.y)] == '0')
        game->ppos.x = x;
    if (game->sq_map[(int)(game->ppos.x)][(int)(y)] == '0')
        game->ppos.y = y;
    printf("New position: (%f, %f)\n", x, y);
}

void    move_right(t_main *game)
{
    double x;
    double y;
    
    x = game->ppos.x + game->pplane.x * PLAYER_SPEED;
    y = game->ppos.y + game->pplane.y * PLAYER_SPEED;
    printf("press right\n");
    printf("Current position: (%f, %f)\n", game->ppos.x, game->ppos.y);
    printf("Next position: (%f, %f)\n", x, y);
    if (game->sq_map[(int)(x)][(int)(game->ppos.y)] == '0')
        game->ppos.x = x;
    if (game->sq_map[(int)(game->ppos.x)][(int)(y)] == '0')
        game->ppos.y = y;
    printf("New position: (%f, %f)\n", x, y);
}

void	key_hook_slow(void *param)
{
	t_main	*game;
    
	game = (t_main *)param;
    if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx_ptr);
    else if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_RIGHT))
		rotate_right(game);
    else if (mlx_is_key_down(game->mlx_ptr,  MLX_KEY_LEFT))
		rotate_left(game);
	else if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_A))
		move_left(game);
	else if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_D))
		move_right(game);
	else if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_W))
		move_up(game);
	else if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_S))
		move_down(game);
}