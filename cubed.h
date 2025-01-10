/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:49:04 by pbumidan          #+#    #+#             */
/*   Updated: 2025/01/10 20:35:12 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_H
# define CUBED_H

# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include <math.h>
# include "./libft/libft.h"
# include "./gnl/get_next_line.h"
# include "./MLX42/include/MLX42/MLX42.h"

# define S_W 1900
# define S_H 1000
# define TILE_SIZE 64
# define FOV 60
# define ROTATION_SPEED 0.040
# define PLAYER_SPEED 4

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

typedef struct s_player
{
	t_int_pt	pos;
	double	angle;
	float	fov_rd;
	int		rot;
	int		l_r;
	int		u_d;
}	t_player;

typedef struct s_ray
{
	double		ray_ngl;
	double		distance;
	int			index;
	bool		wall_hit;
	t_dbl_pt	horiz;
	t_dbl_pt	vert;
}	t_ray;

typedef struct s_data
{
	char			*map;
	char			**map2d;
	t_int_pt		p;
	t_int_pt		m;
	mlx_texture_t	*no_t;
	mlx_texture_t	*ea_t;
	mlx_texture_t	*so_t;
	mlx_texture_t	*we_t;
	bool			n;
	bool			e;
	bool			w;
	bool			s;
	bool			wall;
	unsigned int	floor_color;
	bool			floor;
	unsigned int	ceil_color;
	bool			ceil;
}	t_data;

typedef struct s_mlx
{
	mlx_t			*mlx_p;
	mlx_image_t		*img;
	t_ray			*ray;
	t_data			*dt;
	t_player		*ply;
}	t_mlx;

//parsing functions
bool	check_args(int argc, char **argv, t_data *game);
bool	extract_components(int fd, char *line, t_data *game);
bool	parse_rgb(char *line, char *str, t_data *game);
bool	parse_wall(char *line, char *identifier, t_data *game, bool *OK);
bool	extract_map(int fd, t_data *game);
bool	validate_map(t_data *game);
bool	create_sqmap(t_data *game);
bool	check_floodfill(t_data *game, char **tmp_arr, int rows, int cols);

//game functions
void	cast_rays(t_mlx *mlx);
void	render_ray(t_mlx *mlx, int ray);
void	game_hook(void *ml);
void	key_hook(mlx_key_data_t keydata, void *ml);
void	end_the_game(t_mlx *mlx, int exit_code);

//utils
float	nor_angle(float angle);
void	error_msg(char *msg);
char	*remove_wspace(char *line, int start);
void	free_arr(char **arr);
void	free_all(t_mlx *mlx);

#endif
