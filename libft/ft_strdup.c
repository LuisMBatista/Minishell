/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: treis-ro <treis-ro@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:54:19 by treis-ro          #+#    #+#             */
/*   Updated: 2023/10/12 17:16:05 by treis-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	int		x;
	int		i;
	char	*res;

	x = ft_strlen(str);
	res = (char *)malloc((x + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i < x)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
