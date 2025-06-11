/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: treis-ro <treis-ro@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:03:53 by treis-ro          #+#    #+#             */
/*   Updated: 2023/10/12 15:39:43 by treis-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *str, unsigned int n)
{
	unsigned int	i;
	unsigned char	*m;

	i = 0;
	m = str;
	while (i < n)
		m[i++] = '\0';
}
