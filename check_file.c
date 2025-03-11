/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:46:33 by pbumidan          #+#    #+#             */
/*   Updated: 2025/02/15 17:20:52 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	free_data(t_data *game)
{
	free(game->map);
	free_arr(game->map2d);
	if (game->ea_t)
		mlx_delete_texture(game->ea_t);
	if (game->we_t)
		mlx_delete_texture(game->we_t);
	if (game->no_t)
		mlx_delete_texture(game->no_t);
	if (game->so_t)
		mlx_delete_texture(game->so_t);
	game->no_t = NULL;
	game->so_t = NULL;
	game->we_t = NULL;
	game->ea_t = NULL;
	game->map = NULL;
	game->map2d = NULL;
}

static bool	parse_file(int fd, t_data *game)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (extract_components(fd, line, game) == false)
		{
			free(line);
			return (false);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (!game->wall || !game->ceil || !game->floor)
	{
		error_msg("* Missing file components *");
		free(line);
		return (false);
	}
	free (line);
	return (true);
}

static void	open_file(char *cubfile, t_data *dt)
{
	int	fd;

	fd = open(cubfile, O_RDONLY);
	if (fd < 0)
	{
		free_data(dt);
		error_msg("* Error opening file *");
		exit (EXIT_FAILURE);
	}
	else if (!parse_file(fd, dt))
	{
		get_next_line(-1);
		close(fd);
		free_data(dt);
		exit (EXIT_FAILURE);
	}
	else
	{
		get_next_line(-1);
		close(fd);
	}
}

static bool	valid_cub(char *argv)
{
	int	len;

	if (!argv)
	{
		return (false);
	}
	len = ft_strlen(argv);
	if (len > 4 && ft_strncmp(&argv[len - 4], ".cub", 4) == 0)
	{
		return (true);
	}
	return (false);
}

bool	check_args(int argc, char **argv, t_data *dt)
{
	if (argc > 2)
	{
		error_msg("* Run with only 1 .cub file *");
		return (false);
	}
	else if (argc == 1)
	{
		error_msg("* Run with .cub file *");
		return (false);
	}
	else if (argc == 2)
	{
		if (!valid_cub(argv[1]))
		{
			error_msg("* Invalid file *");
			return (false);
		}
		else
		{	
			open_file(argv[1], dt);
		}
	}
	return (true);
}
