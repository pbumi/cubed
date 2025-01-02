
# include "cubed.h"
# include <math.h>



//##############################################################################//
//############################## THE EXITING CODE ##############################//
//##############################################################################//

// void	ft_exit(t_mlx *mlx) 		// exit the game
// {
// 	int	i = 0;
// 	printf("QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ\n");
// 	mlx_delete_image(mlx->mlx_p, mlx->img); // delete the image
// 	mlx_terminate(mlx->mlx_p); // terminate the mlx pointer
// 	//mlx_close_window(mlx->mlx_p); // close the window
// 	while (mlx->dt->map2d[i])
// 		free(mlx->dt->map2d[i++]); // free the map line by line
// 	free(mlx->dt->map2d); // free the map
// 	free(mlx->dt); // free the data structure
// 	free(mlx->ply); // free the player structure
// 	free(mlx->ray); // free the ray structure
// 	printf("Game closed\n"); // print the message
// 	exit(0); // exit the game
// }

//##############################################################################################//
//##############################TEMPORARY MINIMAP ##############################//
//##############################################################################################//


// void	draw_minimap_square(t_mlx *cub ,t_dbl_pt map_pt, size_t size, uint32_t color)
// {
// 	for (size_t y = map_pt.y; y <= (map_pt.y + size); y++)
// 	{
// 		for (size_t x = map_pt.x; x <= (map_pt.x + size); x++)
// 		{
// 			if (y == (map_pt.y + size) || x == (map_pt.x + size) || y == map_pt.y || x == map_pt.x)
// 				mlx_put_pixel(cub->img, x, y, 0x000000ff);
// 			else	mlx_put_pixel(cub->img, x, y, color);
// 		}
// 	}
// }

// void draw_line(t_mlx *cub, t_dbl_pt start, t_dbl_pt end, uint32_t color)
// {
//     int dx = fabs(end.x - start.x);
//     int dy = fabs(end.y - start.y);
//     int step_x = start.x < end.x ? 1 : -1;
//     int step_y = start.y < end.y ? 1 : -1;
//     int err = dx - dy;

//     while (true)
//     {
//         mlx_put_pixel(cub->img, start.x, start.y, color);
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

// void draw_player(t_mlx *cub)
// {
//     int player_x;
//     int player_y; 
//     int ray_end_x;
//     int ray_end_y; 
	
// 	player_x = cub->dt->p.x * MINIMAP_TILE_SIZE;
// 	player_y = cub->dt->p.y * MINIMAP_TILE_SIZE;
//     draw_minimap_square(cub, (t_dbl_pt){player_x - 10 / 2, player_y - 10 / 2}, 10, 0x00ff2eff);
//     ray_end_x = (player_x + (cub->dt->p.x * 10));
//     ray_end_y = (player_y + (cub->dt->p.y * 10));
//     draw_line(cub, (t_dbl_pt){player_x, player_y}, (t_dbl_pt){ray_end_x, ray_end_y}, 0xFF0000ff);
// }

// uint32_t	set_minimap_color(t_mlx *cub, t_dbl_pt *pt)
// {
// 	uint32_t	color;
// 	int x;
// 	int y;

// 	x = pt->x;
// 	y = pt->y;
// 	color = 0xffffffff;
// 	if (cub->dt->map2d[y][x] == '1')
// 		color = 0xffc100ff;
// 	else if (cub->dt->map2d[y][x] == '0')
// 		color = 0xd75000ff;
// 	return (color);
// }

// void	draw_minimap(t_mlx *cub)
// {
// 	t_dbl_pt	pt;
// 	t_dbl_pt	map_pt;
// 	uint32_t	color;
	
