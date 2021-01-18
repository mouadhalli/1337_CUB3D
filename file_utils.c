/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 13:21:48 by mhalli            #+#    #+#             */
/*   Updated: 2020/12/10 13:21:49 by mhalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			check_numb(char *str, int min, int max)
{
	int		i;
	int		numb;

	i = -1;
	numb = 0;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
	}
	numb = ft_atoi(str);
	if (numb < min || numb > max)
		return (0);
	return (1);
}

int			count_words(char *str, char c)
{
	int		i;
	int		words;

	i = 0;
	words = 0;
	while (str[i])
	{
		if (str[i] != c && (i == 0 || str[i - 1] == c))
			words++;
		i++;
	}
	return (words);
}

int			count_chars(char *str, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

void		free_arr(void **arr, int len)
{
	int		i;

	i = 0;
	while (i <= len)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char		*textr_name(char *line)
{
	int		i;
	char	*txtr;

	i = 0;
	while (ft_isalpha(line[i]))
		i++;
	while (line[i] == ' ')
		i++;
	txtr = filter_txtr(ft_strdup(line + i));
	return (txtr);
}
