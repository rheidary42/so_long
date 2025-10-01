/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 00:41:19 by rheidary          #+#    #+#             */
/*   Updated: 2025/09/30 00:57:50 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void    init_xpms(t_game *game)
{
	game->xpm.floor = mlx_xpm_file_to_image(game->mlx, "xpm_files/floor.xpm",
				&game->xpm.sprite_w, &game->xpm.sprite_h);
	game->xpm.wall = mlx_xpm_file_to_image(game->mlx, "xpm_files/wall.xpm",
				&game->xpm.sprite_w, &game->xpm.sprite_w);
	game->xpm.wall_down = mlx_xpm_file_to_image(game->mlx, "xpm_files/wall_down.xpm",
				&game->xpm.sprite_w, &game->xpm.sprite_h);
	game->xpm.wall_left = mlx_xpm_file_to_image(game->mlx, "xpm_files/wall_left.xpm",
				&game->xpm.sprite_w, &game->xpm.sprite_h);
	game->xpm.wall_right = mlx_xpm_file_to_image(game->mlx, "xpm_files/wall_right.xpm",
				&game->xpm.sprite_w, &game->xpm.sprite_h);
	game->xpm.wall_up = mlx_xpm_file_to_image(game->mlx, "xpm_files/wall_up.xpm",
				&game->xpm.sprite_w, &game->xpm.sprite_h);
	game->xpm.corner_dl = mlx_xpm_file_to_image(game->mlx, "xpm_files/corner_down_left.xpm",
				&game->xpm.sprite_w, &game->xpm.sprite_h);
	game->xpm.corner_dr = mlx_xpm_file_to_image(game->mlx, "xpm_files/corner_down_right.xpm",
				&game->xpm.sprite_w, &game->xpm.sprite_h);
	game->xpm.corner_ul = mlx_xpm_file_to_image(game->mlx, "xpm_files/corner_up_left.xpm",
				&game->xpm.sprite_w, &game->xpm.sprite_h);
	game->xpm.corner_ur = mlx_xpm_file_to_image(game->mlx, "xpm_files/corner_up_right.xpm",
				&game->xpm.sprite_w, &game->xpm.sprite_h);
	game->xpm.closed_exit = mlx_xpm_file_to_image(game->mlx, "xpm_files/closed_exit.xpm",
				&game->xpm.sprite_w, &game->xpm.sprite_h);
	game->xpm.open_exit = mlx_xpm_file_to_image(game->mlx, "xpm_files/open_exit.xpm",
				&game->xpm.sprite_w, &game->xpm.sprite_h);
	init_xpms2(game);
}

void	init_xpms2(t_game *game)
{
	game->xpm.collectible = mlx_xpm_file_to_image(game->mlx, "xpm_files/collectible.xpm",
				&game->xpm.sprite_w, &game->xpm.sprite_h);
	game->xpm.isaac_back = mlx_xpm_file_to_image(game->mlx, "xpm_files/isaac_back.xpm",
				&game->xpm.sprite_w, &game->xpm.sprite_h);
	game->xpm.isaac_front = mlx_xpm_file_to_image(game->mlx, "xpm_files/isaac_front.xpm",
				&game->xpm.sprite_w, &game->xpm.sprite_h);
	game->xpm.isaac_left = mlx_xpm_file_to_image(game->mlx, "xpm_files/isaac_left.xpm",
				&game->xpm.sprite_w, &game->xpm.sprite_h);
	game->xpm.isaac_right = mlx_xpm_file_to_image(game->mlx, "xpm_files/isaac_right.xpm",
				&game->xpm.sprite_w, &game->xpm.sprite_h);
	game->xpm.enemy_back = mlx_xpm_file_to_image(game->mlx, "xpm_files/enemy_back.xpm",
				&game->xpm.sprite_w, &game->xpm.sprite_h);
	game->xpm.enemy_front = mlx_xpm_file_to_image(game->mlx, "xpm_files/enemy_front.xpm",
				&game->xpm.sprite_w, &game->xpm.sprite_h);
	game->xpm.enemy_left = mlx_xpm_file_to_image(game->mlx, "xpm_files/enemy_left.xpm",
				&game->xpm.sprite_w, &game->xpm.sprite_h);
	game->xpm.enemy_right = mlx_xpm_file_to_image(game->mlx, "xpm_files/enemy_right.xpm",
				&game->xpm.sprite_w, &game->xpm.sprite_h);
}

void	check_xpms(t_game *game)
{
	if (!game->xpm.enemy_back)     printf("Missing enemy_back.xpm\n");
    if (!game->xpm.enemy_front)    printf("Missing enemy_front.xpm\n");
    if (!game->xpm.enemy_left)     printf("Missing enemy_left.xpm\n");
    if (!game->xpm.enemy_right)    printf("Missing enemy_right.xpm\n");
	if (!game->xpm.floor || !game->xpm.wall_down
 	|| !game->xpm.wall_left || !game->xpm.wall_right
 	|| !game->xpm.wall_up || !game->xpm.corner_dl
 	|| !game->xpm.corner_dr || !game->xpm.corner_ul
 	|| !game->xpm.corner_ur || !game->xpm.closed_exit
 	|| !game->xpm.open_exit || !game->xpm.wall
	|| !game->xpm.collectible
	|| !game->xpm.isaac_front || !game->xpm.isaac_left
	|| !game->xpm.isaac_right || !game->xpm.isaac_back
	|| !game->xpm.enemy_back || !game->xpm.enemy_front
	|| !game->xpm.enemy_left || !game->xpm.enemy_right)
	{
		write(2, "Failed to load xpms\n", 22);
		free_xpms(game);
		exit (1);
	}
}

void	free_xpms(t_game *game)
{
	if (!game->mlx)
        return ;
	if  (game->xpm.wall)
		mlx_destroy_image(game->mlx, game->xpm.wall);
	if (game->xpm.wall_down)
		mlx_destroy_image(game->mlx, game->xpm.wall_down);
	if (game->xpm.wall_left)
		mlx_destroy_image(game->mlx, game->xpm.wall_left);
	if (game->xpm.wall_right)
		mlx_destroy_image(game->mlx, game->xpm.wall_right);
	if (game->xpm.wall_up)
		mlx_destroy_image(game->mlx, game->xpm.wall_up);
	if (game->xpm.corner_dl)
		mlx_destroy_image(game->mlx, game->xpm.corner_dl);
	if (game->xpm.corner_dr)
		mlx_destroy_image(game->mlx, game->xpm.corner_dr);
	if (game->xpm.corner_ul)
		mlx_destroy_image(game->mlx, game->xpm.corner_ul);
	if (game->xpm.corner_ur)
		mlx_destroy_image(game->mlx, game->xpm.corner_ur);
	if (game->xpm.closed_exit)
		mlx_destroy_image(game->mlx, game->xpm.closed_exit);
	if (game->xpm.open_exit)
		mlx_destroy_image(game->mlx, game->xpm.open_exit);
	free_xpms2(game);
}

void	free_xpms2(t_game *game)
{
	if (game->xpm.collectible)
		mlx_destroy_image(game->mlx, game->xpm.collectible);
	if (game->xpm.floor)
		mlx_destroy_image(game->mlx, game->xpm.floor);
	if (game->xpm.isaac_back)
		mlx_destroy_image(game->mlx, game->xpm.isaac_back);
	if (game->xpm.isaac_front)
		mlx_destroy_image(game->mlx, game->xpm.isaac_front);
	if (game->xpm.isaac_left)
		mlx_destroy_image(game->mlx, game->xpm.isaac_left);
	if (game->xpm.isaac_right)
		mlx_destroy_image(game->mlx, game->xpm.isaac_right);
	if (game->xpm.enemy_back)
		mlx_destroy_image(game->mlx, game->xpm.enemy_back);
	if (game->xpm.enemy_front)
		mlx_destroy_image(game->mlx, game->xpm.enemy_front);
	if (game->xpm.enemy_left)
		mlx_destroy_image(game->mlx, game->xpm.enemy_left);
	if (game->xpm.enemy_right)
		mlx_destroy_image(game->mlx, game->xpm.enemy_right);
}
