/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: treis-ro <treis-ro@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:52:25 by treis-ro          #+#    #+#             */
/*   Updated: 2023/10/13 19:46:19 by treis-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	srcsize;
	size_t	dstsize;
	size_t	offset;

	dstsize = ft_strlen(dst);
	srcsize = ft_strlen(src);
	offset = 0;
	if (size < 1)
		return (srcsize + size);
	while (src[offset] && (dstsize + offset) < size - 1)
	{
		dst[offset + dstsize] = src[offset];
		offset++;
	}
	dst[offset + dstsize] = '\0';
	if (size < dstsize)
		return (srcsize + size);
	else
		return (dstsize + srcsize);
}
