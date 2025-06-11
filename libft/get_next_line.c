/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: treis-ro <treis-ro@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:02:45 by treis-ro          #+#    #+#             */
/*   Updated: 2024/11/01 12:49:39 by treis-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	follow_read[BUFFER_SIZE + 1];
	char		*line;
	int			i;

	line = NULL;
	i = 0;
	if (read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
	{
		while (i <= BUFFER_SIZE)
			follow_read[i++] = '\0';
		return (NULL);
	}
	while (follow_read[0] || read(fd, follow_read, BUFFER_SIZE) > 0)
	{
		line = gnl_strjoin(line, follow_read);
		if (!line)
			return (NULL);
		gnl_update(follow_read);
		if (line[gnl_len(line) - 1] == '\n')
			return (line);
	}
	return (line);
}
