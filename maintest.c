/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 20:36:10 by pbumidan          #+#    #+#             */
/*   Updated: 2024/12/05 20:36:27 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cubed.h"

typedef struct s_vector
{
	double	x;
	double	y;
} t_vector;

int ft_putpixel(mlx_image_t *img, float x, float y, int color)
{

    // Check if the coordinates are within the bounds of the image
    if (x < 0 || y < 0 || x >= img->width || y >= img->height)
        return -1;

    //int alpha = 0xFF;  // Default to fully opaque
    // uint32_t pixel_color;
    // // Combine the color and alpha
    // pixel_color = (0xFF << 24) | (color & 0xFFFFFF);

    // Set the pixel at the given coordinates with the specified color and alpha
    mlx_put_pixel(img, (int)x, (int)y, color);
    
    return 0;
}

void draw_minimap_square(mlx_image_t *img, t_vector map_pt, size_t size, uint32_t color)
{
    for (size_t y = map_pt.y; y < map_pt.y + size; y++)
    {
        for (size_t x = map_pt.x; x < map_pt.x + size; x++)
        {
            ft_putpixel(img, x, y, color);  // Use ft_putpixel to set each pixel
        }
    }
}

// void draw_line(t_cub *cub, t_vector start, t_vector end, uint32_t color)
// {
//     int dx = fabs(end.x - start.x);
//     int dy = fabs(end.y - start.y);
//     int step_x = start.x < end.x ? 1 : -1;
//     int step_y = start.y < end.y ? 1 : -1;
//     int err = dx - dy;

//     while (true)
//     {
//         ft_putpixel(cub->mlx_img, start.x, start.y, color);
//         if (start.x == end.x && start.y == end.y)
//             break;
//         int e2 = err * 2;
//         if (e2 > -dy)
//         {
//             err -= dy;
//             start.x += step_x;
//         }
//         if (e2 < dx)
//         {
//             err += dx;
//             start.y += step_y;
//         }
//     }
// }

// void draw_player(t_main *game)
// {
//     int player_x;
//     int player_y; 
//     int ray_end_x;
//     int ray_end_y; 
	
// 	player_x = (int)(game->p_x * 15);
// 	player_y = (int)(game->p_y * 15);
//     draw_minimap_square(game, (t_vector){player_x - 10 / 2, \
// 										player_y - 10 / 2}, \
// 										10, 0x00ff2eff);
//     ray_end_x = player_x + (cub->player.dir.x * 10);
//     ray_end_y = player_y + (cub->player.dir.y * 10);
//     draw_line(cub, (t_vector){player_x, player_y}, (t_vector){ray_end_x, ray_end_y}, 0xFF0000ff);
// }

uint32_t set_minimap_color(t_main *game, t_vector *pt)
{
    uint32_t color;
    int x = pt->x;
    int y = pt->y;

	color = 0xFF000000; //space
    if (game->map_arr[y][x] == '1')
        color = 0xFFFFFFFF; //0xffc100ff;  // Wall 
    else if (game->map_arr[y][x] == '0')
        color = 0x0000FFFF; //0xd75000ff;  // Floor
    return color;
}

void draw_minimap(mlx_image_t *img, t_main *game)
{
    t_vector pt;
    t_vector map_pt;
    uint32_t color;
    
    // Loop through all the map points
    for (pt.y = 0; pt.y < game->h_map; pt.y++)
    {
        for (pt.x = 0; pt.x < game->w_map; pt.x++)
        {
            map_pt.y = pt.y * 15;  // Scale the y position
            map_pt.x = pt.x * 15;  // Scale the x position

            // Get the color for the current minimap point
            color = set_minimap_color(game, &pt);
            
            // Draw the square on the minimap
            draw_minimap_square(img, map_pt, 15, color);
        }
    }
}

//___________________________________________________________________

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
	return ;
}

static void ft_hook(void* param)
{
	t_main *game;

	game = (t_main *)param;
	draw_minimap(game->window, game);
}

void	key_hook_slow(mlx_key_data_t keydata, void *param)
{
	t_main	*game;

	game = (t_main *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		mlx_close_window(game->mlx_ptr);
}

void testchecker(t_main *game) //TESTER DELETE
{
	ft_putstr("WOW\n");
	printf("NO: %s\n", game->walls->NO);
	printf("SO: %s\n", game->walls->SO);
	printf("WE: %s\n", game->walls->WE);
	printf("EA: %s\n", game->walls->EA);
	printf("F: %d, %d, %d \n", game->floor->R, game->floor->G, game->floor->B);
	printf("C: %d, %d, %d \n", game->ceil->R, game->ceil->G, game->ceil->B);
	for (int i = 0; game->map_arr[i] != NULL; i++)
    {
        printf("%s\n", game->map_arr[i]);
    }
	printf("player x: %d y: %d \n", game->p_x, game->p_y);
}

int main(int argc, char **argv)
{
	t_main game;
	game = (t_main){0};
    ft_putstr("MAINTEST\n");
	check_file(argc, argv, &game);
	testchecker(&game);
	{
		// game.mlx_ptr = NULL;
		//mlx_set_setting(MLX_MAXIMIZED, true);
		game.mlx_ptr = mlx_init(WIDTH, HEIGHT, "CUB3D", true);
		if (!game.mlx_ptr)
		{
			errorhandler(&game, "mlxerror", true);
		}
		game.window = malloc(sizeof(mlx_image_t));
		if (!game.window)
		{
			errorhandler(&game, "window malloc error", true);
		}
		game.window = mlx_new_image(game.mlx_ptr, WIDTH, HEIGHT);
		if (!game.window)
		{
			errorhandler(&game, "image error", true);
		}
		initialize_grafics(&game);
		if (mlx_image_to_window(game.mlx_ptr, game.window, 0, 0) < 0)
		{
			errorhandler(&game, "image error", true);
		}
		mlx_key_hook(game.mlx_ptr, &key_hook_slow, &game);
		mlx_loop_hook(game.mlx_ptr, ft_hook, &game);
		mlx_loop(game.mlx_ptr);
		mlx_terminate(game.mlx_ptr);
	}
	free_struct(&game);
    return 0;
}
