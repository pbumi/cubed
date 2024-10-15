/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 20:36:10 by pbumidan          #+#    #+#             */
/*   Updated: 2024/10/15 20:39:00 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cubed.h"

int	valid_cub(char *argv)
{
	char	*filetype;

	if (!argv)
		return (0);
	if (ft_strlen(argv) < 5)
		return (0);
	filetype = ft_strrchr((char *)argv, '.');
	if (!filetype)
		return (0);
	if (ft_strncmp(filetype, ".cub", 5) == 0)
		return (1);
	return (0);
}

int	check_file(int argc, char **argv)
{
	if (argc > 2)
	{
		ft_putstr_fd("Error\n*  Only one (1) file *\n\n", 2);
		return (0);
	}
	else if (argc == 1)
	{
		ft_putstr_fd("Error\n* Run with .cub file and press ENTER *\n\n", 2);
		return (0);
	}
	else if (argc == 2)
	{
		if (!valid_cub(argv[1]))
		{
			ft_putstr_fd("Error\n* Invalid file *\n\n", 2);
			return (0);
		}
		else if (valid_cub(argv[1]))
			return (1);
	}
	return (0);
}

char *get_substr(char *line, int start)
{
	char *substr = NULL;
	int x = start;
	int end;
	ft_putstr("getsub\n");
	while(line[x] && (line[x] == ' ' || (line[x] >= 9 && line[x] <= 13)))
		x++;
	end = ft_strlen(line) - 1;
	while (end > x && (line[end] == ' ' || (line[end] >= 9 && line[end] <= 13)))
        end--;
	substr = ft_substr(line, x, end - x + 1);
	ft_putstr("substr: ");
	ft_putstr(substr);
	ft_putstr("\n");
	return (substr);
}

bool is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

bool check_fc(int fd, t_main *game)
{
	char *line = NULL;
	
	game->ceil = malloc(sizeof(t_fc));
	if (!game->ceil)
	    {
        ft_putstr_fd("Error\n* Memory allocation failed for ceiling *\n\n", 2);
        close(fd);
        return false;
    }
	  while ((line = get_next_line(fd)) != NULL)
    {
        ft_putstr("test: ");
        ft_putstr(line);
        ft_putstr("\n");
        if (ft_strncmp(line, "F", 1) == 0 && !game->walls->NO)
		{
            if (is_space(line[2]))
            {
                ft_putstr("b4sub\n");
                game->walls->NO = get_substr(line, 3); // Start after "NO "
                free(line);
            }
            else
            {
                ft_putstr_fd("Error\n* Invalid format for NO wall *\n\n", 2);
                free(line);
                close(fd);
                return false;
            }
        }

}

bool check_walls(int fd, t_main *game)
{   
    char *line = NULL;

    ft_putstr("checkcomp\n");

    // Allocate memory for walls
    game->walls = malloc(sizeof(t_wall));
    if (!game->walls)
    {
        ft_putstr_fd("Error\n* Memory allocation failed for walls *\n\n", 2);
        close(fd);
        return false;
    }

    // Initialize walls to NULL
    game->walls->NO = NULL;
    game->walls->SO = NULL;
    game->walls->WE = NULL;
    game->walls->EA = NULL;

    // Read the file line by line
    while ((line = get_next_line(fd)) != NULL)
    {
        ft_putstr("test: ");
        ft_putstr(line);
        ft_putstr("\n");
        if (ft_strncmp(line, "NO", 2) == 0 && !game->walls->NO)
		{
            if (is_space(line[2]))
            {
                ft_putstr("b4sub\n");
                game->walls->NO = get_substr(line, 3); // Start after "NO "
                free(line);
            }
            else
            {
                ft_putstr_fd("Error\n* Invalid format for NO wall *\n\n", 2);
                free(line);
                close(fd);
                return false;
            }
        }
        else if (ft_strncmp(line, "SO", 2) == 0 && !game->walls->SO)
        {
            if (is_space(line[2]))
            {
                ft_putstr("b4sub\n");
                game->walls->SO = get_substr(line, 3); // Start after "NO "
                free(line);
            }
            else
            {
                ft_putstr_fd("Error\n* Invalid format for SO wall *\n\n", 2);
                free(line);
                close(fd);
                return false;
            }
        }
        else if (ft_strncmp(line, "WE",2) == 0 && !game->walls->WE)
        {
            if (is_space(line[2]))
            {
                ft_putstr("b4sub\n");
                game->walls->WE = get_substr(line, 3); // Start after "NO "
                free(line);
            }
            else
            {
                ft_putstr_fd("Error\n* Invalid format for WE wall *\n\n", 2);
                free(line);
                close(fd);
                return false;
            }
        }
        else if (ft_strncmp(line, "EA", 2) == 0 && !game->walls->EA)
        {
            if (is_space(line[2]))
            {
                ft_putstr("b4sub\n");
                game->walls->EA = get_substr(line, 3); // Start after "NO "
                free(line);
            }
            else
            {
                ft_putstr_fd("Error\n* Invalid format for EA wall *\n\n", 2);
                free(line);
                close(fd);
                return false;
            }
        }
        else
        {
            // Ignore other lines or handle as needed
            free(line);
        }
    }

    close(fd);

    // Validate that all walls have been set
    if (!game->walls->NO || !game->walls->SO || !game->walls->WE || !game->walls->EA)
    {
        ft_putstr_fd("Error\n* Missing one or more wall components *\n\n", 2);
        // Free any allocated walls
        if (game->walls->NO) free(game->walls->NO);
        if (game->walls->SO) free(game->walls->SO);
        if (game->walls->WE) free(game->walls->WE);
        if (game->walls->EA) free(game->walls->EA);
        free(game->walls);
        return false;
    }

    return true;
}

void initialize_game(char *cubfile, t_main *game)
{
	ft_putstr("initgame\n");
	int fd;
	fd = open(cubfile, O_RDONLY);
    if (fd < 0)
    {
        ft_putstr_fd("Error\n* Error opening file *\n\n", 2);
        exit(1);
    }
	if (check_walls(fd, game) == false)
		exit(1);//
	if (check_fc(fd, game) == false)
		exit (1);
	
}

int main(int argc, char **argv)
{
	t_main game;
	game = (t_main){0};
	if (!check_file(argc, argv))
		exit (1);
	initialize_game(argv[1], &game);
	ft_putstr("WOW\n");
	ft_putstr(game.walls->NO);
	ft_putstr("\n");
	ft_putstr(game.walls->SO);
	ft_putstr("\n");
	ft_putstr(game.walls->WE);
	ft_putstr("\n");
	ft_putstr(game.walls->EA);
	ft_putstr("\n");
	// Free allocated memory
    free(game.walls->NO);
    free(game.walls->SO);
    free(game.walls->WE);
    free(game.walls->EA);
    free(game.walls);
	
}