// 	for (pt.y = 0; pt.y < cub->dt->m.y; pt.y++)
// 	{
// 		for (pt.x = 0; pt.x < cub->dt->m.x; pt.x++)
// 		{
// 			map_pt.y = pt.y * MINIMAP_TILE_SIZE;
// 			map_pt.x = pt.x * MINIMAP_TILE_SIZE;
// 			color = set_minimap_color(cub, &pt);
// 			draw_minimap_square(cub, map_pt, MINIMAP_TILE_SIZE, color);
// 		}
// 	}
// 	draw_player(cub);
// }

//################################################################################//
//############################## THE MOVEMENT CODE ##############################//
//################################################################################//

void	ft_reles(mlx_key_data_t keydata, t_mlx *mlx)	// release the key
{
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE))
		mlx->ply->l_r = 0;
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE))
		mlx->ply->l_r = 0;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_RELEASE))
		mlx->ply->u_d = 0;
	else if (keydata.key == MLX_KEY_W && (keydata.action == MLX_RELEASE))
		mlx->ply->u_d = 0;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		mlx->ply->rot = 0;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		mlx->ply->rot = 0;
}

void mlx_key(mlx_key_data_t keydata, void *ml)	// key press
{
	t_mlx	*mlx;

	mlx = ml;
	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)) 
		mlx_close_window(mlx->mlx_p);
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS)) // move left
		mlx->ply->l_r = -1;
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS)) // move right
		mlx->ply->l_r = 1;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS)) // move down
		mlx->ply->u_d = -1;
	else if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS) // move up
		mlx->ply->u_d = 1;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS) // rotate left
		mlx->ply->rot = -1;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS) // rotate right
		mlx->ply->rot = 1;
	ft_reles(keydata, mlx); // release the key
}

void	rotate_player(t_mlx *mlx, int i)	// rotate the player
{
	if (i == 1)
	{
		mlx->ply->angle += ROTATION_SPEED; // rotate right
		if (mlx->ply->angle > 2 * M_PI)
			mlx->ply->angle -= 2 * M_PI;
	}
	else
	{
		mlx->ply->angle -= ROTATION_SPEED; // rotate left
		if (mlx->ply->angle < 0)
			mlx->ply->angle += 2 * M_PI;
	}
}

void	move_player(t_mlx *mlx, double move_x, double move_y)	// move the player
{
	int		map_grid_y;
	int		map_grid_x;
	int		new_x;
	int		new_y;

	new_x = roundf(mlx->ply->plyr_x + move_x); // get the new x position
	new_y = roundf(mlx->ply->plyr_y + move_y); // get the new y position
	map_grid_x = (new_x / TILE_SIZE); // get the x position in the map
	map_grid_y = (new_y / TILE_SIZE); // get the y position in the map
	if (mlx->dt->map2d[map_grid_y][map_grid_x] != '1' && \
	(mlx->dt->map2d[map_grid_y][mlx->ply->plyr_x / TILE_SIZE] != '1' && \
	mlx->dt->map2d[mlx->ply->plyr_y / TILE_SIZE][map_grid_x] != '1')) // check the wall hit and the diagonal wall hit
	{
		mlx->ply->plyr_x = new_x; // move the player
		mlx->ply->plyr_y = new_y; // move the player
	}
}

void set_angle(t_mlx *mlx) //set rotational angle
{
	if (mlx->ply->rot == 1) //rotate right
		rotate_player(mlx, 1);
	if (mlx->ply->rot == -1) //rotate left
		rotate_player(mlx, 0);
}

void	set_player(t_mlx *mlx) //, double move_x, double move_y)	// hook the player
{
	t_dbl_pt move;

	if (mlx->ply->l_r == 1) //move right
	{
		move.x = -sin(mlx->ply->angle) * PLAYER_SPEED;
		move.y = cos(mlx->ply->angle) * PLAYER_SPEED;
	}
	if (mlx->ply->l_r == -1) //move left
	{
		move.x = sin(mlx->ply->angle) * PLAYER_SPEED;
		move.y = -cos(mlx->ply->angle) * PLAYER_SPEED;
	}
	if (mlx->ply->u_d == 1) //move up
	{
		move.x = cos(mlx->ply->angle) * PLAYER_SPEED;
		move.y = sin(mlx->ply->angle) * PLAYER_SPEED;
	}
	if (mlx->ply->u_d == -1) //move down
	{
		move.x = -cos(mlx->ply->angle) * PLAYER_SPEED;
		move.y = -sin(mlx->ply->angle) * PLAYER_SPEED;
	}
	move_player(mlx, move.x, move.y); // move the player
}

