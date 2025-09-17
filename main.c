/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 20:21:30 by rheidary          #+#    #+#             */
/*   Updated: 2025/09/09 21:46:30 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	hook_handler(int keycode, t_game *game)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(game->mlx, game->win);
		exit(0);
	}
	game->key_pressed = keycode;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (game->key_pressed == keycode)
		game->key_pressed = 0;
	return (0);
}

void	init_player(t_game *game)
{
	game->player.x = 0;
	game->player.y = 0;
	game->player.alive = 1;
	game->key_pressed = 0;
}

void	move_player(int keycode, t_game *game)
{
	if (keycode == 119)      // W
		game->player.y--;
	else if (keycode == 115) // S
		game->player.y++;
	else if (keycode == 97)  // A
		game->player.x--;
	else if (keycode == 100) // D
		game->player.x++;
}

int	game_loop(t_game *game)
{
    if (game->key_pressed)
	{
        move_player(game->key_pressed, game);
	}
	mlx_put_image_to_window(
        game->mlx,
        game->win,
        game->player_img,
        game->player.x * game->player_w, // multiply by sprite size if using a grid
        game->player.y * game->player_h
    );
	return (0);
}

int	main(void)
{
	t_game		game;
	
	game.mlx = mlx_init();
	init_player(&game);
	game.win = mlx_new_window(game.mlx, 1920, 1080, "so_long");
	mlx_hook(game.win, 2, 1L<<0, hook_handler, &game);
	mlx_hook(game.win, 3, 1L<<1, key_release, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	game.player_img = mlx_xpm_file_to_image(game.mlx, "xpm_files/closed_exit.xpm",
				&game.player_w, &game.player_h);
	if (!game.player_img)
	{
    	write(2, "Failed to load player.xpm\n", 28);
    	return (1);
	}
	mlx_loop(game.mlx);
}