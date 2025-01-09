/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:46:33 by pbumidan          #+#    #+#             */
/*   Updated: 2025/01/09 20:55:12 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cubed.h"

bool check_components(int fd, t_data *game)
{
    char *line;
	
	line = get_next_line(fd);
    while (line != NULL)
    {
		if (extract_components(fd, line, game) == false)
		{
			free(line);
			return false;
		}
        free(line);
		line = get_next_line(fd);
    }
	if (!game->W || !game->C || !game->F)
	{
		error_msg("* Missing file components *");
		free(line);
		return false;
	}
	free (line);
	return true;
}

// void	initialize_struct(t_data *game)
// {
//     game->NO = NULL;
//     game->SO = NULL;
//     game->WE = NULL;
//     game->EA = NULL;
// 	game->W = false;
// 	game->Fcolor = 0;
// 	game->Ccolor = 0;
// 	game->C = false;
// 	game->F = false;
// 	game->p.x = 0;
// 	game->p.y = 0;
// 	game->m.x = 0;
// 	game->m.y = 0;
// 	game->map = NULL;
// 	game->map2d = NULL;
// }

void initialize_game(char *cubfile, t_data *dt)
{
	int fd;
	
	fd = open(cubfile, O_RDONLY);
    if (fd < 0)
    {
		free_data(dt);
		error_msg("* Error opening file *");
		exit (EXIT_FAILURE);
    }
	else if (!check_components(fd, dt))
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

bool    valid_cub(char *argv)
{
    int len;

    if (!argv)
        return false;
    len = ft_strlen(argv);
    if (len > 4 && ft_strncmp(&argv[len - 4], ".cub", 4) == 0)
    {
        return true;
    }
	return false;
}

void	check_file(int argc, char **argv, t_data *dt)
{
	if (argc > 2)
	{
		error_msg("* Run with only 1 .cub file *");
		exit (EXIT_FAILURE);
	}
	else if (argc == 1)
	{
		error_msg("* Run with .cub file *");
		exit (EXIT_FAILURE);
	}
	else if (argc == 2)
	{
		if (!valid_cub(argv[1]))
		{
			error_msg("* Invalid file *");
			exit (EXIT_FAILURE);
		}
		else
		{	
			initialize_game(argv[1], dt);
		}
	}
}
