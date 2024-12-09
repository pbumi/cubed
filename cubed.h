/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:49:04 by pbumidan          #+#    #+#             */
/*   Updated: 2024/12/09 14:30:42 by pbumidan         ###   ########.fr       */
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

# define WIDTH 1920
# define HEIGHT 1080
# define MINI_TILE 60

# define PLAYER_SPEED 0.1
# define PLAYER_TILE 10

typedef struct s_pt
{
	double	x;
	double	y;
}	t_pt;

typedef struct s_wall
{
    char    *NO;
    char    *EA;
    char    *WE;
    char    *SO;
	bool	walls_OK;
}   t_wall;

typedef struct s_fc
{
    int	R;
    int	G;
	int	B;
    bool OK;
}   t_fc;

typedef struct s_textures
{
	mlx_texture_t	*NO;
	mlx_texture_t	*EA;
	mlx_texture_t	*SO;
	mlx_texture_t	*WE;
}	t_textures;

typedef struct s_images
{
	mlx_image_t	*NO;
	mlx_image_t	*EA;
	mlx_image_t	*SO;
	mlx_image_t	*WE;
}			t_images;

typedef struct s_main
{
    t_wall  *walls;
	t_fc	*floor;
    t_fc    *ceil;
    char    *map;
    char    **map_arr;
    double		p_x;
	double		p_y;
	int		*w_map;
	int		h_map;
    mlx_t   *mlx_ptr;
    t_textures  *textu;
    t_images    *imag;
    mlx_image_t *window;
	mlx_image_t *minimap;
}	t_main;

//map
void	check_file(int argc, char **argv, t_main *game);
bool	extract_components(int fd, char *line, t_main *game);
bool extract_map1(int fd, t_main *game);
bool	validate_map(t_main *game);
bool	check_fill(t_main *game);
//free
void free_struct(t_main *game);
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
void	errorhandler(t_main *game, char *msg, bool fatal);
void	error_exit(char *msg, bool fatal);
size_t  arr_size(char **arr);
//moves
void	key_hook_slow(mlx_key_data_t keydata, void *param);

#endif
