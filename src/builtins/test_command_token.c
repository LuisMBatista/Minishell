/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cmd_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: treis-ro <treis-ro@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:19:37 by lumiguel          #+#    #+#             */
/*   Updated: 2025/05/29 03:32:32 by treis-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtin(t_cmd *cmd, t_shell *shell)
{
	if (cmd->cmd[0] == NULL)
		return (0);
	if (ft_strcmp(cmd->cmd[0], "echo") == 0)
		return (ft_echo(cmd->cmd, 0));
	else if (ft_strcmp(cmd->cmd[0], "cd") == 0)
		return (ft_cd(cmd->cmd));
	else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(cmd->cmd[0], "export") == 0)
		return (ft_export(cmd->cmd, shell->env));
	else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
		return (ft_unset(&shell->env, shell->commands->cmd));
	else if (ft_strcmp(cmd->cmd[0], "env") == 0)
		return (ft_env_cmd(shell->env, cmd));
	return (0);
}

int	builtin_check(t_cmd *cmd)
{
	if (!cmd->cmd)
		return (0);
	if (ft_strcmp(cmd->cmd[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd[0], "export") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd[0], "env") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
		return (1);
	return (0);
}
