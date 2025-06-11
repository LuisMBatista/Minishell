/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumiguel <lumiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:00:53 by lumiguel          #+#    #+#             */
/*   Updated: 2025/06/10 11:37:01 by lumiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_flag(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-' || str[1] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(char **args, int n_flag)
{
	int	i;
	int	first;

	i = 1;
	while (args[i] && is_flag(args[i]))
	{
		n_flag = 1;
		i++;
	}
	first = 1;
	while (args[i])
	{
		if (!first)
			write(STDOUT_FILENO, " ", 1);
		else
			first = 0;
		write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		i++;
	}
	if (!n_flag)
		write(STDOUT_FILENO, "\n", 1);
	return (SUCCESS);
}

int	ft_cd(char **args)
{
	char	cwd[1024];

	if (args[2])
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return (FATAL_ERR);
	}
	if (!args[1])
	{
		if (chdir(getenv("HOME")) != 0)
		{
			ft_putstr_fd("Failed to find HOME\n", STDERR_FILENO);
			return (FATAL_ERR);
		}
	}
	else if (chdir(args[1]) != 0)
	{
		ft_putstr_fd(" No such file or directory\n", STDERR_FILENO);
		return (FATAL_ERR);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		return (SUCCESS);
	else
		ft_putstr_fd("getcwd() error\n", STDERR_FILENO);
	return (FATAL_ERR);
}

int	ft_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putstr_fd(cwd, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (SUCCESS);
	}
	else
	{
		ft_putstr_fd("pwd failed\n", STDERR_FILENO);
		return (FATAL_ERR);
	}
}

int	ft_unset(t_env **env, char **keys)
{
	int	i;

	i = 1;
	if (!keys[i])
	{
		return (SUCCESS);
	}
	unset_env(i, keys, *env);
	return (SUCCESS);
}
