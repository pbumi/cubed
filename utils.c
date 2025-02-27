/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:16:51 by pbumidan          #+#    #+#             */
/*   Updated: 2025/01/10 19:56:48 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

float	nor_angle(float angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

int	unit_circle(float angle, char c)
{
	if (c == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (1);
	}
	else if (c == 'y')
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
			return (1);
	}
	return (0);
}

int	get_pixeldata(int c)
{
	return (((c >> 24) & 0xFF) | ((c >> 8) & 0xFF00)
		| ((c << 8) & 0xFF0000) | ((c << 24) & 0xFF000000));
}

char	*remove_wspace(char *line, int start)
{
	char	*substr;
	int		x;
	int		end;

	substr = NULL;
	x = start;
	while (line[x] && (line[x] == ' ' || (line[x] >= 9 && line[x] <= 13)))
	{
		x++;
	}
	end = ft_strlen(line) - 1;
	while (end > x && (line[end] == ' ' || (line[end] >= 9 && line[end] <= 13)))
	{
		end--;
	}
	substr = ft_substr(line, x, (end - x) + 1);
	if (!substr)
	{
		return (NULL);
	}
	return (substr);
}

void	error_msg(char *msg)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
}
