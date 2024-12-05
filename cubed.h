/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:49:04 by pbumidan          #+#    #+#             */
/*   Updated: 2024/12/05 18:41:38 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_H
# define CUBED_H

# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include "./libft/libft.h"
# include "./gnl/get_next_line.h"
# include "./MLX42/include/MLX42/MLX42.h"

# define WIDTH 500
# define HEIGHT 500

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
	mlx_texture_t	*F;
	mlx_texture_t	*C;
}					t_textures;

typedef struct s_images
{
	mlx_image_t	*NO;
	mlx_image_t	*EA;
	mlx_image_t	*SO;
	mlx_image_t	*WE;
	mlx_image_t	*F;
	mlx_image_t	*C;
}				t_images;

typedef struct s_main
{
    t_wall  *walls;
	t_fc	*floor;
    t_fc    *ceil;
    char    *map;
    char    **map_arr;
    int		p_x;
	int		p_y;
	int		w_map;
	int		h_map;
    mlx_t   *mlx_ptr;
    t_textures  *textu;
    t_images    *imag;
    mlx_image_t *window;
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


#endif
