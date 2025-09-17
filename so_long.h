/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 20:14:28 by rheidary          #+#    #+#             */
/*   Updated: 2025/09/09 21:44:02 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

#include "libft/libft.h"
#include "ft_printf/libftprintf.h"

#include <mlx.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_player{
	int	x;
	int	y;
	int	alive;
}	t_player;

typedef struct {
	void		*mlx;
	void		*win;
	t_player	player;
	int			key_pressed;
	void		*player_img;
    int			player_w;
    int			player_h;
	int			last_move_time;
	int			move_delay;
}	t_game;


#endif