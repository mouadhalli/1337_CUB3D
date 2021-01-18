/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 03:16:46 by mhalli            #+#    #+#             */
/*   Updated: 2020/12/21 03:16:48 by mhalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		init_sprite(int i, int j, char *array)
{
	g_ptr.sprite[g_ptr.sprite_num].pos.x =
	(j * TILE_SIZE) + (float)(TILE_SIZE / 2);
	g_ptr.sprite[g_ptr.sprite_num].pos.y =
	(i * TILE_SIZE) + (float)(TILE_SIZE / 2);
	g_ptr.sprite_num++;
	g_map.map[i][j] = array[j];
}

float		distancebetweenpoints(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void		draw_sprite(int x, float distance, float height, t_rays *rays)
{
	int		i;
	int		j;
	int		y_offset;
	int		color;
	int		*tmp;

	tmp = (int*)mlx_get_data_addr(g_ptr.mlx_img, &g_me, &g_me, &g_me);
	i = x - 1;
	while (++i < x + height)
	{
		j = (g_ptr.height - height) / 2;
		y_offset = 0;
		if (i >= 0 && i < g_ptr.width && distance < rays[i].distance)
		{
			while (j < (g_ptr.height + height) / 2 - 1)
			{
				color = g_txt[4].data[(int)(y_offset / height * g_txt[4].height)
				* g_txt[4].width + (int)((i - x) / height * g_txt[4].width)];
				if (j < g_ptr.height && j >= 0 && color != 0x00000)
					tmp[(j) * g_ptr.width + (i)] = color;
				j++;
				y_offset++;
			}
		}
	}
}

void		sort_sprites(void)
{
	int			i;
	int			j;
	t_sprite	tmp;

	i = 0;
	while (i++ < g_ptr.sprite_num)
		g_ptr.sprite[i].distance = distancebetweenpoints(
		g_ptr.sprite[i].pos.x, g_ptr.sprite[i].pos.y, g_pl.pos.x, g_pl.pos.y);
	i = 0;
	while (i < g_ptr.sprite_num - 1)
	{
		j = 0;
		while (j < g_ptr.sprite_num - 1 - i)
		{
			if (g_ptr.sprite[j].distance < g_ptr.sprite[j + 1].distance)
			{
				tmp = g_ptr.sprite[j];
				g_ptr.sprite[j] = g_ptr.sprite[j + 1];
				g_ptr.sprite[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void		render_sprite(t_rays *rays)
{
	float		angle;
	float		sprite_height;
	int			column_index;
	int			i;
	float		alpha;

	g_spr = g_ptr.sprite;
	sort_sprites();
	i = 0;
	while (i < g_ptr.sprite_num)
	{
		g_spr[i].distance = distancebetweenpoints(g_ptr.sprite[i].pos.x,
			g_ptr.sprite[i].pos.y, g_pl.pos.x, g_pl.pos.y);
		angle = atan2(g_pl.pos.y - g_spr[i].pos.y, g_pl.pos.x
			- g_spr[i].pos.x) + M_PI;
		alpha = angle - rays[0].ray_angle;
		if (rays[0].ray_angle > (3 * M_PI) / 2 && angle <= M_PI / 3)
			alpha += 2 * M_PI;
		sprite_height = (TILE_SIZE / g_spr[i].distance)
			* g_ptr.projection_plane;
		column_index = alpha * (g_ptr.width / (M_PI / 3)) - (sprite_height / 2);
		draw_sprite(column_index, g_spr[i].distance, sprite_height, rays);
		i++;
	}
}
