/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumiguel <lumiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 03:21:08 by treis-ro          #+#    #+#             */
/*   Updated: 2025/06/06 12:43:20 by lumiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	print_error(char *str, int err_code)
{
	ft_putstr_fd(str, STDERR_FILENO);
	return (err_code);
}

int	is_whitespace(char c)
{
	if ((c <= 13 && c >= 9) || c == 32)
		return (1);
	return (0);
}
