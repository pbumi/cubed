/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:54:40 by pbumidan          #+#    #+#             */
/*   Updated: 2025/02/15 17:16:29 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

bool	load_texture(char *identifier, t_data *game, char *tmp)
{
	if (ft_strncmp("NO ", identifier, 3) == 0)
	{
		game->no_t = mlx_load_png(tmp);
		if (!game->no_t)
			return (false);
	}
	else if (ft_strncmp("SO ", identifier, 3) == 0)
	{
		game->so_t = mlx_load_png(tmp);
		if (!game->so_t)
			return (false);
	}
	else if (ft_strncmp("WE ", identifier, 3) == 0)
	{
		game->we_t = mlx_load_png(tmp);
		if (!game->we_t)
			return (false);
	}
	else if (ft_strncmp("EA ", identifier, 3) == 0)
	{
		game->ea_t = mlx_load_png(tmp);
		if (!game->ea_t)
			return (false);
	}
	return (true);
}

bool	parse_wall(char *line, char *identifier, t_data *game, bool *OK)
{
	char	*tmp;

	if (ft_strncmp(line, identifier, 3) == 0 && *OK == true)
	{
		error_msg("* Duplicate texture *");
		return (false);
	}
	else if (ft_strncmp(line, identifier, 3) == 0 && *OK == false)
	{
		tmp = remove_wspace(line, 3);
		if (!load_texture(identifier, game, tmp))
		{
			free(tmp);
			error_msg("* Failed to load texture *");
			return (false);
		}
		free(tmp);
		*OK = true;
		return (true);
	}
	return (true);
}
