/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 16:56:28 by mhalli            #+#    #+#             */
/*   Updated: 2020/12/28 16:56:30 by mhalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(int x, int y, int color, void *img)
{
	int		*tmp;

	tmp = (int*)mlx_get_data_addr(img, &g_me, &g_me, &g_me);
	tmp[x + (y * g_ptr.width)] = color;
}

void	print_error(const char *error)
{
	ft_putstr_fd("Error\n", 0);
	ft_putstr_fd((char *)error, 0);
	exit(-1);
}

int		close_win(void)
{
	exit(1);
	return (0);
}

int		is_floor_c(char *s)
{
	if (!ft_strncmp(s, "F", 2)
	|| !ft_strncmp(s, "C", 2))
		return (1);
	return (0);
}
