/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: treis-ro <treis-ro@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 18:09:23 by treis-ro          #+#    #+#             */
/*   Updated: 2023/10/13 18:37:02 by treis-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	const char	*here;
	const char	*save;
	size_t		i;
	size_t		x;

	i = 0;
	if (*little == '\0' || big == little)
		return ((char *)big);
	while (*big && i < len)
	{
		save = little;
		here = big;
		x = i;
		while (*big && *little && *big == *little && i++ < len)
		{
			big++;
			little++;
		}
		if (*little == '\0')
			return ((char *)here);
		little = save;
		big = here + 1;
		i = x + 1;
	}
	return (0);
}
