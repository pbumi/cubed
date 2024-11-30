/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 20:36:10 by pbumidan          #+#    #+#             */
/*   Updated: 2024/11/29 18:04:16 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cubed.h"

void	delete_textures(t_main *game)
{
	if (game->textu->NO)
		mlx_delete_texture(game->textu->NO);
	if (game->textu->EA)
		mlx_delete_texture(game->textu->EA);
	if (game->textu->SO)
		mlx_delete_texture(game->textu->SO);
	if (game->textu->WE)
		mlx_delete_texture(game->textu->WE);
}

void	image_fail(t_main *game)
{
	ft_putstr_fd("Error\n*  MLX42: fail to load texture *\n\n", 2);
	if (game->mlx_ptr)
		mlx_terminate(game->mlx_ptr);
	delete_textures(game);
	if (game->imag)
		free(game->imag);
	if (game->textu)
		free(game->textu);
	free_struct(game);
	exit(1);
}

void	load_images(t_main *game)
{
	game->imag = ft_calloc(1, sizeof(t_images));
	if (!game->imag)
		errorhandler(game, "mallocfail", true);
	game->imag->NO = mlx_texture_to_image(game->mlx_ptr, game->textu->NO);
	if (!game->imag->NO)
		image_fail(game);
	game->imag->EA = mlx_texture_to_image(game->mlx_ptr, game->textu->EA);
	if (!game->imag->EA)
		image_fail(game);
	game->imag->SO = mlx_texture_to_image(game->mlx_ptr, game->textu->SO);
	if (!game->imag->SO)
		image_fail(game);
	game->imag->WE = mlx_texture_to_image(game->mlx_ptr, game->textu->WE);
	if (!game->imag->WE)
		image_fail(game);
}


void	texture_fail(t_main *game)
{
	ft_putstr_fd("Error\n*  MLX42: fail to load texture *\n\n", 2);
	if (game->mlx_ptr)
		mlx_terminate(game->mlx_ptr);
	delete_textures(game);
	if (game->imag)
		free(game->imag);
	if (game->textu)
		free(game->textu);
	free_struct(game);
	exit(1);
}

void	load_textures(t_main *game)
{
	game->textu = ft_calloc(1, sizeof(t_textures));
	if (!game->textu)
		errorhandler(game, "malloc fail", true);
	game->textu->NO = mlx_load_png(game->walls->NO);
	if (!game->textu->NO)
		texture_fail(game);
	game->textu->EA = mlx_load_png(game->walls->EA);
	if (!game->textu->EA)
		texture_fail(game);
	game->textu->SO = mlx_load_png(game->walls->SO);
	if (!game->textu->SO)
		texture_fail(game);
	game->textu->WE = mlx_load_png(game->walls->WE);
	if (!game->textu->WE)
		texture_fail(game);
}
void	initialize_grafics(t_main *game)
{
	load_textures(game);
	load_images(game);
	delete_textures(game);
	//resize_images(game);
	return ;
}
// static void ft_hook(void* param)
// {
// 	t_main *game;

// 	game = (t_main *)param;

// 	printf("WIDTH: %d | HEIGHT: %d\n", game->mlx_ptr->width, game->mlx_ptr->height);
// }

// int main() {
//     mlx_t *mlx_ptr = mlx_init(800, 600, "Test Window", false);
//     if (!mlx_ptr) {
//         printf("mlx_init failed\n");
//         return 1;
//     }
//     mlx_terminate(mlx_ptr);
//     return 0;
// }

int main(int argc, char **argv)
{
	t_main game;
	game = (t_main){0};
	check_file(argc, argv, &game);
	{
		// // game.mlx_ptr = NULL;
		// // mlx_set_setting(MLX_MAXIMIZED, true);
		// game.mlx_ptr = mlx_init(WIDTH, HEIGHT, "42Balls", false);
		// if (!game.mlx_ptr)
		// {
		// 	errorhandler(&game, "mlxerror", true);
		// }
		// // game.window = malloc(sizeof(mlx_image_t));
		// // if (!game.window)
		// // {
		// // 	errorhandler(&game, "window malloc error", true);
		// // }
		// // game.window = mlx_new_image(game.mlx_ptr, WIDTH, HEIGHT);
		// // if (!game.window)
		// // {
		// // 	errorhandler(&game, "image error", true);
		// // }
		// initialize_grafics(&game);
		// // if (mlx_image_to_window(game.mlx_ptr, game.imag->NO, HEIGHT, WIDTH) < 0)
		// // {
		// // 	errorhandler(&game, "image error", true);
		// // }
		// mlx_loop_hook(game.mlx_ptr, ft_hook, &game);
		// mlx_loop(game.mlx_ptr);
		// mlx_terminate(game.mlx_ptr);
		ft_putstr("WOW\n");
		ft_putstr(game.walls->NO);
		ft_putstr("\n");
		ft_putstr(game.walls->SO);
		ft_putstr("\n");
		ft_putstr(game.walls->WE);
		ft_putstr("\n");
		ft_putstr(game.walls->EA);
		ft_putstr("\n");
		printf("F: %d, %d, %d \n", game.floor->R, game.floor->G, game.floor->B);
		printf("C: %d, %d, %d \n", game.ceil->R, game.ceil->G, game.ceil->B);
		for (int i = 0; game.map_arr[i] != NULL; i++)
    	{
        printf("%s\n", game.map_arr[i]);
    	}
		printf("player x: %d y: %d \n", game.p_x, game.p_y);
		free_struct(&game);
	}
    return 0;
}
