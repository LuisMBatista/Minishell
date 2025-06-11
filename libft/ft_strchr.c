/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: treis-ro <treis-ro@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:39:30 by treis-ro          #+#    #+#             */
/*   Updated: 2023/10/25 17:43:47 by treis-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int k)
{
	while (*str)
	{
		if (*str == (char)k)
			return ((char *)str);
		str++;
	}
	if (*str == (char)k)
		return ((char *)str);
	return (0);
}
