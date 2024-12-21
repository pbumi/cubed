/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:49:04 by pbumidan          #+#    #+#             */
/*   Updated: 2024/12/21 19:35:00 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_H
# define CUBED_H

# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <math.h>
# include "./libft/libft.h"
# include "./gnl/get_next_line.h"
# include "./MLX42/include/MLX42/MLX42.h"

# define S_W 1900 // screen width
# define S_H 1000 // screen height
# define TILE_SIZE 30 // tile size
# define FOV 60 // field of view
# define ROTATION_SPEED 0.045 // rotation speed
# define PLAYER_SPEED 4	// player speed


typedef struct s_dbl_pt
{
	double	x;
	double	y;
}	t_dbl_pt;

typedef struct s_int_pt
{
	int	x;
	int	y;
}	t_int_pt;

typedef struct s_wall
{
    char    *NO;
    char    *EA;
    char    *WE;
    char    *SO;
	bool	walls_OK;
}   t_wall;

typedef struct s_images
{
	mlx_image_t	*NO;
	mlx_image_t	*EA;
	mlx_image_t	*SO;
	mlx_image_t	*WE;
}			t_images;

typedef struct s_player //the player structure
{
	int		plyr_x; // player x position in pixels
	int		plyr_y; // player y position in pixels
	double	angle;	// player angle
	float	fov_rd;	// field of view in radians
	int		rot;	// rotation flag
	int		l_r;	// left right flag
	int		u_d;	// up down flag
}	t_player;

typedef struct s_ray	//the ray structure
{
	double	ray_ngl;	// ray angle
	double	distance;	// distance to the wall
	int		flag;		// flag for the wall
}	t_ray;

typedef struct s_data	//the data structure
{
	t_wall  *walls;
	char 	*map;
	char	**map2d;	// the map
	t_int_pt	p;
	t_int_pt	m;
	unsigned int	Fcolor;
	bool			F;
	unsigned int	Ccolor;
	bool			C;
	// int		p_x;		// player x position in the map
	// int		p_y;		// player y position in the map
	// int		w_map;		// map width
	// int		h_map;		// map height
}	t_data;

typedef struct s_mlx	//the mlx structure
{
	mlx_t			*mlx_p;	// the mlx pointer
	mlx_image_t		*img;	// the image
	t_ray			*ray;	// the ray structure
	t_data			*dt;	// the data structure
	t_player		*ply;	// the player structure
}	t_mlx;

// typedef struct s_main
// {
//     t_wall  *walls;
// 	t_fc	*floor;
//     t_fc    *ceil;
// 	t_int_pt	msize;
//     char    *map;
// 	char	**sq_map;
// }	t_data;

//map
void	check_file(int argc, char **argv, t_data *game);
bool	extract_components(int fd, char *line, t_data *game);
bool extract_map1(int fd, t_data *game);
bool	validate_map(t_data *game);
bool	check_fill(t_data *game);
//free
void free_struct(t_data *game);
void free_arr(char **arr);
void safe_free(void **ptr);
void free_and_close(char *line, int fd);
//space
bool is_space(char c);
char *remove_wspace(char *line, int start);
bool is_empty_line(char *line);
char *remove_wspace(char *line, int start);
char *remove_whitespaces(char *line, int start);
bool remove_spaces(char **colors);
//utils
void	errorhandler(t_data *game, char *msg, bool fatal);
void	error_exit(char *msg, bool fatal);
size_t  arr_size(char **arr);
int find_max(int *arr, int size);
char** allocate2DCharArray(int x, int y);

int find_max(int *arr, int size);
//moves
void	key_hook_slow(void *param);

#endif
