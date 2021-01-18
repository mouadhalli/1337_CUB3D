/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 01:42:02 by mhalli            #+#    #+#             */
/*   Updated: 2020/12/16 01:42:05 by mhalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			init_player(int i, int j)
{
	if (g_map.map[i][j] == 'E')
		g_pl.rotationangle = 0;
	else if (g_map.map[i][j] == 'S')
		g_pl.rotationangle = M_PI / 2;
	else if (g_map.map[i][j] == 'W')
		g_pl.rotationangle = M_PI;
	else if (g_map.map[i][j] == 'N')
		g_pl.rotationangle = 3 * (M_PI / 2);
	g_pl.pos.x = (j * TILE_SIZE) + (TILE_SIZE / 2);
	g_pl.pos.y = (i * TILE_SIZE) + (TILE_SIZE / 2);
	g_map.map[i][j] = '0';
	g_pl.turndirection = 0;
	g_pl.walkdirection = 0;
	g_pl.turnspeed = 3 * (M_PI / 180);
	g_pl.moove_left = 0;
	g_pl.moove_right = 0;
	g_pl.moove_forward_or_backward = 0;
	g_pl.walkspeed = TILE_SIZE / 9;
}

int				reset_player(int key)
{
	if (key == KEY_UP || key == KEY_DOWN)
	{
		g_pl.walkdirection = 0;
		g_pl.moove_forward_or_backward = 0;
	}
	else if (key == KEY_RIGHT)
		g_pl.moove_right = 0;
	else if (key == KEY_LEFT)
		g_pl.moove_left = 0;
	else if (key == 124)
		g_pl.turndirection = 0;
	else if (key == 123)
		g_pl.turndirection = 0;
	if (key == 257)
		g_pl.walkspeed = TILE_SIZE / 9;
	return (0);
}

int				moove_player(int key)
{
	if (key == ESC)
		close_win();
	if (key == KEY_UP)
	{
		g_pl.walkdirection = 1;
		g_pl.moove_forward_or_backward = 1;
	}
	else if (key == KEY_DOWN)
	{
		g_pl.walkdirection = -1;
		g_pl.moove_forward_or_backward = 1;
	}
	else if (key == KEY_RIGHT)
		g_pl.moove_right = 1;
	else if (key == KEY_LEFT)
		g_pl.moove_left = 1;
	else if (key == 124)
		g_pl.turndirection = 1;
	else if (key == 123)
		g_pl.turndirection = -1;
	if (key == 257)
		g_pl.walkspeed = g_pl.walkspeed * 7;
	return (1);
}

void			calc_movement(float *nplayer_x, float *nplayer_y)
{
	float	move_step;

	if (g_pl.moove_left)
	{
		*nplayer_x = g_pl.pos.x - cos(g_pl.rotationangle +
			(90 * (M_PI / 180))) * g_pl.walkspeed;
		*nplayer_y = g_pl.pos.y - sin(g_pl.rotationangle +
			(90 * (M_PI / 180))) * g_pl.walkspeed;
	}
	else if (g_pl.moove_right)
	{
		*nplayer_x = g_pl.pos.x + cos(g_pl.rotationangle +
			(90 * (M_PI / 180))) * g_pl.walkspeed;
		*nplayer_y = g_pl.pos.y + sin(g_pl.rotationangle +
			(90 * (M_PI / 180))) * g_pl.walkspeed;
	}
	else if (g_pl.moove_forward_or_backward)
	{
		move_step = g_pl.walkdirection * g_pl.walkspeed;
		*nplayer_x = g_pl.pos.x + cos(g_pl.rotationangle) * move_step;
		*nplayer_y = g_pl.pos.y + sin(g_pl.rotationangle) * move_step;
	}
}

void			pl_movements(void)
{
	float	nplayer_x;
	float	nplayer_y;

	nplayer_x = g_pl.pos.x;
	nplayer_y = g_pl.pos.y;
	g_pl.rotationangle += g_pl.turndirection * g_pl.turnspeed;
	g_pl.rotationangle = normalized_angle(g_pl.rotationangle);
	calc_movement(&nplayer_x, &nplayer_y);
	if (!pl_colision(nplayer_x, g_pl.pos.y))
		g_pl.pos.x = nplayer_x;
	if (!pl_colision(g_pl.pos.x, nplayer_y))
		g_pl.pos.y = nplayer_y;
}
