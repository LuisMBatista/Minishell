/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: treis-ro <treis-ro@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:43:00 by treis-ro          #+#    #+#             */
/*   Updated: 2024/11/01 12:49:05 by treis-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_len(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != '\n')
		i++;
	if (str && str[i] == '\n')
		i++;
	return (i);
}

char	*gnl_strjoin(char *line, char *flw)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = (char *)malloc((gnl_len(line) + gnl_len(flw) + 1) * (sizeof(char)));
	if (!res)
		return (free(line), NULL);
	while (line && line[i])
	{
		res[i] = line[i];
		i++;
	}
	while (flw[j] != '\n' && flw[j])
	{
		res[i + j] = flw[j];
		j++;
	}
	if (flw[j] == '\n')
		res[i + j++] = '\n';
	res[i + j] = '\0';
	if (line)
		free(line);
	return (res);
}

void	gnl_update(char *follow_read)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (follow_read[i] != '\n' && i < BUFFER_SIZE)
	{
		follow_read[i] = '\0';
		i++;
	}
	if (follow_read [i] == '\n')
	{
		follow_read[i] = '\0';
		i++;
	}
	while (i < BUFFER_SIZE)
	{
		follow_read[j] = follow_read[i];
		follow_read[i] = '\0';
		i++;
		j++;
	}
}
