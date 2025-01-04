/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_extract.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:08:22 by pbumidan          #+#    #+#             */
/*   Updated: 2025/01/04 20:58:29 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cubed.h"

char *extract_loop(char *map_content, int fd)
{
    char *line;
    char *tmp;

    line = get_next_line(fd);
    while (line != NULL)
    {
        if (line[0] != '\0')
        {
            tmp = gnl_strjoin(map_content, line);
            free(map_content);
            if (!tmp)
            {
                free(line);
                map_content = NULL;
                return NULL;
            }
            map_content = tmp;
        }
        free(line);
        line = get_next_line(fd);
    }
    free(line);
    return (map_content);
}

bool extract_map1(int fd, t_data *game)
{
    char *map_content;

    map_content = ft_strdup("");
    if (!map_content)
        return false;
    map_content = extract_loop(map_content, fd);
    if (!map_content)
    {
        return false;
    }
    game->map = ft_strtrim(map_content, "\n");
    if (!game->map)
    {
        free(map_content);
        return false;
    }
    free(map_content);
    map_content = NULL;
    if (validate_map(game) == false)
    {
        free(game->map);
        game->map = NULL;
        return false;
    }
    return true;
}

// char *extract_loop(char *map_content, int fd)
// {
//     char *line;
//     char *tmp;

//     while ((line = get_next_line(fd)) != NULL)
//     {
//         if (line[0] != '\0')
//         {
//             tmp = map_content;
//             map_content = gnl_strjoin(tmp, line);
//             free(tmp);
//             if (!map_content)
//             {
//                 free(line);
//                 return NULL;
//             }
//         }
//         free(line);
//     }
//     return map_content;
// }

// bool extract_map1(int fd, t_data *game)
// {
//     char *map_content;
    
//     map_content = ft_strdup("");
//     if (!map_content)
//         return false;
//     map_content = extract_loop(map_content, fd);
//     if (!map_content)
//     {
//         return false;  // Return false if extract_loop failed to read the map
//     }
//     game->map = ft_strtrim(map_content, "\n");
//     if (!game->map)
//     {
//         free(map_content);  // Ensure map_content is freed if strtrim fails
//         return false;
//     }
//     free(map_content);     // Free the original map_content as it's no longer needed
//     map_content = NULL;
//     if (!validate_map(game))
//     {
//         free(game->map);  // Ensure to free the trimmed map if validation fails
//         return false;
//     }
//     return true;  // Return true if everything was successful
// }
