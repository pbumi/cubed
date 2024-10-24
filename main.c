/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 20:36:10 by pbumidan          #+#    #+#             */
/*   Updated: 2024/10/23 17:32:37 by pbumidan         ###   ########.fr       */
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

void    free_arr(char **arr)
{
	if (!arr)
		return;
    size_t x;
	x = 0;
    while (arr[x])
        free(arr[x++]);
    free(arr);
}

void free_struct(t_main *game)
{
    safe_free((void **)&game->walls->NO);
    safe_free((void **)&game->walls->SO);
    safe_free((void **)&game->walls->WE);
    safe_free((void **)&game->walls->EA);
    safe_free((void **)&game->walls);
    safe_free((void **)&game->floor);
    safe_free((void **)&game->ceil);
	safe_free((void **)&game->map);
	free_arr(game->map_arr);
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

bool is_space(char c)
{
    if ((c == 32 || (c >= 9 && c <= 13)) && c != '\n')
        return true;
    return false;
}

bool is_empty_line(char *line)
{
    while (*line)
    {
        if (!is_space(*line))  // Check if the line has a non-space character
            return false;
        line++;
    }
    return true;  // The line has only spaces
}

bool is_broken_map(char *line)
{
	size_t x;
	
	x = 0;
	while (line[x + 1])
    {
        if (line[x] == '\n' && line[x + 1] == '\n')
            return true;
        x++;
    }
    return false; 
}
bool incorrect_mapsize(char *line)
{
	size_t x;
	size_t x_count;
	size_t y_count;
	
	x = 0;
	x_count = 0;
	y_count	= 0;
	while (line[x])
    {
        if (line[x] == '\n')
        {
			y_count++;
			if (x_count < 2) // MIN MAX X
				return true;
		}
		x_count++;
        x++;
    }
	if (y_count < 2) // MIN MAX Y
	{
		return true;
	}
    return false; 
}

bool incorrect_mapcharacter(char *line)
{
	size_t x;
	size_t x_count;
	size_t y_count;
	
	x = 0;
	x_count = 0;
	y_count	= 0;
	while (line[x])
    {
		x_count++;
		if (!ft_strchr(" 01NSWE\n", line[x]))
		{
			printf("Error\n");
			printf("* Invalid character : '%c' in x:%ld y:%ld *\n\n", line[x], x_count, y_count);
			return true;
		}
        if (line[x] == '\n')
        {
			y_count++;
			x_count = -1;
		}
        x++;
    }
    return false; 
}

char *remove_wspace(char *line, int start)
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

bool get_rgb2(char *line, t_fc *fc)
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


bool get_rgb1(char *line, char *str, t_fc *fc)
{
    // Check if the line starts with the correct prefix (C or F)
    if (ft_strncmp(line, str, 1) == 0 && is_space(line[1]) == true)
    {
        char *sub = remove_wspace(line, 2); // Extract substring after 'C' or 'F'
        printf("Extracting RGB from: %s\n", sub);
        
        // Attempt to extract RGB values
        if (get_rgb2(sub, fc) == false)
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
	char *tmp = NULL;
    if (ft_strncmp(line, identifier, 2) == 0 && !(*wall_ptr))
    {
        if (is_space(line[2]) == true)
        {
			tmp = remove_wspace(line, 3);
			if (is_empty_line(tmp) == false)
			{
				*wall_ptr = tmp;
				return true;
			}
			free(tmp);
        }
        ft_putstr_fd("Error\n* Invalid format for ", 2);
        ft_putstr_fd(identifier, 2);
        ft_putstr_fd(" wall *\n\n", 2);
        return false;
    }
    return true;
}

bool check_walls(char *line, t_main *game)
{
    if (!check_wall_component(line, "NO", &game->walls->NO))
        return false;
    if (!check_wall_component(line, "SO", &game->walls->SO))
        return false;
    if (!check_wall_component(line, "WE", &game->walls->WE))
        return false;
    if (!check_wall_component(line, "EA", &game->walls->EA))
	{
        return false;
	}
	if (game->walls->NO && game->walls->SO && game->walls->WE && game->walls->EA)
	{
		game->walls->walls_OK = true;
	}
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
	game->walls->walls_OK = false;
    game->walls->NO = NULL;
    game->walls->SO = NULL;
    game->walls->WE = NULL;
    game->walls->EA = NULL;
    game->ceil = malloc(sizeof(t_fc));
    game->floor = malloc(sizeof(t_fc));
    if (!game->ceil || !game->floor)
    {
        ft_putstr_fd("Error\n* Memory allocation failed for ceiling/floor *\n\n", 2);
        return false;
    }
	game->ceil->OK = false;
	game->floor->OK = false;
    return true;
}

char *extract_loop(char *map_content, int fd)
{
    char *line;
    char *tmp;

    while ((line = get_next_line(fd)) != NULL)
    {
        if (line[0] != '\0')
        {
            tmp = map_content;
            map_content = gnl_strjoin(tmp, line);
            free(tmp);
            if (!map_content)
            {
                free(line);
                return NULL;
            }
        }
        free(line);
    }
    return map_content;
}

bool	validate_map(t_main *game)
{
	if (is_empty_line(game->map) == true)
	{
		ft_putstr_fd("Error\n* Empty MAP *\n\n", 2);
		return false;
	}
	if (is_broken_map(game->map) == true)
	{
		ft_putstr_fd("Error\n* Empty lines in MAP *\n\n", 2);
		return false;
	}
	if (incorrect_mapsize(game->map) == true)
	{
		ft_putstr_fd("Error\n* Incorrect MAP size *\n\n", 2);
		return false;
	}
	if (incorrect_mapcharacter(game->map) == true)
	{
		return false;	
	}
	return true;
}
void	change_space_to1(char *str)
{
	size_t x;

	x = 0;
	while(str[x])
	{
		if (str[x] == ' ')
		{
			str[x] = '1';
		}
		x++; 
	}
}
bool extract_map1(int fd, t_main *game)
{
    char *map_content;
	map_content = ft_strdup("");
    if (!map_content)
        return false;
    map_content = extract_loop(map_content, fd);
    if (!map_content)
        return false;
    game->map = remove_wspace(map_content, 0);
	free(map_content);
	change_space_to1(game->map);
	if (!validate_map(game))
		return false;
    return true;
}

bool	extract_components(int fd, char *line, t_main *game)
{
	if (check_walls(line, game) == false)
        return false;
	if (get_rgb1(line, "F", game->floor) == true)
        game->floor->OK = true;
	if (get_rgb1(line, "C", game->ceil) == true)
	{
        game->ceil->OK = true;
	}
	if (game->walls->walls_OK == true && game->floor->OK && game->ceil->OK)
	{
		if (extract_map1(fd, game) == false)
		{
			return false;
    	}		
	}
	return true;
}

bool check_components(int fd, t_main *game)
{
    char *line = NULL;

    while ((line = get_next_line(fd)) != NULL)
    {
		if (extract_components(fd, line, game) == false)
		{
			free (line);
			line = get_next_line(-1);
			return false;
		}
		else
        	free(line);
    }
	if (!game->walls->walls_OK || !game->floor->OK || !game->ceil->OK)
	{
		ft_putstr_fd("Error\n* Missing components *\n\n", 2);
		return false;
	}
	return true;
}

bool initialize_game(char *cubfile, t_main *game)
{
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
	game->map_arr = ft_split(game->map, '\n');
	if (!game->map_arr)
	{
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
	else
	{
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
		//printf("MAP : %s\n", game.map);
		for (int i = 0; game.map_arr[i] != NULL; i++)
    	{
        printf("%s\n", game.map_arr[i]);
    	}
	}
	free_struct(&game);
    return 0;
}