//#####################################################################################//
//############################## THE WALL RENDERING CODE ##############################//
//#####################################################################################//

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)	// put the pixel
{
	if (x < 0) // check the x position
		return ;
	else if (x >= S_W)
		return ;
	if (y < 0) // check the y position
		return ;
	else if (y >= S_H)
		return ;
	mlx_put_pixel(mlx->img, x, y, color); // put the pixel
}

float	nor_angle(float angle)	// normalize the angle
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}
void	draw_floor_ceiling(t_mlx *mlx, int ray, int t_pix, int b_pix)	// draw the floor and the ceiling
{
	int		i;
	// unsigned int	color;

	i = b_pix;
	// color = (mlx->dt->floor->R << 16 | mlx->dt->floor->G << 8 | mlx->dt->floor->B); // get the color
	while (i < S_H)
	{
		my_mlx_pixel_put(mlx, ray, i++, mlx->dt->Fcolor); // floor
	}
	i = 0;
	// color = (mlx->dt->ceil->R << 16 | mlx->dt->ceil->G << 8 | mlx->dt->ceil->B); // get the color
	while (i < t_pix)
		my_mlx_pixel_put(mlx, ray, i++, mlx->dt->Ccolor); // ceiling
}

mlx_texture_t	*get_texture(t_mlx *mlx, int flag)
{
	mlx->ray->ray_ngl = nor_angle(mlx->ray->ray_ngl);
	if (flag == 0)
	{
		if (mlx->ray->ray_ngl > M_PI / 2 && mlx->ray->ray_ngl < 3 * (M_PI / 2))
			return (mlx->tex->EA);
		else
			return (mlx->tex->WE);
	}
	else
	{
		if (mlx->ray->ray_ngl > 0 && mlx->ray->ray_ngl < M_PI)
			return (mlx->tex->SO);
		else
			return (mlx->tex->NO);
	}
}

double	get_x_o(mlx_texture_t *texture, t_mlx *mlx)
{
	double	x_o;

	if (mlx->ray->flag == 1)
		x_o = (int)fmodf((mlx->ray->horiz.x * (texture->width / TILE_SIZE)), texture->width);
	else
		x_o = (int)fmodf((mlx->ray->vert.y * (texture->width / TILE_SIZE)), texture->width);
	return (x_o);
}

// void	draw_wall(t_mlx *mlx, int t_pix, int b_pix, double wall_h)
// {
// 	double			x_o;
// 	double			y_o;
// 	mlx_texture_t	*texture;
// 	uint32_t		*arr;
// 	double			factor;

// 	texture = get_texture(mlx, mlx->ray->flag);
// 	arr = (uint32_t *)texture->pixels;
// 	factor = (double)texture->height / wall_h;

// 	x_o = get_x_o(texture, mlx);
// 	y_o = (t_pix - (S_H / 2) + (wall_h / 2)) * factor;
// 	if (y_o < 0)
// 		y_o = 0;
// 	while (t_pix < b_pix)
// 	{
// 		my_mlx_pixel_put(mlx, mlx->ray->index, t_pix, reverse_bytes(arr[(int)y_o * texture->width + (int)x_o]));
// 		y_o += factor;
// 		t_pix++;
// 	}
// }

int	reverse_bytes(int c)
{
	unsigned int	b;

	b = 0;
	b |= (c & 0xFF) << 24;
	b |= (c & 0xFF00) << 8;
	b |= (c & 0xFF0000) >> 8;
	b |= (c & 0xFF000000) >> 24;
	return (b);
}

