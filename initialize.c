/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:46:33 by pbumidan          #+#    #+#             */
/*   Updated: 2024/12/21 19:39:28 by pbumidan         ###   ########.fr       */
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
			free_and_close(line, fd);
			return false;
		}
		else
		{
        	free(line);
			line = get_next_line(fd);
		}
    }
	if (!game->walls->walls_OK || !game->C || !game->F)
	{
		errorhandler(game,"* Missing components *", false);
		free_and_close(line,fd);
		return false;
	}
	free_and_close(line, fd);
	return true;
}

void	initialize_struct(t_data *game)
{
    game->walls = malloc(sizeof(t_wall));
    if (!game->walls)
    {
		errorhandler(game, "* Memory allocation failed for walls *", true);
    }
	game->walls->walls_OK = false;
    game->walls->NO = NULL;
    game->walls->SO = NULL;
    game->walls->WE = NULL;
    game->walls->EA = NULL;
	game->Fcolor = 0;
	game->Ccolor = 0;
	game->p.x = 0;
	game->p.y = 0;
	game->m.x = 0;
	game->m.y = 0;
	game->C = false;
	game->F = false;
	game->map = NULL;
	game->map2d = NULL;
}

void initialize_game(char *cubfile, t_data *game)
{
	int fd;
	initialize_struct(game);
	fd = open(cubfile, O_RDONLY);
    if (fd < 0)
    {
		errorhandler(game, "Error opening file *", true);
    }
	if (!check_components(fd, game))
		exit (1);
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

void	check_file(int argc, char **argv, t_data *game)
{
	if (argc > 2)
	{
		error_exit("* Run with only 1 .cub file *", true);
	}
	else if (argc == 1)
	{
		error_exit("* Run with .cub file and press ENTER *", true);
	}
	else if (argc == 2)
	{
		if (!valid_cub(argv[1]))
		{
			error_exit("* Invalid file *", true);
		}
		else
			initialize_game(argv[1], game);
	}
}
