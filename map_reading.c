/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 16:45:02 by mhalli            #+#    #+#             */
/*   Updated: 2020/12/28 16:45:04 by mhalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			to_split(char c)
{
	if ((c == '1') || c == ' ')
		return (0);
	else
		return (1);
}

void		fill_line(char *array, int i)
{
	int		j;

	j = 0;
	while (array[j])
	{
		if (array[j] == '1' || array[j] == '0')
			g_map.map[i][j] = array[j];
		else if (array[j] == '2' && g_ptr.sprite_num < 500)
			init_sprite(i, j, array);
		else if (ft_strchr("NSEW", array[j]))
		{
			g_map.map[i][j] = array[j];
			init_player(i, j);
		}
		j++;
	}
	while (j < g_map.num_cols)
	{
		g_map.map[i][j] = '1';
		j++;
	}
	free(array);
}

void		fill_map(char *buffer)
{
	char	**array;
	int		i;

	i = -1;
	array = ft_split(buffer, '\n');
	g_map.map = malloc(g_map.num_rows * sizeof(char *));
	while (array[++i])
	{
		g_map.map[i] = malloc(g_map.num_cols * sizeof(char));
		fill_line(array[i], i);
	}
	free(array);
}

void		add_mapline(char **buffer, char *str)
{
	char		*tmp;

	if (g_map.num_cols < (int)ft_strlen(str))
		g_map.num_cols = ft_strlen(str);
	tmp = *buffer;
	*buffer = ft_strjoin(*buffer, str);
	if (tmp)
		free(tmp);
	tmp = *buffer;
	*buffer = ft_strjoin(*buffer, "\n");
	free(tmp);
	free(str);
}

int			get_map(char *line, int *argnb, int fd)
{
	int		len;
	char	*buffer;

	if (*argnb < 8)
		print_error("missing element");
	if (g_map.map)
		print_error("duplicated map");
	*argnb += 1;
	g_map.num_cols = ft_strlen(line);
	g_map.num_rows = 0;
	buffer = ft_strdup("");
	while (!to_split(*line))
	{
		add_mapline(&buffer, line);
		len = get_next_line(fd, &line);
		g_map.num_rows++;
	}
	if (*line && to_split(*line))
		print_error("the map should be the last element of the file");
	free(line);
	anlys_map(buffer);
	fill_map(buffer);
	free(buffer);
	return (0);
}