void	draw_wall(t_mlx *mlx, int t_pix, int b_pix, double wall_h)
{
	double			x_o;
	double			y_o;
	mlx_texture_t	*texture;
	uint32_t		*arr;
	double			factor;

	texture = get_texture(mlx, mlx->ray->flag);
	arr = (uint32_t *)texture->pixels;
	factor = (double)texture->height / wall_h;

	x_o = get_x_o(texture, mlx);
	y_o = (t_pix - (S_H / 2) + (wall_h / 2)) * factor;
	if (y_o < 0)
		y_o = 0;
	while (t_pix < b_pix)
	{
		my_mlx_pixel_put(mlx, mlx->ray->index, t_pix, arr[(int)y_o * texture->width + (int)x_o]); //reverse_bytes(arr[(int)y_o * texture->width + (int)x_o]));
		y_o += factor;
		t_pix++;
	}
}

void	render_wall(t_mlx *mlx, int ray)
{
	double	wall_h;
	double	b_pix;
	double	t_pix;

	mlx->ray->distance *= cos(nor_angle(mlx->ray->ray_ngl - mlx->ply->angle));
	wall_h = (TILE_SIZE / mlx->ray->distance) * ((S_W / 2) / tan(mlx->ply->fov_rd / 2));
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

// void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)	// put the pixel
// {
// 	if (x < 0) // check the x position
// 		return ;
// 	else if (x >= S_W)
// 		return ;
// 	if (y < 0) // check the y position
// 		return ;
// 	else if (y >= S_H)
// 		return ;
// 	mlx_put_pixel(mlx->img, x, y, color); // put the pixel
// }

// float	nor_angle(float angle)	// normalize the angle
// {
// 	if (angle < 0)
// 		angle += (2 * M_PI);
// 	if (angle > (2 * M_PI))
// 		angle -= (2 * M_PI);
// 	return (angle);
// }

// void	draw_floor_ceiling(t_mlx *mlx, int ray, int t_pix, int b_pix)	// draw the floor and the ceiling
// {
// 	int		i;
// 	// unsigned int	color;

// 	i = b_pix;
// 	// color = (mlx->dt->floor->R << 16 | mlx->dt->floor->G << 8 | mlx->dt->floor->B); // get the color
// 	while (i < S_H)
// 	{
// 		my_mlx_pixel_put(mlx, ray, i++, mlx->dt->Fcolor); // floor
// 	}
// 	i = 0;
// 	// color = (mlx->dt->ceil->R << 16 | mlx->dt->ceil->G << 8 | mlx->dt->ceil->B); // get the color
// 	while (i < t_pix)
// 		my_mlx_pixel_put(mlx, ray, i++, mlx->dt->Ccolor); // ceiling
// }

// int	get_color(t_mlx *mlx, int flag)	// get the color of the wall
// {
// 	mlx->ray->ray_ngl = nor_angle(mlx->ray->ray_ngl); // normalize the angle
// 	if (flag == 0)
// 	{
// 		if (mlx->ray->ray_ngl > M_PI / 2 && mlx->ray->ray_ngl < 3 * (M_PI / 2))
// 			return (0xB5B5B5FF); // west wall
// 		else
// 			return (0xB5B5B5FF); // east wall
// 	}
// 	else
// 	{
// 		if (mlx->ray->ray_ngl > 0 && mlx->ray->ray_ngl < M_PI)
// 			return (0xF5F5F5FF); // south walls
// 		else
// 			return (0xF5F5F5FF); // north wall
// 	}
// }

// void	draw_wall(t_mlx *mlx, int ray, int t_pix, int b_pix)	// draw the wall
// {
// 	int color;

// 	color = get_color(mlx, mlx->ray->flag);
// 	while (t_pix < b_pix)
// 		my_mlx_pixel_put(mlx, ray, t_pix++, color);
// }

// void	render_wall(t_mlx *mlx, int ray)	// render the wall
// {
// 	double	wall_h;
// 	double	b_pix;
// 	double	t_pix;

// 	mlx->ray->distance *= cos(nor_angle(mlx->ray->ray_ngl - mlx->ply->angle)); // fix the fisheye
// 	wall_h = (TILE_SIZE / mlx->ray->distance) * ((S_W / 2) / tan(mlx->ply->fov_rd / 2)); // get the wall height
// 	b_pix = (S_H / 2) + (wall_h / 2); // get the bottom pixel
// 	t_pix = (S_H / 2) - (wall_h / 2); // get the top pixel
// 	if (b_pix > S_H) // check the bottom pixel
// 		b_pix = S_H;
// 	if (t_pix < 0) // check the top pixel
// 		t_pix = 0;
// 	draw_wall(mlx, ray, t_pix, b_pix); // draw the wall
// 	draw_floor_ceiling(mlx, ray, t_pix, b_pix); // draw the floor and the ceiling
// }

//#################################################################################//
//############################## THE RAYCASTING CODE ##############################//
//#################################################################################//

int	unit_circle(float angle, char c)	// check the unit circle
{
	if (c == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (1);
	}
	else if (c == 'y')
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
			return (1);
	}
	return (0);
}

