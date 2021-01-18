/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_rays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 10:35:34 by mhalli            #+#    #+#             */
/*   Updated: 2020/12/28 10:35:36 by mhalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		vert_inter(float nextvertx, float nextverty)
{
	g_ray.vertihitx = nextvertx;
	g_ray.vertihity = nextverty;
	if (g_ray.xtocheck >= 0 && g_ray.xtocheck < g_map.num_cols * TILE_SIZE &&
		g_ray.ytocheck >= 0 && g_ray.ytocheck < g_map.num_rows * TILE_SIZE)
	{
		g_p.x = (int)floor(g_ray.xtocheck / TILE_SIZE);
		g_p.y = (int)floor(g_ray.ytocheck / TILE_SIZE);
		g_ray.vertihitcont = g_map.map[(int)g_p.y][(int)g_p.x];
		g_ray.vertihit = TRUE;
	}
}

void		verticheck(float xstep, float ystep)
{
	float		nextvertx;
	float		nextverty;

	nextvertx = g_ray.xintercept;
	nextverty = g_ray.yintercept;
	while (nextvertx >= 0 && nextvertx < g_map.num_cols * TILE_SIZE &&
		nextverty >= 0 && nextverty < g_map.num_rows * TILE_SIZE)
	{
		g_ray.xtocheck = nextvertx + (g_ray.israyfacingleft ? -1 : 0);
		g_ray.ytocheck = nextverty;
		if (g_wall_at(g_ray.xtocheck, g_ray.ytocheck))
		{
			vert_inter(nextvertx, nextverty);
			break ;
		}
		else
		{
			nextvertx += xstep;
			nextverty += ystep;
		}
	}
}

void		vertiray(float rayangle)
{
	float		xstep;
	float		ystep;

	g_ray.xintercept = floor(g_pl.pos.x / TILE_SIZE) * TILE_SIZE;
	g_ray.xintercept += g_ray.israyfacingright ? TILE_SIZE : 0;
	g_ray.yintercept = g_pl.pos.y + (g_ray.xintercept - g_pl.pos.x)
		* tan(rayangle);
	xstep = TILE_SIZE;
	xstep *= g_ray.israyfacingleft ? -1 : 1;
	ystep = TILE_SIZE * tan(rayangle);
	ystep *= (g_ray.israyfacingup && ystep > 0) ? -1 : 1;
	ystep *= (g_ray.israyfacingdown && ystep < 0) ? -1 : 1;
	verticheck(xstep, ystep);
}

void		init_txt_and_colors(void)
{
	int		i;

	i = 0;
	while (i < 5)
	{
		g_txt[i].data = 0;
		i++;
	}
	g_ptr.ceil = 0;
	g_ptr.floor = 0;
}

char		*filter_txtr(char *txtr)
{
	int		i;

	i = ft_strlen(txtr) - 1;
	while (txtr[i] == ' ')
		txtr[i--] = '\0';
	return (txtr);
}
