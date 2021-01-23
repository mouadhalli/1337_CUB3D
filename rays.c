/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 08:55:58 by mhalli            #+#    #+#             */
/*   Updated: 2020/12/28 08:56:02 by mhalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float		normalized_angle(float angle)
{
	angle = remainder(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

void		init_ray(float rayangle)
{
	g_ray.israyfacingdown = rayangle > 0 && rayangle < M_PI;
	g_ray.israyfacingup = !g_ray.israyfacingdown;
	g_ray.israyfacingright = rayangle < 0.5 * M_PI || rayangle > 1.5 * M_PI;
	g_ray.israyfacingleft = !g_ray.israyfacingright;
	g_ray.horzhit = FALSE;
	g_ray.horzhitx = 0;
	g_ray.horzhity = 0;
	g_ray.horzhitcont = 0;
	g_ray.vertihit = FALSE;
	g_ray.vertihitx = 0;
	g_ray.vertihity = 0;
	g_ray.vertihitcont = 0;
}

void		hit_distance(t_rays *rays)
{
	rays->horzhitdistance = g_ray.horzhit
	? distancebetweenpoints(g_pl.pos.x, g_pl.pos.y,
		g_ray.horzhitx, g_ray.horzhity)
	: INT_MAX;
	rays->verthitdistance = g_ray.vertihit
	? distancebetweenpoints(g_pl.pos.x, g_pl.pos.y,
		g_ray.vertihitx, g_ray.vertihity)
	: INT_MAX;
}

void		cast_ray(t_rays *rays, float rayangle, int i)
{
	rayangle = normalized_angle(rayangle);
	init_ray(rayangle);
	horizray(rayangle);
	vertiray(rayangle);
	hit_distance(rays);
	if (rays->verthitdistance < rays->horzhitdistance)
	{
		rays[i].distance = rays->verthitdistance;
		rays[i].wallhit_x = g_ray.vertihitx;
		rays[i].wallhit_y = g_ray.vertihity;
		rays[i].wallhitcontent = g_ray.vertihitcont;
		rays[i].washit_vertical = TRUE;
	}
	else
	{
		rays[i].distance = rays->horzhitdistance;
		rays[i].wallhit_x = g_ray.horzhitx;
		rays[i].wallhit_y = g_ray.horzhity;
		rays[i].wallhitcontent = g_ray.horzhitcont;
		rays[i].washit_vertical = FALSE;
	}
}

void		cast_rays(t_rays *rays)
{
	float		rayangle;
	int			i;

	rayangle = normalized_angle(g_pl.rotationangle - ((60 * (M_PI / 180)) / 2));
	i = -1;
	while (++i < g_ptr.width)
	{
		cast_ray(rays, rayangle, i);
		rays[i].ray_angle = rayangle;
		rays[i].israyfacing_down = g_ray.israyfacingdown;
		rays[i].israyfacing_up = g_ray.israyfacingup;
		rays[i].israyfacing_left = g_ray.israyfacingleft;
		rays[i].israyfacing_right = g_ray.israyfacingright;
		rayangle += (60 * (M_PI / 180)) / g_ptr.width;
	}
}
