/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 20:36:10 by pbumidan          #+#    #+#             */
/*   Updated: 2024/12/19 14:29:15 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cubed.h"

// int ft_put_pixel(mlx_image_t *img, double x, double y, unsigned int color)
// {

//     // Check if the coordinates are within the bounds of the image
//     if (x < 0 || y < 0 || x >= img->width || y >= img->height)
//         return -1;

//     // Set the pixel at the given coordinates with the specified color and alpha
//     mlx_put_pixel(img, x, y, color);
    
//     return 0;
// }

void draw_minimap_square(mlx_image_t *img, t_int_pt *map_pt, size_t size, size_t color)
{
    int y;
	y = map_pt->y;
    while (y < map_pt->y + size)
    {
        int x;
		x = map_pt->x;
        while (x < map_pt->x + size)
        {
            mlx_put_pixel(img, x, y, color);  // Use ft_putpixel to set each pixel
            x++;
        }
        y++;
    }
}

void draw_player_square(mlx_image_t *img, int px, int py, size_t color)
{
    int y;
	y = py;
    while (y < py + PLAYER_TILE)
    {
        int x;
		x = px;
        while (x < px + PLAYER_TILE)
        {
            mlx_put_pixel(img, x, y, color);  // Use ft_putpixel to set each pixel
            x++;
        }
        y++;
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

void draw_player(t_main *game, mlx_image_t *img)
{
	t_dbl_pt player;
    // int player_x;
    // int player_y; 
    // int ray_end_x;
    // int ray_end_y; 
	
	player.x = (int)(game->p_x * MINI_TILE);
	player.y = (int)(game->p_y * MINI_TILE);
	draw_player_square(img, player.x - PLAYER_TILE / 2, player.y - PLAYER_TILE / 2, 0x00ff2eff);

    // ray_end_x = player_x + (cub->player.dir.x * 10);
    // ray_end_y = player_y + (cub->player.dir.y * 10);
    // draw_line(cub, (t_vector){player_x, player_y}, (t_vector){ray_end_x, ray_end_y}, RED);
}
// void draw_player(t_main *game)
// {
// 	t_pt player;
//     // int player_x;
//     // int player_y; 
//     // int ray_end_x;
//     // int ray_end_y; 
	
// 	player.x = (int)(game->p_x * 4);
// 	player.y = (int)(game->p_y * 4);
//     draw_minimap_square(game->minimap, &player, MINI_TILE, 0x00ff2eff);
//     // ray_end_x = player_x + (cub->player.dir.x * 10);
//     // ray_end_y = player_y + (cub->player.dir.y * 10);
//     // draw_line(cub, (t_vector){player_x, player_y}, (t_vector){ray_end_x, ray_end_y}, 0xFF0000ff);
// }

uint32_t set_minimap_color(t_main *game, t_int_pt *pt)
{
    size_t color;
    int x = pt->x;
    int y = pt->y;

	color = 0x00000000; //space
    if (game->sq_map[y][x] == '1')
        color = 0xFFFFFFFF ; //0xffc100ff;  // Wall
    else if (game->sq_map[y][x] == '0' || game->sq_map[y][x] == 'N' \
		|| game->sq_map[y][x] == 'S' || game->sq_map[y][x] == 'E' \
		|| game->sq_map[y][x] == 'W')
        color = 0x0000FFFF; //0xd75000ff;  // Floor
    return color;
}

void draw_minimap(t_main *game, mlx_image_t *minimap)
{
    t_int_pt pt;
    t_int_pt map_pt;
    size_t color;

    pt.y = 0;
    while (pt.y < game->h_map)
    {
        pt.x = 0;
        while (pt.x < game->w_map)
        {
            map_pt.y = pt.y * MINI_TILE;
            map_pt.x = pt.x * MINI_TILE;
            color = set_minimap_color(game, &pt);  // Get the color for the current minimap point
            draw_minimap_square(minimap, &map_pt, MINI_TILE, color); // Draw the square on the minimap
            pt.x++;
        }
        pt.y++;
    }
}
//___________________________________________________________________

// void	delete_textures(t_main *game)
// {
// 	if (game->textu->NO)
// 		mlx_delete_texture(game->textu->NO);
// 	if (game->textu->EA)
// 		mlx_delete_texture(game->textu->EA);
// 	if (game->textu->SO)
// 		mlx_delete_texture(game->textu->SO);
// 	if (game->textu->WE)
// 		mlx_delete_texture(game->textu->WE);
// }

// void	image_fail(t_main *game)
// {
// 	ft_putstr_fd("Error\n*  MLX42: fail to load texture *\n\n", 2);
// 	if (game->mlx_ptr)
// 		mlx_terminate(game->mlx_ptr);
// 	delete_textures(game);
// 	if (game->imag)
// 		free(game->imag);
// 	if (game->textu)
// 		free(game->textu);
// 	free_struct(game);
// 	exit(1);
// }

// void	load_images(t_main *game)
// {
// 	game->imag = ft_calloc(1, sizeof(t_images));
// 	if (!game->imag)
// 		errorhandler(game, "mallocfail", true);
// 	game->imag->NO = mlx_texture_to_image(game->mlx_ptr, game->textu->NO);
// 	if (!game->imag->NO)
// 		image_fail(game);
// 	game->imag->EA = mlx_texture_to_image(game->mlx_ptr, game->textu->EA);
// 	if (!game->imag->EA)
// 		image_fail(game);
// 	game->imag->SO = mlx_texture_to_image(game->mlx_ptr, game->textu->SO);
// 	if (!game->imag->SO)
// 		image_fail(game);
// 	game->imag->WE = mlx_texture_to_image(game->mlx_ptr, game->textu->WE);
// 	if (!game->imag->WE)
// 		image_fail(game);
// }


// void	texture_fail(t_main *game)
// {
// 	ft_putstr_fd("Error\n*  MLX42: fail to load texture *\n\n", 2);
// 	if (game->mlx_ptr)
// 		mlx_terminate(game->mlx_ptr);
// 	delete_textures(game);
// 	if (game->imag)
// 		free(game->imag);
// 	if (game->textu)
// 		free(game->textu);
// 	free_struct(game);
// 	exit(1);
// }

// void	load_textures(t_main *game)
// {
// 	game->textu = ft_calloc(1, sizeof(t_textures));
// 	if (!game->textu)
// 		errorhandler(game, "malloc fail", true);
// 	game->textu->NO = mlx_load_png(game->walls->NO);
// 	if (!game->textu->NO)
// 		texture_fail(game);
// 	game->textu->EA = mlx_load_png(game->walls->EA);
// 	if (!game->textu->EA)
// 		texture_fail(game);
// 	game->textu->SO = mlx_load_png(game->walls->SO);
// 	if (!game->textu->SO)
// 		texture_fail(game);
// 	game->textu->WE = mlx_load_png(game->walls->WE);
// 	if (!game->textu->WE)
// 		texture_fail(game);
// }
// void	initialize_grafics(t_main *game)
// {
// 	load_textures(game);
// 	load_images(game);
// 	delete_textures(game);
// 	return ;
// }

static void gamehook(void* param)
{
	t_main *game;

	game = (t_main *)param;
	draw_minimap(game, game->minimap);
	draw_player(game, game->minimap);
}

// void	key_hook_slow(mlx_key_data_t keydata, void *param)
// {
// 	t_main	*game;

// 	game = (t_main *)param;
// 	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
// 		mlx_close_window(game->mlx_ptr);
// 	else if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_A))
// 		move_left(game);
// 	else if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_D))
// 		move_right(game);
// 	else if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_W))
// 		move_up(game);
// 	else if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_S))
// 		move_down(game);
// }

void testchecker(t_main *game) //TESTER DELETE
{
	printf("NO: %s\n", game->walls->NO);
	printf("SO: %s\n", game->walls->SO);
	printf("WE: %s\n", game->walls->WE);
	printf("EA: %s\n", game->walls->EA);
	printf("F: %d, %d, %d \n", game->floor->R, game->floor->G, game->floor->B);
	printf("C: %d, %d, %d \n", game->ceil->R, game->ceil->G, game->ceil->B);
	printf("sqmap\n");
	for (int i = 0; game->sq_map[i] != NULL; i++)
    {
        printf("%s\n", game->sq_map[i]);
    }
	printf("\n player x: %f y: %f \n", game->p_x, game->p_y);
	printf("\n plane x: %f y: %f \n", game->plane.x, game->plane.y);
	printf("\n dir x: %f y: %f \n", game->dir.x, game->dir.y);
	
}

int find_max(int *arr, int size)
{
    int max = arr[0];  // Assume the first element is the max initially

    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];  // Update max if current element is greater
        }
    }
    return max;
}

void end_game(t_main *game)
{
    mlx_delete_image(game->mlx_ptr, game->minimap);
	mlx_terminate(game->mlx_ptr);
    free_struct(game);
}

void start_game(t_main *game)
{
	//initialize_grafics(&game);
	game->mlx_ptr = mlx_init(WIDTH, HEIGHT, "CUB3D", true);
	if (!game->mlx_ptr)
	{			
        errorhandler(game, "mlxerror", true);
	}
	game->minimap = mlx_new_image(game->mlx_ptr, game->w_map * MINI_TILE, game->h_map * MINI_TILE);
	if (!game->minimap)
	{
		errorhandler(game, "image error", true);
	}
	if (mlx_image_to_window(game->mlx_ptr, game->minimap, 0, 0) < 0)
	{
		errorhandler(game, "image error", true);
	}
	mlx_loop_hook(game->mlx_ptr, &key_hook_slow, game);
	mlx_loop_hook(game->mlx_ptr, &gamehook, game);
	mlx_loop(game->mlx_ptr);
}

int main(int argc, char **argv)
{
	t_main game;
	game = (t_main){0};
	check_file(argc, argv, &game);
	testchecker(&game);
    start_game(&game);
    end_game(&game);
}
