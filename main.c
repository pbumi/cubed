/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:51:37 by pbumidan          #+#    #+#             */
/*   Updated: 2025/01/10 20:33:53 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cubed.h"

static void init_the_player(t_mlx *mlx)
{
	mlx->ply->pos.x = mlx->dt->p.x * TILE_SIZE + TILE_SIZE / 2;
	mlx->ply->pos.y = mlx->dt->p.y * TILE_SIZE + TILE_SIZE / 2;
	mlx->ply->fov_rd = (FOV * M_PI) / 180;
	if (mlx->dt->map2d[mlx->dt->p.y][mlx->dt->p.x] == 'N')
    {
        mlx->ply->angle = 3 * M_PI / 2;
    }
    else if (mlx->dt->map2d[mlx->dt->p.y][mlx->dt->p.x] == 'S')
    {
        mlx->ply->angle = M_PI / 2;
    }
    else if (mlx->dt->map2d[mlx->dt->p.y][mlx->dt->p.x] == 'W')
    {
        mlx->ply->angle = M_PI;
    }
    else if (mlx->dt->map2d[mlx->dt->p.y][mlx->dt->p.x] == 'E')
    {
        mlx->ply->angle = 0;
    } 
}

static bool	initialize_mlx_struct(t_mlx *mlx, t_data *dt)
{
	mlx->dt = dt;
	mlx->ply = ft_calloc(1, sizeof(t_player));	
	if (!mlx->ply)
	{
		error_msg("* mlx_ply initilization failed *");
		return (false);
	}
	mlx->ray = ft_calloc(1, sizeof(t_ray));
	if (!mlx->ray)
	{
		error_msg("* mlx_ray initilization failed *");
		return (false);
	}
	init_the_player(mlx);
	return(true);
}

void 	end_the_game(t_mlx *mlx, int exit_code)
{
	if (mlx->img)
		mlx_delete_image(mlx->mlx_p, mlx->img);
	free_all(mlx);
	mlx_terminate(mlx->mlx_p);
	if (exit_code == EXIT_SUCCESS)
	{
		ft_putendl_fd("GAME OVER!", STDOUT_FILENO);
		exit(exit_code);
	}
	else
		exit(exit_code);
}

static void	start_the_game(t_mlx *mlx)
{
	mlx->mlx_p = mlx_init(S_W, S_H, "Cub3D", 0);
	if (!mlx->mlx_p)
    {
		error_msg("* mlx initilization failed *");
		end_the_game(mlx, EXIT_FAILURE);
	}
	mlx_key_hook(mlx->mlx_p, &key_hook, mlx);
	mlx_loop_hook(mlx->mlx_p, &game_hook, mlx);
	mlx_loop(mlx->mlx_p);
}

int main(int argc, char **argv)
{
    t_data dt;
	t_mlx	mlx;

	dt = (t_data){0};
	if (check_args(argc, argv, &dt) == false)
		return (EXIT_FAILURE);
	mlx = (t_mlx){0};
	if (initialize_mlx_struct(&mlx, &dt) == false)
		end_the_game(&mlx, EXIT_FAILURE);
	start_the_game(&mlx);
	end_the_game(&mlx, EXIT_SUCCESS);
	return(0);
}

