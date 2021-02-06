/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_rays.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 10:35:44 by mhalli            #+#    #+#             */
/*   Updated: 2020/12/28 10:35:46 by mhalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		horz_inter(float nexthorzx, float nexthorzy)
{
	g_ray.horzhitx = nexthorzx;
	g_ray.horzhity = nexthorzy;
	if (g_ray.xtocheck >= 0 && g_ray.xtocheck < g_map.num_cols * TILE_SIZE &&
		g_ray.ytocheck >= 0 && g_ray.ytocheck < g_map.num_rows * TILE_SIZE)
	{
		g_p.x = (int)floor(g_ray.xtocheck / TILE_SIZE);
		g_p.y = (int)floor(g_ray.ytocheck / TILE_SIZE);
		g_ray.horzhitcont = g_map.map[(int)g_p.y][(int)g_p.x];
		g_ray.horzhit = TRUE;
	}
}

void		horizcheck(float xstep, float ystep)
{
	float		nexthorzx;
	float		nexthorzy;

	nexthorzx = g_ray.xintercept;
	nexthorzy = g_ray.yintercept;
	while (nexthorzx >= 0 && nexthorzx < g_map.num_cols * TILE_SIZE &&
		nexthorzy >= 0 && nexthorzy < g_map.num_rows * TILE_SIZE)
	{
		g_ray.xtocheck = nexthorzx;
		g_ray.ytocheck = nexthorzy + (g_ray.israyfacingup ? -1 : 0);
		if (wall_at(g_ray.xtocheck, g_ray.ytocheck))
		{
			horz_inter(nexthorzx, nexthorzy);
			break ;
		}
		else
		{
			nexthorzx += xstep;
			nexthorzy += ystep;
		}
	}
}

void		horizray(float rayangle)
{
	float		xstep;
	float		ystep;

	g_ray.yintercept = floor(g_pl.pos.y / TILE_SIZE) * TILE_SIZE;
	g_ray.yintercept += g_ray.israyfacingdown ? TILE_SIZE : 0;
	g_ray.xintercept = g_pl.pos.x + (g_ray.yintercept - g_pl.pos.y)
		/ tan(rayangle);
	ystep = TILE_SIZE;
	ystep *= g_ray.israyfacingup ? -1 : 1;
	xstep = TILE_SIZE / tan(rayangle);
	xstep *= (g_ray.israyfacingleft && xstep > 0) ? -1 : 1;
	xstep *= (g_ray.israyfacingright && xstep < 0) ? -1 : 1;
	horizcheck(xstep, ystep);
}

void		file_path_checker(int *fd, int c, char **v)
{
	if (c < 2 || (*fd = open(v[1], O_RDONLY)) < 0)
		print_error("invalid file");
	if (ft_strlen(*(v + 1)) > 4 && !ft_strncmp(*(v + 1)
		+ ft_strlen(v[1]) - 5, "/.cub", 4))
		print_error("file name must contain .cub extension");
	if (ft_strncmp(*(v + 1) + ft_strlen(v[1]) - 4, ".cub", 4)
		|| ft_strlen(*(v + 1)) < 5)
		print_error("file name must contain .cub extensionnn");
}