int	inter_check(float angle, float *inter, float *step, int is_horizon)	// check the intersection
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

int	wall_hit(float x, float y, t_mlx *mlx)	// check the wall hit
{
	int		x_m;
	int		y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor (x / TILE_SIZE); // get the x position in the map
	y_m = floor (y / TILE_SIZE); // get the y position in the map
	if ((y_m >= mlx->dt->m.y || x_m >= mlx->dt->m.x))
		return (0);
	if (mlx->dt->map2d[y_m] && x_m <= (int)ft_strlen(mlx->dt->map2d[y_m]))
		if (mlx->dt->map2d[y_m][x_m] == '1')
			return (0);
	return (1);
}

float	get_h_inter(t_mlx *mlx, float angl)	// get the horizontal intersection
{
	float	h_x;
	float	h_y;
	float	x_step;
	float	y_step;
	int		pixel;

	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(angl);
	h_y = floor(mlx->ply->plyr_y / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angl, &h_y, &y_step, 1);
	h_x = mlx->ply->plyr_x + (h_y - mlx->ply->plyr_y) / tan(angl);
	if ((unit_circle(angl, 'y') && x_step > 0) || (!unit_circle(angl, 'y') && x_step < 0)) // check x_step value
		x_step *= -1;
	while (wall_hit(h_x, h_y - pixel, mlx)) // check the wall hit whit the pixel value
	{
		h_x += x_step;
		h_y += y_step;
	}
	mlx->ray->horiz.x = h_x;
	mlx->ray->horiz.y = h_y;
	return (sqrt(pow(h_x - mlx->ply->plyr_x, 2) + pow(h_y - mlx->ply->plyr_y, 2))); // get the distance
}

float	get_v_inter(t_mlx *mlx, float angl)	// get the vertical intersection
{
	float	v_x;
	float	v_y;
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = TILE_SIZE; 
	y_step = TILE_SIZE * tan(angl);
	v_x = floor(mlx->ply->plyr_x / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angl, &v_x, &x_step, 0); // check the intersection and get the pixel value
	v_y = mlx->ply->plyr_y + (v_x - mlx->ply->plyr_x) * tan(angl);
	if ((unit_circle(angl, 'x') && y_step < 0) || (!unit_circle(angl, 'x') && y_step > 0)) // check y_step value
		y_step *= -1;
	while (wall_hit(v_x - pixel, v_y, mlx)) // check the wall hit whit the pixel value
	{
		v_x += x_step;
		v_y += y_step;
	}
	mlx->ray->vert.x = v_x;
	mlx->ray->vert.y = v_y;
	return (sqrt(pow(v_x - mlx->ply->plyr_x, 2) + pow(v_y - mlx->ply->plyr_y, 2))); // get the distance
}

