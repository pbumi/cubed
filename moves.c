/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 17:46:09 by pbumidan          #+#    #+#             */
/*   Updated: 2024/12/07 17:48:18 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void	move_left(t_game *game)
{
	int	x;
	int	y;

	if (wall_collision(game, game->player_x - MOVE, game->player_y, LEFT))
		return ;
	game->player_x -= MOVE;
	move_player_images(game, LEFT);
	game->steps += 1;
	x = game->player_x / TILE;
	y = game->player_y / TILE;
	if (game->map.arr[y][x] == 'E' && game->colls == 0)
	{
		game->exit_reached = true;
		game->over = true;
	}
	print_moves(game);
}

void	move_right(t_game *game)
{
	int	x;
	int	y;

	if (wall_collision(game, game->player_x + PLAYER, game->player_y, RIGHT))
		return ;
	game->player_x += MOVE;
	move_player_images(game, RIGHT);
	game->steps += 1;
	x = game->player_x / TILE;
	y = game->player_y / TILE;
	print_moves(game);
}

void	move_up(t_game *game)
{
	int	x;
	int	y;

	if (wall_collision(game, game->player_x, game->player_y - MOVE, UP))
		return ;
	game->player_y -= MOVE;
	move_player_images(game, UP);
	game->steps += 1;
	x = game->player_x / TILE;
	y = game->player_y / TILE;
	print_moves(game);
}

void	move_down(t_game *game)
{
	int	x;
	int	y;

	if (wall_collision(game, game->player_x, game->player_y + PLAYER, DOWN))
		return ;
	game->player_y += MOVE;
	move_player_images(game, DOWN);
	game->steps += 1;
	x = game->player_x / TILE;
	y = game->player_y / TILE;
	print_moves(game);
}