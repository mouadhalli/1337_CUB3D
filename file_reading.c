/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reading.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 12:30:00 by mhalli            #+#    #+#             */
/*   Updated: 2020/12/10 12:30:02 by mhalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			is_txtr(char *s)
{
	if ((!ft_strncmp(s, "NO", 3)
		|| !ft_strncmp(s, "EA", 3)
		|| !ft_strncmp(s, "WE", 3)
		|| !ft_strncmp(s, "S", 2)
		|| !ft_strncmp(s, "SO", 3)))
		return (1);
	return (0);
}

void		get_textures(char **filename, int *argnb, char *line)
{
	int		side;
	void	*img;
	char	*txtrname;

	txtrname = textr_name(line);
	side = texture_side(filename[0]);
	if (g_txt[side].data)
		print_error("duplicated texture");
	if (line[(int)(ft_strlen(line) - 1)] == ' ')
		print_error("space at the end of a texture element");
	img = mlx_xpm_file_to_image(g_ptr.mlx_ptr, txtrname,
		&(g_txt[side].width), &(g_txt[side].height));
	if (!img)
		print_error("invalid texture path");
	g_txt[side].data = (int *)mlx_get_data_addr(img, &g_me, &g_me, &g_me);
	*argnb += 1;
	free(img);
	free(line);
	free_arr((void **)filename, 2);
	free(txtrname);
}

void		resolution(char **arg, int *argnb, char *line)
{
	if (g_ptr.width || g_ptr.height)
		print_error("duplicated resolution");
	if (line[(int)(ft_strlen(line) - 1)] == ' ')
		print_error("space at the end of resolution element");
	if (count_words(line, ' ') != 3)
		print_error("the resolution must contain two dimensions");
	if (!filter_resolution(arg[1])
		|| !filter_resolution(arg[2]))
		print_error("invalid window width or height");
	g_ptr.width = ft_atoi(*(arg + 1));
	g_ptr.height = ft_atoi(*(arg + 2));
	if (g_ptr.width == 0 || g_ptr.height == 0)
		print_error("Impossible resolution\n");
	*argnb += 1;
	if (g_ptr.width > 2880 || g_ptr.width < 0)
		g_ptr.width = 2880;
	if (g_ptr.height > 1620 || g_ptr.height < 0)
		g_ptr.height = 1620;
	g_ptr.proj_plane = (g_ptr.width / 2) / tan((60 * (M_PI / 180)) / 2);
	free_arr((void **)arg, 3);
	free(line);
}

void		get_floor_ceil(char **colors, int *argnb, char *line)
{
	int		retrn;
	char	**color;

	if ((colors[0][0] == 'F' && g_ptr.floor)
		|| (colors[0][0] == 'C' && g_ptr.ceil))
		print_error("duplicated Floor or ceiling color");
	if (line[(int)(ft_strlen(line) - 1)] == ' ')
		print_error("space at the end of floor or ceiling element");
	color = ft_split(colors[1], ',');
	if (count_words(line, ' ') != 2 || (count_words(colors[1], ',') != 3)
		|| (count_chars(colors[1], ',') != 2))
		print_error("invalid RGB combination");
	if (!check_numb(color[0], 0, 256) || !check_numb(color[1], 0, 256)
		|| !check_numb(color[2], 0, 256))
		print_error("invalid color");
	*argnb += 1;
	retrn = ((ft_atoi(color[0]) * 256 * 256) + (ft_atoi(color[1]) * 256)
		+ ft_atoi(color[2]));
	if (colors[0][0] == 'F')
		g_ptr.floor = retrn;
	else
		g_ptr.ceil = retrn;
	free_arr((void **)colors, 2);
	free_arr((void **)color, 3);
	free(line);
}

void		get_cub_fl(int fd)
{
	char	*line;
	char	**word;
	int		argnb;

	argnb = 0;
	while (get_next_line(fd, &line) || ft_strlen(line))
	{
		if (*line && to_split(*line))
			word = ft_split(line, ' ');
		if (*line && !to_split(*line))
			get_map(line, &argnb, fd);
		else if (*line && (!ft_strncmp(word[0], "R", 2)))
			resolution(word, &argnb, line);
		else if (*line && is_txtr(word[0]))
			get_textures(word, &argnb, line);
		else if (*line && is_floor_c(word[0]))
			get_floor_ceil(word, &argnb, line);
		else if (*line && g_map.map)
			print_error("the map should be the last element of the file");
		else if (*line)
			print_error("invalid element inside the file");
		else
			free(line);
	}
	free(line);
}