void	cast_rays(t_mlx *mlx)	// cast the rays
{
	double	h_inter;
	double	v_inter;

	mlx->ray->index = 0;
	mlx->ray->ray_ngl = mlx->ply->angle - (mlx->ply->fov_rd / 2); // the start angle to start from left
	while (mlx->ray->index < S_W) // loop for the rays
	{
		mlx->ray->flag = 0; // flag for the wall
		h_inter = get_h_inter(mlx, nor_angle(mlx->ray->ray_ngl)); // get the horizontal intersection
		v_inter = get_v_inter(mlx, nor_angle(mlx->ray->ray_ngl)); // get the vertical intersection
		if (v_inter <= h_inter) // check the distance
			mlx->ray->distance = v_inter; // get the distance
		else
		{
			mlx->ray->distance = h_inter; // get the distance
			mlx->ray->flag = 1; // flag for the wall
		}
		render_wall(mlx, mlx->ray->index); // render the wall
		mlx->ray->index++; // next ray
		mlx->ray->ray_ngl += (mlx->ply->fov_rd / S_W); // next angle
	}
}


//##############################################################################################//
//############################## START THE GAME AND THE GAME LOOP ##############################//
//##############################################################################################//

void	game_loop(void *ml)	// game loop
{
	t_mlx	*mlx;

	mlx = ml;	// cast to the mlx structure
	mlx_delete_image(mlx->mlx_p, mlx->img);	// delete the image
	mlx->img = mlx_new_image(mlx->mlx_p, S_W, S_H);	// create new image
	set_angle(mlx);
	set_player(mlx); //, 0, 0); // hook the player
	cast_rays(mlx);	// cast the rays
	mlx_image_to_window(mlx->mlx_p, mlx->img, 0, 0); // put the image to the window
}


// void getplayerangle(t_mlx *mlx)
// {
//     if (mlx->dt->map2d[mlx->dt->p.y][mlx->dt->p.x] == 'N')
//     {
//         mlx->ply->angle = 3 * M_PI / 2;
//     }
//     else if (mlx->dt->map2d[mlx->dt->p.y][mlx->dt->p.x] == 'S')
//     {
//         mlx->ply->angle = M_PI / 2;
//     }
//     else if (mlx->dt->map2d[mlx->dt->p.y][mlx->dt->p.x] == 'W')
//     {
//         mlx->ply->angle = M_PI;
//     }
//     else if (mlx->dt->map2d[mlx->dt->p.y][mlx->dt->p.x] == 'E')
//     {
//         mlx->ply->angle = 0;
//     }
// }    
void init_the_player(t_mlx mlx)	// init the player structure
{
	mlx.ply->plyr_x = mlx.dt->p.x * TILE_SIZE + TILE_SIZE / 2; // player x position in pixels in the center of the tile
	mlx.ply->plyr_y = mlx.dt->p.y * TILE_SIZE + TILE_SIZE / 2; // player y position in pixels in the center of the tile
	mlx.ply->fov_rd = (FOV * M_PI) / 180; // field of view in radians
	if (mlx.dt->map2d[mlx.dt->p.y][mlx.dt->p.x] == 'N')
    {
        mlx.ply->angle = 3 * M_PI / 2;
    }
    else if (mlx.dt->map2d[mlx.dt->p.y][mlx.dt->p.x] == 'S')
    {
        mlx.ply->angle = M_PI / 2;
    }
    else if (mlx.dt->map2d[mlx.dt->p.y][mlx.dt->p.x] == 'W')
    {
        mlx.ply->angle = M_PI;
    }
    else if (mlx.dt->map2d[mlx.dt->p.y][mlx.dt->p.x] == 'E')
    {
        mlx.ply->angle = 0;
    } 
	//getplayerangle(&mlx);//mlx.ply->angle = M_PI // player angle
	//the rest of the variables are initialized to zero by calloc
}

