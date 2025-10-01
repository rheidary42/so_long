/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 20:14:28 by rheidary          #+#    #+#             */
/*   Updated: 2025/09/30 03:14:21 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

//     ╱|、
//   (˚ˎ 。7
//    |、˜〵
//   じしˍ,)ノ
// 
//           I cast "Understand Shitty Code"!
//  ∧＿∧
// ( ･ω･)つ━☆・*。
// ⊂　 ノ 　　　・゜
// しーＪ　　　°。+ *´¨* ☆
//
#include "libs/libft/libft.h"
#include "libs/ft_printf/libftprintf.h"

#include <stdio.h>

#include <mlx.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <fcntl.h>

// To be changed
#define MAX_MAP_HEIGHT 25
#define MAX_MAP_WIDTH 30

typedef struct s_xpm
{
	int			sprite_w;
	int			sprite_h;
	void		*floor;
	void		*wall;
	void		*wall_down;
	void		*wall_left;
	void		*wall_right;
	void		*wall_up;
	void		*corner_dl;
	void		*corner_dr;
	void		*corner_ul;
	void		*corner_ur;
	void		*closed_exit;
	void		*open_exit;
	int			coll_w;
	int			coll_h;
	void		*collectible;
	void		*isaac_back;
	void		*isaac_front;
	void		*isaac_left;
	void		*isaac_right;
	void		*enemy_back;
	void		*enemy_front;
	void		*enemy_left;
	void		*enemy_right;
}	t_xpm;

typedef struct s_map
{
	char		buffer[MAX_MAP_HEIGHT  * (MAX_MAP_WIDTH + 1)];
	int			width;
	int			height;
	int			collectible_count;
}	t_map;

typedef struct s_player
{
	int	x;
	int	y;
	int	alive;
}	t_player;

typedef struct s_enemy
{
	int	x;
	int	y;
	int	move_cooldown;
	int	last_move;
	int	enemy_count;
	int	mode;
	int	direction;
}	t_enemy;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_player	player;
	t_xpm		xpm;
	t_map		map;
	t_enemy		enemy;
	int			key_pressed;
	int			last_key;
	int			move_cooldown;
	long long	last_move;
	int			exit_open;
	int			walls_rendered;
}	t_game;

// MAP_VALIDATION
// map_validation.c
int		init_map(t_game *game, char *map);
void	calculate_map_dimensions(t_game *game, int len);
void	validate_map(t_game *game, ssize_t len);
int 	check_map_elements(t_game *game, ssize_t len);
int 	check_border(t_game *game, int width, int height, char *map);
// flood_fill.c
int 	flood_fill(t_game *game);
void	dfs_fill(t_game *game, int idx, int *visited);

// HELPERS
// helper1.c
void		init_data(t_game *game);
long long	time_in_ms(void);
int 		track_element_pos(t_game *game, int element_pos, int flag);
int			keycode_valid(int keycode, t_game *game);

// XPM_HANDLING
// xpm_init.c
void    init_xpms(t_game *game);
void	init_xpms2(t_game *game);
void	check_xpms(t_game *game);
void	free_xpms(t_game *game);
void	free_xpms2(t_game *game);

// GAME_LOGIC
// hooks.c
int	key_release(int keycode, t_game *game);
int	hook_handler(int keycode, t_game *game);
int	x_handler(t_game *game);
#endif