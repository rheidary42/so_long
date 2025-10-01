/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 20:21:30 by rheidary          #+#    #+#             */
/*   Updated: 2025/09/30 14:15:02 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static	int	moves = 0;

void	move_player(int keycode, t_game *game)
{
	long long	current_time;
	int next_x;
	int next_y;

	next_x = game->player.x;
	next_y = game->player.y;
	current_time = time_in_ms();
	if (current_time - game->last_move > game->move_cooldown && keycode_valid(keycode, game))
	{
		if (keycode == 119)      // W
			next_y--;
		else if (keycode == 115) // S
			next_y++;
		else if (keycode == 97)  // A
			next_x--;
		else if (keycode == 100) // D
			next_x++;
		if (game->map.buffer[next_y * (game->map.width + 1) + next_x] != '1')
		{
			game->player.x = next_x;
			game->player.y = next_y;
			ft_printf("Moves: %d\n", ++moves);
			game->last_move = current_time;
		}
	}
}

void	*correct_wall(t_game *game, int x, int y)
{
	if (x == 0 && y == 0)
		return (game->xpm.corner_ul);
	if (x == game->map.width - 1 && y == 0)
		return (game->xpm.corner_ur);
	if (x == 0 && y == game->map.height - 1)
		return (game->xpm.corner_dl);
	if (x == game->map.width - 1 && y == game->map.height - 1)
	{
		game->walls_rendered = 1;
		return (game->xpm.corner_dr);
	}
	if (y == 0)
		return (game->xpm.wall_up);
	if (y == game->map.height - 1)
		return (game->xpm.wall_down);
	if (x == 0)
		return (game->xpm.wall_left);
	if (x == game->map.width - 1)
		return (game->xpm.wall_right);
	else
		return (game->xpm.wall);
}

void	render_tile(t_game *game, char tile, int x, int y)
{
	if (tile == '1' && !(x == game->player.x && y == game->player.y))
	{
		if (y == 0 && game->walls_rendered && (x == 1 || x == 2 || x == 3))
			return ;
		else
			mlx_put_image_to_window(game->mlx, game->win, correct_wall(game, x, y), x * game->xpm.sprite_w, y * game->xpm.sprite_h);
	}
	if (tile == '0' && !(x == game->player.x && y == game->player.y) && !(x == game->enemy.x && y == game->enemy.y))
		mlx_put_image_to_window(game->mlx, game->win, game->xpm.floor, x * game->xpm.sprite_w, y * game->xpm.sprite_h);
	if (tile == 'E' && !game->exit_open && !(x == game->player.x && y == game->player.y) && !(x == game->enemy.x && y == game->enemy.y))
		mlx_put_image_to_window(game->mlx, game->win, game->xpm.closed_exit, x * game->xpm.sprite_w, y * game->xpm.sprite_h);
	else if (tile == 'E' && game->exit_open && !(x == game->player.x && y == game->player.y) && !(x == game->enemy.x && y == game->enemy.y))
		mlx_put_image_to_window(game->mlx, game->win, game->xpm.open_exit, x * game->xpm.sprite_w, y * game->xpm.sprite_h);
	if (tile == 'C' && !(x == game->player.x && y == game->player.y) && !(x == game->enemy.x && y == game->enemy.y))
		mlx_put_image_to_window(game->mlx, game->win, game->xpm.collectible, x * game->xpm.sprite_w, y * game->xpm.sprite_h);
}

void	render_map(t_game *game)
{
	static	int ft = 1;
	int i;
	int y;
	int x;
	
	i = -1;
	y = -1;
	if (ft == 1)
	{
		ft = 0;
		mlx_put_image_to_window(game->mlx, game->win, game->xpm.floor, game->player.x * game->xpm.sprite_w, game->player.y * game->xpm.sprite_h);
		if (game->enemy.enemy_count)
			mlx_put_image_to_window(game->mlx, game->win, game->xpm.enemy_front, game->enemy.x * game->xpm.sprite_w, game->enemy.y * game->xpm.sprite_h);
	}
	while (++y < game->map.height)
	{
		x = -1;
		while (++x < game->map.width)
			render_tile(game, game->map.buffer[++i], x, y);
		i++;	
	}
}

void	render_player(t_game *game)
{
	int	x;
	int	y;
	
	x = game->player.x * game->xpm.sprite_w;
	y = game->player.y * game->xpm.sprite_h;
	if (game->last_key == 119)
		mlx_put_image_to_window(game->mlx, game->win, game->xpm.isaac_back, x, y);
	if (game->last_key == 115 || game->last_key == 0)
		mlx_put_image_to_window(game->mlx, game->win, game->xpm.isaac_front, x, y);
	if (game->last_key == 97)
		mlx_put_image_to_window(game->mlx, game->win, game->xpm.isaac_left, x, y);
	if (game->last_key == 100)
		mlx_put_image_to_window(game->mlx, game->win, game->xpm.isaac_right, x, y);
}

void	handle_collectibles(t_game *game)
{
	if (game->map.buffer[game->player.y * (game->map.width + 1) + game->player.x] == 'C')
	{
		game->map.buffer[game->player.y * (game->map.width + 1) + game->player.x] = '0';
		game->map.collectible_count--;
		if (game->map.collectible_count == 0)
			game->exit_open = 1;
	}
}

void	check_end(t_game *game)
{
	if (game->player.x == game->enemy.x && game->player.y == game->enemy.y)
	{
		free_xpms(game);
		mlx_destroy_window(game->mlx, game->win);
		write (1, "You died, skill issue :(\n", 26);
		exit(0);
	}
	if (game->exit_open && game->map.buffer[game->player.y * (game->map.width + 1) + game->player.x] == 'E')
	{
	free_xpms(game);
	mlx_destroy_window(game->mlx, game->win);
	write (1, "You win, yippie! yippie! yippie!\n", 34);
	exit(0);
	}
}

void    render_moves(t_game *game)
{
    char    *str;

	mlx_put_image_to_window(game->mlx, game->win,
        game->xpm.wall_up, 1 * game->xpm.sprite_w, 0);
	mlx_put_image_to_window(game->mlx, game->win,
        game->xpm.wall_up, 2 * game->xpm.sprite_w, 0);
	mlx_put_image_to_window(game->mlx, game->win,
        game->xpm.wall_up, 3 * game->xpm.sprite_w, 0);
    str = ft_itoa(moves);
    mlx_string_put(game->mlx, game->win, 32, 20, 0xFFFFFF, "Moves: ");
	if (moves < 9999)
    	mlx_string_put(game->mlx, game->win, 102, 20, 0xFFFFFF, str);
	else
    	mlx_string_put(game->mlx, game->win, 102, 20, 0xFFFFFF, "A lot!");
	if (moves > 999999)
	{
		free_xpms;
		mlx_destroy_window(game->mlx, game->win);
		ft_printf("You moved too much");
		ft_printf(" and got arrested by the move police and died.\n");
		exit(0);
	}
    free(str);
}

void	render_enemy(t_game *game)
{
	int	x;
	int	y;
	
	if (!game->enemy.enemy_count)
		return ;
	x = game->enemy.x * game->xpm.sprite_w;
	y = game->enemy.y * game->xpm.sprite_h;
	if (game->enemy.direction == 119)
		mlx_put_image_to_window(game->mlx, game->win, game->xpm.enemy_back, x, y);
	if (game->enemy.direction == 115)
		mlx_put_image_to_window(game->mlx, game->win, game->xpm.enemy_front, x, y);
	if (game->enemy.direction == 97)
		mlx_put_image_to_window(game->mlx, game->win, game->xpm.enemy_left, x, y);
	if (game->enemy.direction == 100)
		mlx_put_image_to_window(game->mlx, game->win, game->xpm.enemy_right, x, y);
}

int	check_horizontal_los(t_game *game, int x, int y, int width)
{
	if (game->player.y != y)
		return (0);
	if (game->enemy.direction == 97 && game->player.x < x)
	{
		while (--x > game->player.x)
			if (game->map.buffer[y * width + x] == '1')
				return (0);
		return (1);
	}
	if (game->enemy.direction == 100 && game->player.x > x)
	{
		while (++x < game->player.x)
			if (game->map.buffer[y * width + x] == '1')
				return (0);
		return (1);
	}
	return (0);
}

int	check_vertical_los(t_game *game, int x, int y, int width)
{
	if (game->player.x != x)
		return (0);
	if (game->enemy.direction == 115 && game->player.y > y)
	{
		while (++y < game->player.y)
			if (game->map.buffer[y * width + x] == '1')
				return (0);
		return (1);
	}
	if (game->enemy.direction == 119 && game->player.y < y)
	{
		while (--y > game->player.y)
			if (game->map.buffer[y * width + x] == '1')
				return (0);
		return (1);
	}
	return (0);
}

void	in_line_of_sight(t_game *game, int x, int y)
{
	int	width;

	width = game->map.width + 1;
	if (check_horizontal_los(game, x, y, width) || check_vertical_los(game, x, y, width))
		game->enemy.mode = 1;
	else
		game->enemy.mode = 0;
	if (game->enemy.mode == 1)
		game->enemy.move_cooldown = 80;
	if (game->enemy.mode == 0)
		game->enemy.move_cooldown = 250;
}

void	enemy_wander(t_game *game, int *x, int *y)
{
	int	dir;
	int	width;

	dir = rand() % 4;
	if (dir == 0 && game->map.buffer[*y * (game->map.width + 1) + (*x - 1)] != '1')
	{
		*x -= 1;
		game->enemy.direction = 97;
	}
	else if (dir == 1 && game->map.buffer[*y * (game->map.width + 1) + (*x + 1)] != '1')
	{
		*x += 1;
		game->enemy.direction = 100;
	}
	else if (dir == 2 && game->map.buffer[(*y - 1) * (game->map.width + 1) + *x] != '1')
	{
		*y -= 1;
		game->enemy.direction = 119;
	}
	else if (dir == 3 && game->map.buffer[(*y + 1) * (game->map.width + 1) + *x] != '1')
	{
		*y += 1;
		game->enemy.direction = 115;
	}
}

void	enemy_chase(t_game *game, int *x, int *y)
{
	int	width;

	width = game->map.width + 1;
	if (*x < game->player.x && game->map.buffer[*y * width + (*x + 1)] != '1')
	{
		*x += 1;
		game->enemy.direction = 100;
	}
	else if (*x > game->player.x && game->map.buffer[*y * width + (*x - 1)] != '1')
	{
		*x -= 1;
		game->enemy.direction = 97;
	}
	else if (*y < game->player.y && game->map.buffer[(*y + 1) * width + *x] != '1')
	{
		*y += 1;
		game->enemy.direction = 115;
	}
	else if (*y > game->player.y && game->map.buffer[(*y - 1) * width + *x] != '1')
	{
		*y -= 1;
		game->enemy.direction = 119;
	}
}

// mode 0 = random wandering
// mode 1 = chase player
void	move_enemy(t_game *game)
{
	int	current_time;
	int next_x;
	int next_y;

	next_x = game->enemy.x;
	next_y = game->enemy.y;
	current_time = time_in_ms();
	if (current_time - game->enemy.last_move > game->enemy.move_cooldown)
	{
		in_line_of_sight(game, game->enemy.x, game->enemy.y);
		if (game->enemy.mode == 0)
			enemy_wander(game, &next_x, &next_y);
		if (game->enemy.mode == 1)
			enemy_chase(game, &next_x, &next_y);
		if (game->map.buffer[next_y * (game->map.width + 1) + next_x] != '1')
		{
			game->enemy.x = next_x;
			game->enemy.y = next_y;
			game->enemy.last_move = current_time;
		}
	}
}

// The game loop handles the core updates each frame:
// 1. Render the map (optionally split into static walls and dynamic elements)
// 2. Process player movement and increment the move counter if the tile is walkable
// 3. Update the map when collectibles are picked up (replace with floor or open the exit)
int	game_loop(t_game *game)
{
	if (game->key_pressed)
		move_player(game->key_pressed, game);
	move_enemy(game);
	render_moves(game);
	render_map(game);
	render_enemy(game);
	render_player(game);
	handle_collectibles(game);
	check_end(game);
	return (1);
}

int	main(int argc, char **argv)
{
	t_game		game;
	
	if (argc != 2)
	{
		write (2, "Invalid amount of Arguments\n", 28);
		return (-1);
	}
	game.mlx = mlx_init();
	init_data(&game);
	init_map(&game, argv[1]);
	init_xpms(&game);
	check_xpms(&game);
	game.win = mlx_new_window(game.mlx, game.map.width * game.xpm.sprite_w, game.map.height * game.xpm.sprite_h, "so_long");
	mlx_hook(game.win, 3, 1L<<1, key_release, &game);
	mlx_hook(game.win, 2, 1L<<0, hook_handler, &game);
	mlx_hook(game.win, 17, 0, x_handler, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
}