void	mlx_texture_fail(t_mlx *mlx)	// texture fail
{
	(void)mlx;
	printf("Error\nTexture failed to load\n");	// print the message
	//ft_exit(mlx);	// exit the game ;aonddgoasno;A;K
}

void	init_the_textures(t_mlx *mlx)	// load the textures
{
	mlx->tex->NO = mlx_load_png(mlx->dt->NO);	// load the north texture
	if (!mlx->tex->NO)	// check the texture
		mlx_texture_fail(mlx);	// texture fail
	mlx->tex->SO = mlx_load_png(mlx->dt->SO);	// load the south texture
	if (!mlx->tex->SO)	// check the texture
		mlx_texture_fail(mlx);	// texture fail
	mlx->tex->WE = mlx_load_png(mlx->dt->WE);	// load the west texture
	if (!mlx->tex->WE)	// check the texture
		mlx_texture_fail(mlx);	// texture fail
	mlx->tex->EA = mlx_load_png(mlx->dt->EA);	// load the east texture
	if (!mlx->tex->EA)	// check the texture
		mlx_texture_fail(mlx);	// texture fail
}

void	start_the_game(t_data *dt)	// start the game
{
	t_mlx	mlx;

	mlx.dt = dt;	// init the mlx structure
	mlx.ply = ft_calloc(1, sizeof(t_player));	// init the player structure i'm using calloc to initialize the variables to zero
	mlx.ray = ft_calloc(1, sizeof(t_ray));	// init the ray structure
	mlx.tex = ft_calloc(1, sizeof(t_textures));	// init the textures structure
	mlx.mlx_p = mlx_init(S_W, S_H, "Cub3D", 0);	// init the mlx pointer
	init_the_player(mlx);	// init the player structure
	init_the_textures(&mlx);	// init the textures
	mlx_key_hook(mlx.mlx_p, &mlx_key, &mlx);	// key press and release
	mlx_loop_hook(mlx.mlx_p, &game_loop, &mlx);	// game loop
	mlx_loop(mlx.mlx_p);
	mlx_terminate(mlx.mlx_p);
	//ft_exit(&mlx);
}

//################################################################################################//
//############################## THE MAIN FUNCTION AND INIT THE MAP ##############################//
//################################################################################################//

// t_data *init_argumet(t_data *game)	// init the data structure
// {
//     t_data *dt = calloc(1, sizeof(t_data));// init the data structure
// 	//dt->map2d = calloc(10, sizeof(char *)); // init the map
//     makemap(dt, game); // make the map
// 	dt->p_y = (int)game->ppos.y; // player y position in the map
// 	dt->p_x = (int)game->ppos.x; // player x position in the map
// 	dt->w_map = game->msize.x; // map width
// 	dt->h_map = game->msize.y; // map height
// 	return (dt); // return the data structure
// }

void testchecker(t_data *game) //TESTER DELETE
{
	printf("NO: %s\n", game->NO);
	printf("SO: %s\n", game->SO);
	printf("WE: %s\n", game->WE);
	printf("EA: %s\n", game->EA);
	printf("sqmap\n");
	for (int i = 0; game->map2d[i] != NULL; i++)
    {
        printf("%s\n", game->map2d[i]);
    }
	printf("\n player x: %d y: %d \n", game->p.x, game->p.y);
	printf("\n map x: %d y: %d \n", game->m.x, game->m.y);
    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
}

int main(int argc, char **argv)	// main function
{
    t_data dt;

	dt = (t_data){0};
	check_file(argc, argv, &dt);
	testchecker(&dt);
	start_the_game(&dt);
	free_struct(&dt);
	//ft_exit()	// start the game
	return 0;
}
