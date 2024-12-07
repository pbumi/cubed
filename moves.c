/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 17:46:09 by pbumidan          #+#    #+#             */
/*   Updated: 2024/12/07 22:45:46 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

// Function to check if there's a wall ('1') at a specific position
bool wall_collision(t_main *game, double x, double y)
{
    // Ensure that x and y are within the bounds of the map
    int map_x = (int)x;
    int map_y = (int)y;

    printf("Checking collision at: (%d, %d)\n", map_x, map_y); // Debugging print

    // Ensure the x and y coordinates fall within the map's bounds
    if (map_x < 0 || map_x >= game->w_map[map_y] || map_y < 0 || map_y >= game->h_map)
    {
        printf("Out of bounds collision detected!\n");  // Debugging print
        return true; // Out of bounds treated as a collision
    }

    // Check if there's a wall ('1') at the given position
    if (game->map_arr[map_y][map_x] == '1')
    {
        printf("Wall collision detected at: (%d, %d)\n", map_x, map_y); // Debugging print
        return true; // Wall collision found
    }

    return false; // No wall
}

// Function to check if there's a collision at the player's future position
bool check_player_collision(t_main *game, double x, double y)
{
    // Debugging print to see the future position being checked
    printf("Checking future position: (%f, %f)\n", x, y);

    // Check the four corners of the player's bounding box
    if (     // Center
        wall_collision(game, x + PLAYER_SPEED, y) || // Right side
        wall_collision(game, x - PLAYER_SPEED, y) || // Left side
        wall_collision(game, x, y + PLAYER_SPEED) || // Down side
        wall_collision(game, x, y - PLAYER_SPEED))   // Up side
    {
        printf("Collision detected while checking position: (%f, %f)\n", x, y); // Debugging print
        return true; // Collision detected
    }

    return false; // No collision
}

// Move down
void move_down(t_main *game)
{
    printf("s key pressed\n");

    double next_x = game->p_x;
    double next_y = game->p_y + PLAYER_SPEED;

    // Check if the new position is valid (no wall in the path)
    if (!check_player_collision(game, next_x, next_y)) {
        game->p_y = next_y; // Move player down
        printf("Updated position: (%f, %f)\n", game->p_x, game->p_y);
    } else {
        printf("Collision detected while moving down.\n");
    }
}

// Move up
void move_up(t_main *game)
{
    printf("w key pressed\n");

    double prev_x = game->p_x;
    double prev_y = game->p_y - PLAYER_SPEED;

    // Check if the new position is valid (no wall in the path)
    if (!check_player_collision(game, prev_x, prev_y)) {
        game->p_y = prev_y; // Move player up
        printf("Updated position: (%f, %f)\n", game->p_x, game->p_y);
    } else {
        printf("Collision detected while moving up.\n");
    }
}

// Move left
void move_left(t_main *game)
{
    printf("a key pressed\n");

    double left_x = game->p_x - PLAYER_SPEED;
    double left_y = game->p_y;

    // Check if the new position is valid (no wall in the path)
    if (!check_player_collision(game, left_x, left_y)) {
        game->p_x = left_x; // Move player left
        printf("Updated position: (%f, %f)\n", game->p_x, game->p_y);
    } else {
        printf("Collision detected while moving left.\n");
    }
}

// Move right
void move_right(t_main *game)
{
    printf("d key pressed\n");

    double right_x = game->p_x + PLAYER_SPEED;
    double right_y = game->p_y;

    // Check if the new position is valid (no wall in the path)
    if (!check_player_collision(game, right_x, right_y)) {
        game->p_x = right_x; // Move player right
        printf("Updated position: (%f, %f)\n", game->p_x, game->p_y);
    } else {
        printf("Collision detected while moving right.\n");
    }
}

// bool wall_collision(t_main *game, double x, double y)
// {
//     // Ensure that x and y are within the bounds of the map
//     int map_x = (int)x;
//     int map_y = (int)y;

//     // Check if the x and y coordinates fall within the map's bounds
//     if (map_x < 0 || map_x >= game->w_map[map_y] || map_y < 0 || map_y >= game->h_map)
//         return true; // Out of bounds is treated as a collision

//     // Check if there's a wall ('1') at the given position
//     if (game->map_arr[map_y][map_x] == '1')
//         return true; // There is a wall, return true

//     return false; // No wall, return false
// }

// void move_down(t_main *game)
// {
//     printf("s key pressed\n");

//     double next_x = game->p_x;
//     double next_y = game->p_y + PLAYER_SPEED;  // Move down along y-axis

//     // Check if the new position is a valid move (no wall at next position)
//     if (!wall_collision(game, next_x, next_y)) {
//         game->p_y = next_y;  // Update position
//         printf("Updated position: (%f, %f)\n", game->p_x, game->p_y);
//     }
// }

// void move_up(t_main *game)
// {
//     printf("w key pressed\n");

//     double prev_x = game->p_x;
//     double prev_y = game->p_y - PLAYER_SPEED;  // Move up along y-axis

//     // Check if the new position is a valid move (no wall at prev position)
//     if (!wall_collision(game, prev_x, prev_y)) {
//         game->p_y = prev_y;  // Update position
//         printf("Updated position: (%f, %f)\n", game->p_x, game->p_y);
//     }
// }

// void move_left(t_main *game)
// {
//     printf("a key pressed\n");

//     double left_x = game->p_x - PLAYER_SPEED;  // Move left along x-axis
//     double left_y = game->p_y;

//     // Check if the new position is a valid move (no wall at left position)
//     if (!wall_collision(game, left_x, left_y)) {
//         game->p_x = left_x;  // Update position
//         printf("Updated position: (%f, %f)\n", game->p_x, game->p_y);
//     }
// }

// void move_right(t_main *game)
// {
//     printf("d key pressed\n");

//     double right_x = game->p_x + PLAYER_SPEED;  // Move right along x-axis
//     double right_y = game->p_y;

//     // Check if the new position is a valid move (no wall at right position)
//     if (!wall_collision(game, right_x, right_y)) {
//         game->p_x = right_x;  // Update position
//         printf("Updated position: (%f, %f)\n", game->p_x, game->p_y);
//     }
// }



// void move_down(t_main *game)
// {
//     printf("w key pressed\n");

//     double next_x = game->p_x;
//     double next_y = game->p_y + PLAYER_SPEED;  // Move down along y-axis

//     printf("Next position: (%f, %f)\n", next_x, next_y);
//     printf("map_arr value at next_x: %c\n", game->map_arr[(int)next_x][(int)game->p_y]);
//     printf("map_arr value at next_y: %c\n", game->map_arr[(int)game->p_x][(int)next_y]);

//     // Check if the new position is a valid move (open space, '0')
//     if (game->map_arr[(int)(next_x)][(int)(game->p_y)] == '0')
//         game->p_x = next_x;
//     if (game->map_arr[(int)(game->p_x)][(int)(next_y)] == '0')
//         game->p_y = next_y;

//     printf("Updated position: (%f, %f)\n", game->p_x, game->p_y);
// }

// void move_up(t_main *game)
// {
//     printf("s key pressed\n");

//     double prev_x = game->p_x;
//     double prev_y = game->p_y - PLAYER_SPEED;  // Move up along y-axis

//     // Check if the new position is a valid move (open space, '0')
//     if (game->map_arr[(int)(prev_x)][(int)(game->p_y)] == '0')
//         game->p_x = prev_x;
//     if (game->map_arr[(int)(game->p_x)][(int)(prev_y)] == '0')
//         game->p_y = prev_y;
// }

// void move_left(t_main *game)
// {
//     printf("a key pressed\n");

//     double left_x = game->p_x - PLAYER_SPEED;  // Move left along x-axis
//     double left_y = game->p_y;

//     // Check if the new position is a valid move (open space, '0')
//     if (game->map_arr[(int)(left_x)][(int)(game->p_y)] == '0')
//         game->p_x = left_x;
//     if (game->map_arr[(int)(game->p_x)][(int)(left_y)] == '0')
//         game->p_y = left_y;
// }

// void move_right(t_main *game)
// {
//     printf("d key pressed\n");

//     double right_x = game->p_x + PLAYER_SPEED;  // Move right along x-axis
//     double right_y = game->p_y;

//     // Check if the new position is a valid move (open space, '0')
//     if (game->map_arr[(int)(right_x)][(int)(game->p_y)] == '0')
//         game->p_x = right_x;
//     if (game->map_arr[(int)(game->p_x)][(int)(right_y)] == '0')
//         game->p_y = right_y;
// }

//__________________________________________________________________________________________

// bool wall_collision(t_main *game, double x, double y, int direction)
// {
//     int startX = 0, startY = 0, endX = 0, endY = 0;  // Initialize all variables

//     // Calculate the edges of the player based on the movement direction
//     if (direction == LEFT)
//     {
//         startX = (x - PLAYER_TILE) / TILE;
//         endX = x / TILE;
//         startY = y / TILE;
//         endY = (y + PLAYER_TILE - 1) / TILE;
//     }
//     else if (direction == RIGHT)
//     {
//         startX = (x + PLAYER_TILE) / TILE;
//         endX = (x + PLAYER_TILE) / TILE; // No need for `+ D`, just check the edge.
//         startY = y / TILE;
//         endY = (y + PLAYER_TILE - 1) / TILE;
//     }
//     else if (direction == UP)
//     {
//         startX = x / TILE;
//         endX = (x + PLAYER_TILE - 1) / TILE;
//         startY = (y - PLAYER_TILE) / TILE;
//         endY = (y - PLAYER_TILE + D) / TILE;
//     }
//     else if (direction == DOWN)
//     {
//         startX = x / TILE;
//         endX = (x + PLAYER_TILE - 1) / TILE;
//         startY = (y + PLAYER_TILE) / TILE;
//         endY = (y + PLAYER_TILE) / TILE; // Only check the current tile for DOWN.
//     }

//     // Now we know that all variables are initialized
//     for (int checkY = startY; checkY <= endY; checkY++)
//     {
//         for (int checkX = startX; checkX <= endX; checkX++)
//         {
//             // Check if there's a wall ('1') at any of the tiles the player is occupying
//             if (game->map_arr_arr[checkY][checkX] == '1')  // Collision check
//                 return true;  // Collision with wall
//         }
//     }

//     return false;  // No collision
// }

// void move_left(t_main *game)
// {
//     if (wall_collision(game, game->p_x - MOVE, game->p_y, LEFT))
//         return;  // Prevent movement if there is a wall
//     game->p_x -= MOVE;  // Move the player to the left
//     printf("left\n");
// 	printf("y %f x %f\n", game->p_y, game->p_x);
// }

// void move_right(t_main *game)
// {
//     if (wall_collision(game, game->p_x + PLAYER_TILE, game->p_y, RIGHT))
//         return;  // Prevent movement if there is a wall
//     game->p_x += MOVE;  // Move the player to the right
//     printf("right\n");
// 	printf("y %f x %f\n", game->p_y, game->p_x);
// }

// void move_up(t_main *game)
// {
//     if (wall_collision(game, game->p_x, game->p_y - MOVE, UP))
//         return;  // Prevent movement if there is a wall
//     game->p_y -= MOVE;  // Move the player up
//     printf("up\n");
// 	printf("y %f x %f\n", game->p_y, game->p_x);
// }

// void move_down(t_main *game)
// {
//     if (wall_collision(game, game->p_x, game->p_y + PLAYER_TILE, DOWN))
//         return;  // Prevent movement if there is a wall
//     game->p_y += MOVE;  // Move the player down
//     printf("down\n");
// 	printf("y %f x %f\n", game->p_y, game->p_x);
// }

void	key_hook_slow(mlx_key_data_t keydata, void *param)
{
	t_main	*game;

	game = (t_main *)param;

	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		mlx_close_window(game->mlx_ptr);
	else if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_A))
		move_left(game);
	else if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_D))
		move_right(game);
	else if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_W))
		move_up(game);
	else if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_S))
		move_down(game);
}
