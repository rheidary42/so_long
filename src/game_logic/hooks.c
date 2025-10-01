/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 21:41:00 by rheidary          #+#    #+#             */
/*   Updated: 2025/09/29 21:43:16 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_release(int keycode, t_game *game)
{
    
    if (game->key_pressed == keycode)
        game->key_pressed = 0;
    return (0);
}

int	hook_handler(int keycode, t_game *game)
{
	if (keycode == 65307)
	{
		free_xpms(game);
		mlx_destroy_window(game->mlx, game->win);
		exit(0);
	}
	game->key_pressed = keycode;
	return (0);
}

int	x_handler(t_game *game)
{
	free_xpms(game);
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
	return (0);
}
