/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:49:04 by pbumidan          #+#    #+#             */
/*   Updated: 2024/10/25 17:53:38 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_H
# define CUBED_H

#include <unistd.h>
#include <stdbool.h>
# include <stdbool.h>
# include "./libft/libft.h"
# include "./gnl/get_next_line.h"
# include "./MLX42/include/MLX42/MLX42.h"

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

typedef struct s_main
{
    t_wall  *walls;
	t_fc	*floor;
    t_fc    *ceil;
    char    *map;
    char    **map_arr;
}	t_main;

#endif
