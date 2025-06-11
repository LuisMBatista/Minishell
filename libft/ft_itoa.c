/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: treis-ro <treis-ro@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:27:28 by treis-ro          #+#    #+#             */
/*   Updated: 2023/10/31 16:10:02 by treis-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	leng(long x)
{
	size_t	size;

	size = 0;
	while (x > 9)
	{
		x /= 10;
		size++;
	}
	return (size + 1);
}

char	*build(size_t size, long k, char *res)
{
	int	i;

	i = size - 1;
	if (k == 0)
		res[i--] = k + '0';
	else
	{
		while (i >= 0)
		{
			if (k > 0)
				res[i--] = (k % 10) + '0';
			else
				res[i--] = '-';
			k /= 10;
		}
	}
	res[size] = '\0';
	return (res);
}

char	*ft_itoa(int n)
{
	char	*res;
	size_t	size;
	long	k;

	k = n;
	size = 0;
	if (k < 0)
	{
		k *= -1;
		size++;
	}
	size += leng(k);
	res = (char *)malloc((size + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	res = build(size, k, res);
	return (res);
}
