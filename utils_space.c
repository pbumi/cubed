/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:20:30 by pbumidan          #+#    #+#             */
/*   Updated: 2024/10/31 17:21:53 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cubed.h"


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
	if (!substr)
	{
		return NULL;	
	}
	return (substr);
}

bool remove_spaces(char **colors)
{
    size_t x = 0;
    while (colors[x])
    {
        char *new_str = remove_wspace(colors[x], 0);
        if (!new_str)
        {
            // Free all previously allocated memory before returning false
            while (x > 0)
            {
                x--;
                safe_free((void **)&colors[x]);
            }
            return false;
        }
        free(colors[x]);  // Free the old string
        colors[x] = new_str;  // Replace with the new string without spaces
        x++;
    }
    return true;
}