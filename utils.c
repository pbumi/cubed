/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:25:27 by pbumidan          #+#    #+#             */
/*   Updated: 2024/10/31 17:25:52 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cubed.h"

void	errorhandler(t_main *game, char *msg, bool fatal)
{
	if (game)
	{
		free_struct(game);
	}	
	if (msg)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putendl_fd(msg, 2);	
	}
	if (fatal)
	{
		exit(1);
	}
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