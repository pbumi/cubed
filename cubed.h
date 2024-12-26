/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:49:04 by pbumidan          #+#    #+#             */
/*   Updated: 2024/12/26 15:54:20 by pbumidan         ###   ########.fr       */
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

typedef struct s_textures
{
	mlx_texture_t	*NO;
	mlx_texture_t	*EA;
	mlx_texture_t	*SO;
	mlx_texture_t	*WE;
}			t_textures;

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
	int		index;
	int		flag;		// flag for the wall
	t_dbl_pt	horiz;		// horizontal wall hit
	t_dbl_pt	vert;		// vertical wall hit
}	t_ray;

typedef struct s_data	//the data structure
{
	char 	*map;
	char	**map2d;	// the map
	t_int_pt	p; // player index
	t_int_pt	m; // map index
	char    *NO;
    char    *EA;
    char    *WE;
    char    *SO;
	bool	W;
	unsigned int	Fcolor;
	bool			F;
	unsigned int	Ccolor;
	bool			C;
}	t_data;

typedef struct s_mlx	//the mlx structure
{
	mlx_t			*mlx_p;	// the mlx pointer
	mlx_image_t		*img;	// the image
	t_ray			*ray;	// the ray structure
	t_data			*dt;	// the data structure
	t_player		*ply;	// the player structure
	t_textures		*tex;
}	t_mlx;

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
