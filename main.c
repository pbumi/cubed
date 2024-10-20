/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 20:36:10 by pbumidan          #+#    #+#             */
/*   Updated: 2024/10/20 15:03:38 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cubed.h"
# include <stdio.h>

void safe_free(void **ptr)
{
    if (*ptr)
    {
        free(*ptr);
        *ptr = NULL;
    }
}

void free_struct(t_main *game)
{
    // Free wall components
    safe_free((void **)&game->walls->NO);
    safe_free((void **)&game->walls->SO);
    safe_free((void **)&game->walls->WE);
    safe_free((void **)&game->walls->EA);
    
    // Free walls struct itself
    safe_free((void **)&game->walls);

    // Free floor and ceiling components
    safe_free((void **)&game->floor);
    safe_free((void **)&game->ceil);
}

void    free_arr(char **arr)
{
    size_t i = 0;
    while (arr[i])
        free(arr[i++]);
    free(arr);
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

bool	check_file(int argc, char **argv)
{
	if (argc > 2)
	{
		ft_putstr_fd("Error\n*  Only one (1) file *\n\n", 2);
		return false;
	}
	else if (argc == 1)
	{
		ft_putstr_fd("Error\n* Run with .cub file and press ENTER *\n\n", 2);
		return false;
	}
	else if (argc == 2)
	{
		if (!valid_cub(argv[1]))
		{
			ft_putstr_fd("Error\n* Invalid file *\n\n", 2);
			return false;
		}
	}
	return true;
}

char *get_substr(char *line, int start)
{
	char *substr = NULL;
	int x = start;
	int end;
	while(line[x] && (line[x] == ' ' || (line[x] >= 9 && line[x] <= 13)))
    {
		x++;
    }
	end = ft_strlen(line) - 1;
	while (end > x && (line[end] == ' ' || (line[end] >= 9 && line[end] <= 13)))
    {
        end--;
    }
	substr = ft_substr(line, x, end - x + 1);
	return (substr);
}

size_t  arr_size(char **arr)
{
    size_t count;
    
    count = 0;
    while (arr[count] != NULL)
    {
        count++;
    }
    return (count);
}

bool check_range(char **colors)
{
    if (ft_atoi(colors[0]) < 0 || ft_atoi(colors[0]) > 255)
        return false;
    if (ft_atoi(colors[1]) < 0 || ft_atoi(colors[1]) > 255)
        return false;
    if (ft_atoi(colors[2]) < 0 || ft_atoi(colors[2]) > 255)
        return false;
    return true;
}

bool get_rgb(char *line, t_fc *fc)
{
    char **colors;
	colors = ft_split(line, ',');
    if (!colors)
    {
        ft_putstr_fd("Error\n* Memory allocation failed for colors *\n\n", 2);
        return false;
    }
    if ((arr_size(colors) != 3) || (check_range(colors) == false))
    {
        ft_putstr_fd("Error\n* Invalid parmeters for colors *\n\n", 2);
        free_arr(colors);
        return false;
    }
    fc->R = ft_atoi(colors[0]);
    fc->G = ft_atoi(colors[1]);
    fc->B = ft_atoi(colors[2]);
    free_arr(colors);
	return (true);
}

bool is_space(char c)
{
    if ((c == 32 || (c >= 9 && c <= 13)) && c != '\n')
        return true;
    return false;
}

bool extract_rgb(char *line, char *str, t_fc *fc)
{
    // Check if the line starts with the correct prefix (C or F)
    if (ft_strncmp(line, str, 1) == 0 && is_space(line[1]) == true)
    {
        char *sub = get_substr(line, 2); // Extract substring after 'C' or 'F'
        printf("Extracting RGB from: %s\n", sub);
        
        // Attempt to extract RGB values
        if (get_rgb(sub, fc) == false)
        {
            free(sub);  // Clean up substring memory
            return false;  // Return false if RGB extraction fails
        }
        free(sub);  // Clean up substring memory
        return true;  // Return true if successful
    }
    return false;  // Return false if the line doesn't match
}

bool check_wall_component(char *line, char *identifier, char **wall_ptr)
{
    // Check if the line starts with the wall identifier (like "NO", "SO", etc.)
    if (ft_strncmp(line, identifier, 2) == 0 && !(*wall_ptr))
    {
        // Ensure the character after the identifier is a space
        if (is_space(line[2]) == true)
        {
            // Extract the substring after the identifier and store it
            *wall_ptr = get_substr(line, 3);  // Start after the identifier and space
            return true;
        }
        else
        {
            ft_putstr_fd("Error\n* Invalid format for ", 2);
            ft_putstr_fd(identifier, 2);
            ft_putstr_fd(" wall *\n\n", 2);
            return false;
        }
    }
    return true;  // If the identifier doesn't match, just return true
}

bool check_walls(char *line, t_main *game)
{
    // Check NO wall
    if (!check_wall_component(line, "NO", &game->walls->NO))
        return false;

    // Check SO wall
    if (!check_wall_component(line, "SO", &game->walls->SO))
        return false;

    // Check WE wall
    if (!check_wall_component(line, "WE", &game->walls->WE))
        return false;

    // Check EA wall
    if (!check_wall_component(line, "EA", &game->walls->EA))
        return false;

    return true;
}

bool    initialize_struct(t_main *game)
{
    game->walls = malloc(sizeof(t_wall));
    if (!game->walls)
    {
        ft_putstr_fd("Error\n* Memory allocation failed for walls *\n\n", 2);
        return false;
    }
    game->ceil = malloc(sizeof(t_fc));
    game->floor = malloc(sizeof(t_fc));
    if (!game->ceil || !game->floor)
    {
        ft_putstr_fd("Error\n* Memory allocation failed for ceiling/floor *\n\n", 2);
        return false;
    }
    game->walls->NO = NULL;
    game->walls->SO = NULL;
    game->walls->WE = NULL;
    game->walls->EA = NULL;
    return true;
}

bool check_components(int fd, t_main *game)
{
    char *line = NULL;
    bool F = false;
    bool C = false;

    while ((line = get_next_line(fd)) != NULL)
    {
        if (check_walls(line, game) == false)
        {
            free (line);
            return false;  
        }
        if (extract_rgb(line, "C", game->ceil) == true)
        {
            C = true;
        }
        if (extract_rgb(line, "F", game->floor) == true)
        {
            F = true;
        }
        free(line);
    }
	line = get_next_line(-1);
    if (!game->walls->NO || !game->walls->SO || !game->walls->WE || !game->walls->EA)
    {
        ft_putstr_fd("Error\n* Missing one or more wall components *\n\n", 2);
            // Free any allocated walls
        return false;
    }
    if (!F || !C)
    {
        return false;
    }
    return true;
}

bool initialize_game(char *cubfile, t_main *game)
{
	ft_putstr("initgame\n");
	int fd;
    if (initialize_struct(game) == false)
    {
        return false;
    }
	fd = open(cubfile, O_RDONLY);
    if (fd < 0)
    {
        ft_putstr_fd("Error\n* Error opening file *\n\n", 2);
        return false;
    }
    if (check_components(fd, game) == false)
    {
        close(fd);
        return false;
    }
    return true;
}

int main(int argc, char **argv)
{
	t_main game;
	game = (t_main){0};
	if (check_file(argc, argv) == false)
		exit (1);
	if (initialize_game(argv[1], &game) == false)
    {
		free_struct(&game);
        return 1;
    }
	ft_putstr("WOW\n");
	ft_putstr(game.walls->NO);
	ft_putstr("\n");
	ft_putstr(game.walls->SO);
	ft_putstr("\n");
	ft_putstr(game.walls->WE);
	ft_putstr("\n");
	ft_putstr(game.walls->EA);
	ft_putstr("\n");
    printf("F: %d, %d, %d \n", game.floor->R, game.floor->G, game.floor->B);
    printf("C: %d, %d, %d \n", game.ceil->R, game.ceil->G, game.ceil->B);
	free_struct(&game);
    return 0;
}
