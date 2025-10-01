/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 00:38:41 by rheidary          #+#    #+#             */
/*   Updated: 2025/09/30 03:30:41 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_data(t_game *game)
{
	game->player.alive = 1;
	game->key_pressed = 0;
	game->last_key = 0;
	game->move_cooldown = 150; // value in milliseconds
	game->last_move = 0;
	game->exit_open = 0;
	game->walls_rendered = 0;
	game->map.collectible_count = 0;
	game->enemy.enemy_count = 0;
	game->enemy.direction = 115;
	game->enemy.mode = 0;
	game->enemy.move_cooldown = 0;
	game->enemy.last_move = time_in_ms();
}

long long	time_in_ms(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((long long)tv.tv_sec * 1000 + (long long)tv.tv_usec / 1000LL);
}

int track_element_pos(t_game *game, int element_pos, int flag)
{
	if (flag == 0)
	{
    	game->player.x = element_pos % (game->map.width + 1);
    	game->player.y = element_pos / (game->map.width + 1);
		game->map.buffer[element_pos] = '0';
	}
	if (flag == 1)
	{
		game->enemy.x = element_pos % (game->map.width + 1);
    	game->enemy.y = element_pos / (game->map.width + 1);
		game->map.buffer[element_pos] = '0';
	}
    return (1);
}

int	keycode_valid(int keycode, t_game *game)
{
	if (keycode == 119 || keycode == 115 || keycode == 97 || keycode == 100)
	{
		game->last_key = keycode;
		return (1);
	}
	return (0);
}

int	random_direction()
{
	int direction[4] = {119, 115, 97, 100};

	return (direction[rand() % 4]);
}