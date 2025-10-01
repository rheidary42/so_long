/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:16:36 by rheidary          #+#    #+#             */
/*   Updated: 2025/09/30 03:31:11 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	init_map(t_game *game, char *map)
{
	int			fd;
	ssize_t		len;

	fd = open(map, O_RDONLY);
	if (fd < 0)
    {
        write(2, "Map not found\n", 15);
        exit(1);
    }
	len = read(fd, game->map.buffer, (MAX_MAP_HEIGHT + 1) * MAX_MAP_WIDTH);
	close(fd);
	if (len < 0)
		return (0);
	if (len <= (ssize_t)((MAX_MAP_HEIGHT + 1) * MAX_MAP_WIDTH))
		game->map.buffer[len] = '\0';
	else
	{
		write(2, "Error\nInvalid map size (too big)\n", 34);
		return (0);
	}
	calculate_map_dimensions(game, len);
	validate_map(game, len);
	return (1);
}

// The else if check ensures that the width of each line is consistent with the first line’s width.
// For lines after the first, we calculate the effective width while accounting for the newline (1 * game->map.height).
// If the calculated width does not match the first line, the map is considered invalid.
// By enforcing consistent width on every line, we implicitly guarantee that the map’s height is correct,
// since any irregularity in height would also break this width consistency check.
// EXAMPLE:  Width = 5 | After 5 iterations i = 29 | if (5 != (29 - 4) / (1 + 4) -> CORRECT)
void	calculate_map_dimensions(t_game *game, int len)
{
	int	i;
	
	game->map.width = 0;
	game->map.height = 0;
	i = 0;
	while (i < len)
	{
		while (i < len && game->map.buffer[i] != '\n')
			i++;
		if (game->map.width == 0)
			game->map.width = i;
		else if (game->map.width != ((i - (1 * game->map.height)) / (1 + game->map.height)))
		{
			write (2, "Error\nInconsistent map dimensions\n", 35);
			exit(1);
		}
		game->map.height++;
		if (game->map.buffer[i] == '\n')
			i++;
	}
}

// Map validation has three steps: 
// 1. Check that all characters in the map are valid.
// 2. Validate map borders are fully enclosed by walls ('1')
// 3. Verify that the player can reach all collectibles and the exit.
void    validate_map(t_game *game, ssize_t len)
{
    if (!check_map_elements(game, len))
    {
        write(2, "Error\nInvalid map components\n", 30);
        exit(1);
    }
    // WE MUST CHECK THE BORDER, A BEAUTIFUL BORDER, AND MEXICO WILL PAY FOR IT
    if (!check_border(game, game->map.width, game->map.height, game->map.buffer))
    {
        printf("width: %d\nheight:%d\n", game->map.width, game->map.height);
        write(2, "Error\nInvalid border\n", 22);
        exit(1);
    }
    if (!flood_fill(game))
    {
        write(2, "Error\nMission: Impossible map\n", 31);
        exit(1);
    }
    
}

int check_map_elements(t_game *game, ssize_t len)
{
    ssize_t     i;
    int         player_count;
    int         exit_count;
    
    i = -1;
    player_count = 0;
    exit_count = 0;
    while (++i < len)
    {
        if (game->map.buffer[i] != '0' && game->map.buffer[i] != '1' && game->map.buffer[i] != 'E' && game->map.buffer[i] != 'X'
			&& game->map.buffer[i] != 'P' && game->map.buffer[i] != 'C' && game->map.buffer[i] != '\n')
			return (0);
        if (game->map.buffer[i] == 'P')
            player_count += track_element_pos(game, i, 0);
        else if (game->map.buffer[i] == 'E')
            exit_count++;
        else if (game->map.buffer[i] == 'C')
            game->map.collectible_count++;
        if (game->map.buffer[i] == 'X')
            game->enemy.enemy_count += track_element_pos(game, i, 1);
    }
    if (player_count != 1 || exit_count != 1 || game->map.collectible_count < 1 || game->enemy.enemy_count > 1)
        return (0);
    return (1);    
}

int check_border(t_game *game, int width, int height, char *map)
{
    int i;
    int j;

    i = 0;
    // top/bottom border check
    while (i < width)
    {
        if (map[i] != '1' || map[i + ((width + 1) * (height - 1))] != '1')
            return (0);
        i++;
    }
    i = 0;
    j = 0;
    // left/right border check
    while (j++ < height)
    {
        if (map[i] != '1' || map[i + (width - 1)] != '1')
            return (0);
        i += width + 1;
    }
    return (1);
}
