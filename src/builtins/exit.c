/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumiguel <lumiguel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:48:32 by treis-ro          #+#    #+#             */
/*   Updated: 2025/06/05 10:41:10 by lumiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_numeric(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '+' || s[0] == '-')
		i++;
	if (s[i] == '\0')
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	exit_shell(char	**args, int *flag)
{
	long	code;

	*flag = 0;
	if (!args[1])
		return (SUCCESS);
	if (!is_numeric(args[1]))
	{
		ft_putendl_fd(" numeric argument required", STDERR_FILENO);
		return (SYNTAX_ERR);
	}
	if (args[2])
	{
		*flag = 1;
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		return (FATAL_ERR);
	}
	code = ft_atoi(args[1]);
	return ((int)code);
}
