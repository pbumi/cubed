
# include "cubed.h"
# include <math.h>



//##############################################################################//
//############################## THE EXITING CODE ##############################//
//##############################################################################//

void	free_all(t_mlx *mlx) 		// exit the game
{
 	if (mlx->EA)
		mlx_delete_texture(mlx->EA);
	if (mlx->WE)
 		mlx_delete_texture(mlx->WE);
	if (mlx->NO)
 		mlx_delete_texture(mlx->NO);
	if (mlx->SO)
 		mlx_delete_texture(mlx->SO);
	if (mlx->dt)
		free_data(mlx->dt);
	if (mlx->ply)
		free(mlx->ply);
	if (mlx->ray)
		free(mlx->ray);
}


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
		if (mlx->ply->angle > (2 * M_PI))
			mlx->ply->angle -= (2 * M_PI);
	}
	else
	{
		mlx->ply->angle -= ROTATION_SPEED; // rotate left
		if (mlx->ply->angle < 0)
			mlx->ply->angle += (2 * M_PI);
	}
}

void	move_player(t_mlx *mlx, double move_x, double move_y)	// move the player
{
	int		map_grid_y;
	int		map_grid_x;
	int		new_x;
	int		new_y;

	new_x = (int)(mlx->ply->plyr_x + move_x); // roundf(mlx->ply->plyr_x + move_x); // get the new x position
	new_y = (int)(mlx->ply->plyr_y + move_y);  //roundf(mlx->ply->plyr_y + move_y); // get the new y position
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

	move.x = 0;
	move.y = 0;
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

	i = b_pix;
	while (i < S_H)
	{
		mlx_put_pixel(mlx->img, ray, i, mlx->dt->Fcolor);
		i++;
	}
	i = 0;
	while (i < t_pix)
	{
		mlx_put_pixel(mlx->img, ray, i, mlx->dt->Ccolor);
		i++;
	}
}

mlx_texture_t	*get_texture(t_mlx *mlx)
{
	mlx->ray->ray_ngl = nor_angle(mlx->ray->ray_ngl);
	if (mlx->ray->wall_hit == false)
	{
		if (mlx->ray->ray_ngl > M_PI / 2 && mlx->ray->ray_ngl < 3 * (M_PI / 2))
			return (mlx->WE);
		else
			return (mlx->EA);
	}
	else
	{
		if (mlx->ray->ray_ngl > 0 && mlx->ray->ray_ngl < M_PI)
			return (mlx->NO);
		else
			return (mlx->SO);
	}
}

double	get_pixeldata(mlx_texture_t *texture, t_mlx *mlx)
{
	double	pixel;

	if (mlx->ray->wall_hit == true)
		pixel = (int)(mlx->ray->horiz.x * (texture->width / TILE_SIZE)) % texture->width; //(int)fmodf((mlx->ray->horiz.x * (texture->width / TILE_SIZE)), texture->width);
	else
		pixel = (int)(mlx->ray->vert.y * (texture->width / TILE_SIZE)) % texture->width; //(int)fmodf((mlx->ray->vert.y * (texture->width / TILE_SIZE)), texture->width);
	return (pixel);
}

int reverse_bytes(int c)
{
    return ((c >> 24) & 0xFF) |    // Move most significant byte to least significant byte
           ((c >> 8) & 0xFF00) |   // Move 2nd byte to 3rd byte
           ((c << 8) & 0xFF0000) | // Move 3rd byte to 2nd byte
           ((c << 24) & 0xFF000000); // Move least significant byte to most significant byte
}

