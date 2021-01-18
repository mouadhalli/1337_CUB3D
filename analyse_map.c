/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 16:48:57 by mhalli            #+#    #+#             */
/*   Updated: 2020/12/28 16:48:58 by mhalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			texture_side(char *filename)
{
	if (!ft_strncmp(filename, "NO", 3))
		return (NO);
	else if (!ft_strncmp(filename, "SO", 3))
		return (SO);
	else if (!ft_strncmp(filename, "EA", 3))
		return (EA);
	else if (!ft_strncmp(filename, "WE", 3))
		return (WE);
	else if (!ft_strncmp(filename, "S", 3))
		return (S);
	return (0);
}

int			closed_map(char *line, char c)
{
	int		i;

	i = -1;
	while (line[++i])
	{
		while (line[i] == ' ')
			i++;
		if (line[i] != c)
			return (0);
	}
	return (1);
}

int			filter_row(char *row, char *str)
{
	int		j;

	j = -1;
	while (row[++j])
	{
		if (!ft_strchr(str, row[j]))
			return (0);
	}
	return (1);
}

void		clean_mapline(char **lines, int *player, int i)
{
	int		j;

	j = 0;
	if (!filter_row(lines[i], "012NSEW "))
		print_error("bad element in the map\n");
	while (lines[i][j])
	{
		if (ft_isalpha(lines[i][j]))
			*player += 1;
		if (lines[i][j] == '0' || lines[i][j] == '2' || ft_isalpha(lines[i][j]))
		{
			if ((int)ft_strlen(lines[i - 1]) - 1 < j || lines[i - 1][j] == ' '
			|| (int)ft_strlen(lines[i + 1]) - 1 < j || lines[i + 1][j] == ' ')
				print_error("bad element arround |0| or |SPRITE| or |PLAYER|");
		}
		j++;
	}
}

void		anlys_map(char *buffer)
{
	char	**lines;
	int		i;
	int		player;

	i = 0;
	player = 0;
	lines = ft_split(buffer, '\n');
	if (!filter_row(lines[0], "1 ")
	|| !filter_row(lines[g_map.num_rows - 1], "1 "))
		print_error("the map must be closed with walls");
	while (++i < g_map.num_rows - 1)
		clean_mapline(lines, &player, i);
	free_arr((void **)lines, g_map.num_rows);
	if (player > 1)
		print_error("only one player is allowed inside the map");
	else if (player < 1)
		print_error("no player was found inside the map");
}
