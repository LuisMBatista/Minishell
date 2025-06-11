/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: treis-ro <treis-ro@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:21:22 by treis-ro          #+#    #+#             */
/*   Updated: 2024/11/01 12:32:50 by treis-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atoi(const char *str)
{
	int				mod;
	long			i;

	i = 0;
	mod = 1;
	while ((str[i] <= 13 && str[i] >= 9) || str[i] == 32)
		str++;
	if (*str == '-')
	{
		mod = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (!(*str >= 48 && *str <= 57))
			return (0);
		i = i * 10 + (*str - 48);
		str++;
	}
	return (mod * i);
}
