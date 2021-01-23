/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 14:51:47 by mhalli            #+#    #+#             */
/*   Updated: 2020/12/28 14:51:49 by mhalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			pl_colision(float x, float y)
{
	int		index_x;
	int		index_y;

	index_x = x;
	index_y = y;
	if (index_x < 0 || index_x > g_map.num_cols * TILE_SIZE ||
		index_y < 0 || index_y > g_map.num_rows * TILE_SIZE)
		return (1);
	index_x = floor(index_x / TILE_SIZE);
	index_y = floor(index_y / TILE_SIZE);
	if (g_map.map[index_y][index_x] == '1')
		return (1);
	else if (g_map.map[index_y][index_x] == '2')
		return (1);
	return (0);
}

int			wall_at(float x, float y)
{
	int		index_x;
	int		index_y;

	index_x = x;
	index_y = y;
	if (index_x < 0 || index_x > g_map.num_cols * TILE_SIZE ||
		index_y < 0 || index_y > g_map.num_rows * TILE_SIZE)
		return (1);
	index_x = floor(index_x / TILE_SIZE);
	index_y = floor(index_y / TILE_SIZE);
	if (g_map.map[index_y][index_x] == '1')
		return (1);
	return (0);
}

void		render(void)
{
	t_rays		rays[g_ptr.width];

	mlx_clear_window(g_ptr.mlx_ptr, g_ptr.mlx_win);
	pl_movements();
	cast_rays(rays);
	render_walls(rays);
	render_sprite(rays);
	mlx_put_image_to_window(g_ptr.mlx_ptr, g_ptr.mlx_win, g_ptr.mlx_img, 0, 0);
}

int			move_p(void)
{
	mlx_hook(g_ptr.mlx_win, 2, 0, moove_player, (void *)0);
	mlx_hook(g_ptr.mlx_win, 3, 0, reset_player, (void *)0);
	mlx_hook(g_ptr.mlx_win, 17, 0, close_win, (void *)0);
	render();
	return (0);
}

int			main(int c, char **v)
{
	int		fd;

	fd = 0;
	if ((c < 2 || (fd = open(v[1], O_RDONLY)) < 0)
	|| ft_strncmp(*(v + 1) + ft_strlen(v[1]) - 4, ".cub", 4))
		print_error("invalid .cub file path");
	g_ptr.mlx_ptr = mlx_init();
	g_txt = ft_calloc(5, sizeof(t_texture));
	init_txt_and_colors();
	get_cub_fl(fd);
	if (!g_map.map)
		print_error("map not found");
	g_ptr.mlx_win = mlx_new_window(g_ptr.mlx_ptr, g_ptr.width,
		g_ptr.height, "Jumia_Cub3D");
	g_ptr.mlx_img = mlx_new_image(g_ptr.mlx_ptr, g_ptr.width, g_ptr.height);
	g_data = (int*)mlx_get_data_addr(g_ptr.mlx_img, &g_me, &g_me, &g_me);
	if (c > 3 || (c > 2 && ft_strncmp(v[2], "--save", 7)))
		print_error("invalid argument after .cub!!");
	if (c > 2 && !ft_strncmp(v[2], "--save", 7))
		take_screenshot();
	mlx_loop_hook(g_ptr.mlx_ptr, move_p, &g_pl);
	mlx_loop(g_ptr.mlx_ptr);
}
