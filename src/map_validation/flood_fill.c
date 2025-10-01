/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 00:10:20 by rheidary          #+#    #+#             */
/*   Updated: 2025/09/23 08:25:29 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int flood_fill(t_game *game)
{
    int i;
    int j;
    int starting_pos;
    int visited[MAX_MAP_HEIGHT  * (MAX_MAP_WIDTH + 1)];

    i = -1;
    j = 0;
// Initialize visited[] on stack to avoid calloc/free overhead and track colls
    while (++i < (game->map.width + 1) * game->map.height)
        visited[i] = 0;
    starting_pos = game->player.y * (game->map.width + 1) + game->player.x;
    dfs_fill(game, starting_pos, visited);
    i = -1;
    while (game->map.buffer[++i])
    {
        if (game->map.buffer[i] == 'C' && visited[i] == 0)
            return (0);
        if (game->map.buffer[i] == 'E' && visited[i] == 0)
            return (0);
    }
    return (1);
}

void dfs_fill(t_game *game, int idx, int *visited)
{
    // wall check
    if (game->map.buffer[idx] == '1')
        return;
    // already checked 
    if (visited[idx])
        return;
    visited[idx] = 1;
    dfs_fill(game, idx + 1, visited);
    dfs_fill(game, idx - 1, visited);
    dfs_fill(game, idx + (game->map.width + 1), visited);
    dfs_fill(game, idx - (game->map.width + 1), visited);
}