void draw_wall(t_mlx *mlx, int t_pix, int b_pix, double wall_h) // edited
{
	t_dbl_pt pix;
    mlx_texture_t   *texture;
    uint32_t        *arr;
    double          factor;

    texture = get_texture(mlx);
    arr = (uint32_t *)texture->pixels;
    factor = (double)texture->height / wall_h;
    pix.x = get_pixeldata(texture, mlx);
    pix.y = (t_pix - (S_H / 2) + (wall_h / 2)) * factor;
    if (pix.y < 0)
        pix.y = 0;
    while (t_pix < b_pix)
    {
        if (t_pix >= 0 && t_pix < S_H) 
        {
            mlx_put_pixel(mlx->img, mlx->ray->index, t_pix, \
			reverse_bytes(arr[(int)pix.y * texture->width + (int)pix.x]));
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
	x_m = (int) (x / TILE_SIZE); //floor (x / TILE_SIZE); // get the x position in the map
	y_m =  (int) (y / TILE_SIZE); //floor (y / TILE_SIZE); // get the y position in the map
	if ((y_m >= mlx->dt->m.y || x_m >= mlx->dt->m.x))
		return (0);
	if (mlx->dt->map2d[y_m] && x_m <= (int)ft_strlen(mlx->dt->map2d[y_m]))
	{
		if (mlx->dt->map2d[y_m][x_m] == '1')
			return (0);
	}
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
	h_y = (int)(mlx->ply->plyr_y / TILE_SIZE) * TILE_SIZE; //floor(mlx->ply->plyr_y / TILE_SIZE) * TILE_SIZE;
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
	v_x = (int)(mlx->ply->plyr_x / TILE_SIZE) * TILE_SIZE; // floor(mlx->ply->plyr_x / TILE_SIZE) * TILE_SIZE;
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
		mlx->ray->wall_hit = false; // flag for the wall
		h_inter = get_h_inter(mlx, nor_angle(mlx->ray->ray_ngl)); // get the horizontal intersection
		v_inter = get_v_inter(mlx, nor_angle(mlx->ray->ray_ngl)); // get the vertical intersection
		if (v_inter <= h_inter) // check the distance
			mlx->ray->distance = v_inter; // get the distance
		else
		{
			mlx->ray->distance = h_inter; // get the distance
			mlx->ray->wall_hit = true; // flag for the wall
		}
		render_ray(mlx, mlx->ray->index); // render the wall
		mlx->ray->index++; // next ray
		mlx->ray->ray_ngl += (mlx->ply->fov_rd / S_W); // next angle
	}
}


//##############################################################################################//
//############################## START THE GAME AND THE GAME LOOP ##############################//
//##############################################################################################//

void free_all_exit(t_mlx *mlx, int exit_code)
{
	free_all(mlx);
	free(mlx);
	mlx = NULL;
	exit(exit_code);
}
void 	end_the_game(t_mlx *mlx, int exit_code)
{
	mlx_delete_image(mlx->mlx_p, mlx->img);
	mlx_terminate(mlx->mlx_p);
	if (exit_code == EXIT_SUCCESS)
		ft_putendl_fd("GAME OVER!", STDOUT_FILENO);
	else
		free_all_exit(mlx, exit_code);
}

void	game_loop(void *ml)	// game loop
{
	t_mlx	*mlx;

	mlx = (t_mlx *)ml;
	mlx_delete_image(mlx->mlx_p, mlx->img);	// delete the image
	mlx->img = mlx_new_image(mlx->mlx_p, S_W, S_H);
	if(!mlx->img)
	{
		ft_putstr_fd("Error\nMlx image load error\n", 2);
		end_the_game(mlx, 1);
	}
	set_angle(mlx);
	set_player(mlx); //, 0, 0); // hook the player
	cast_rays(mlx);	// cast the rays
	mlx_image_to_window(mlx->mlx_p, mlx->img, 0, 0);// put the image to the window
}

void init_the_player(t_mlx *mlx)	// init the player structure
{
	mlx->ply->plyr_x = mlx->dt->p.x * TILE_SIZE + TILE_SIZE / 2; // player x position in pixels in the center of the tile
	mlx->ply->plyr_y = mlx->dt->p.y * TILE_SIZE + TILE_SIZE / 2; // player y position in pixels in the center of the tile
	mlx->ply->fov_rd = (FOV * M_PI) / 180; // field of view in radians
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

void	init_the_textures(t_mlx *mlx)	
{
	mlx->NO = mlx_load_png(mlx->dt->NO);	
	if (!mlx->NO)
	{
		ft_putstr_fd("Error\nFailed to load NO texture\n", 2);
		free_all_exit(mlx, STDERR_FILENO);
	}
	mlx->SO = mlx_load_png(mlx->dt->SO);	
	if (!mlx->SO)
	{
		ft_putstr_fd("Error\nFailed to load SO texture\n", 2);
		free_all_exit(mlx, STDERR_FILENO);
	}
	mlx->WE = mlx_load_png(mlx->dt->WE);
	if (!mlx->WE)
	{
		ft_putstr_fd("Error\nFailed to load WE texture\n", 2);
		free_all_exit(mlx, STDERR_FILENO);
	}
	mlx->EA = mlx_load_png(mlx->dt->EA);
	if (!mlx->EA)
	{
		ft_putstr_fd("Error\nFailed to load EA texturen", 2);
		free_all_exit(mlx, STDERR_FILENO);
	}
}

bool	initialize_mlx_struct(t_mlx *mlx, t_data *dt)
{
	mlx->dt = dt;
	mlx->ply = ft_calloc(1, sizeof(t_player));	// init the player structure i'm using calloc to initialize the variables to zero
	if (!mlx->ply)
	{
		error_msg("* mlx initilization failed *");
		return (false);
	}
	mlx->ray = ft_calloc(1, sizeof(t_ray));	// init the ray structure
	if (!mlx->ray)
	{
		error_msg("* mlx initilization failed *");
		return (false);
	}
	init_the_player(mlx);	// init the player structure
	init_the_textures(mlx);
	return(true);
}


void	start_the_game(t_mlx *mlx)	// start the game
{
	mlx->mlx_p = mlx_init(S_W, S_H, "Cub3D", 0);	// init the mlx pointer
	if (!mlx->mlx_p)
    {
		error_msg("* mlx initilization failed *");
		end_the_game(mlx, 1);
	}
	mlx_key_hook(mlx->mlx_p, &mlx_key, mlx);	// key press and release
	mlx_loop_hook(mlx->mlx_p, &game_loop, mlx);	// game loop
	mlx_loop(mlx->mlx_p);
}

// //################################################################################################//
// //############################## THE MAIN FUNCTION AND INIT THE MAP ##############################//
// //################################################################################################//

int main(int argc, char **argv)	// main function
{
    t_data dt;
	t_mlx	*mlx;

	dt = (t_data){0};
	check_file(argc, argv, &dt);
	mlx = ft_calloc(1, sizeof(t_mlx));
	if (!mlx)
		free_dt_exit(&dt, "* Memory allocation failure*", EXIT_FAILURE);
	if (initialize_mlx_struct(mlx, &dt) == false)
		free_all_exit(mlx, EXIT_FAILURE);
	start_the_game(mlx);
	end_the_game(mlx, EXIT_SUCCESS);
}

