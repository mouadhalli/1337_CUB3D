/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 17:17:01 by mhalli            #+#    #+#             */
/*   Updated: 2020/12/31 17:17:05 by mhalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			init_wall(t_rays *rays, int i)
{
	g_wall.perpdistance = rays[i].distance *
		cos(rays[i].ray_angle - g_pl.rotationangle);
	g_wall.distanceprojplane = (g_ptr.width / 2) / tan((60 * (M_PI / 180)) / 2);
	g_wall.projectedg_wallheight = (TILE_SIZE / g_wall.perpdistance) *
		g_wall.distanceprojplane;
	g_wall.g_wallstripheight = (int)g_wall.projectedg_wallheight;
}

double			f_mod(double a, double b)
{
	return (a - (floor(a / b) * b));
}

void			which_texture(int *txt, int i, t_rays *rays)
{
	if (rays[i].israyfacing_up && !rays[i].washit_vertical)
		*txt = SO;
	else if (rays[i].israyfacing_down && !rays[i].washit_vertical)
		*txt = NO;
	else if (rays[i].israyfacing_left && rays[i].washit_vertical)
		*txt = EA;
	else if (rays[i].israyfacing_right && rays[i].washit_vertical)
		*txt = WE;
}

void			draw_texture(int px, int i, t_rays *rays)
{
	int		*tmp;
	int		side;
	int		offset_x;
	int		offset_y;
	int		textrtop;

	which_texture(&side, i, rays);
	tmp = (int*)mlx_get_data_addr(g_ptr.mlx_img, &g_me, &g_me, &g_me);
	if (rays[i].washit_vertical)
		offset_x = f_mod(rays[i].g_wallhit_y, TILE_SIZE) *
			(g_txt[side].width / TILE_SIZE);
	else
		offset_x = f_mod(rays[i].g_wallhit_x, TILE_SIZE) *
			(g_txt[side].width / TILE_SIZE);
	textrtop = px + (g_wall.g_wallstripheight / 2) - (g_ptr.height / 2);
	offset_y = textrtop * ((float)g_txt[side].height
		/ g_wall.g_wallstripheight);
	tmp[i + ((g_ptr.width) * px)] = g_txt[side].data[offset_x +
		(offset_y * g_txt[side].width)];
}

void			render_walls(t_rays *rays)
{
	int		i;
	int		px;
	int		g_walltop_px;
	int		g_wallbottom_px;

	i = -1;
	while (++i < g_ptr.width)
	{
		init_wall(rays, i);
		g_walltop_px = (g_ptr.height / 2) - (g_wall.g_wallstripheight / 2);
		g_walltop_px = g_walltop_px < 0 ? 0 : g_walltop_px;
		g_wallbottom_px = (g_ptr.height / 2) + (g_wall.g_wallstripheight / 2);
		g_wallbottom_px = g_wallbottom_px > g_ptr.height
			? g_ptr.height : g_wallbottom_px;
		px = -1;
		while (++px < g_ptr.height)
		{
			if (px < g_walltop_px)
				my_mlx_pixel_put(i, px, g_ptr.ceil, g_ptr.mlx_img);
			else if (px >= g_walltop_px && px < g_wallbottom_px)
				draw_texture(px, i, rays);
			else if (px >= g_wallbottom_px)
				my_mlx_pixel_put(i, px, g_ptr.floor, g_ptr.mlx_img);
		}
	}
}
