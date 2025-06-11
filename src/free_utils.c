/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumiguel <lumiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:42:07 by treis-ro          #+#    #+#             */
/*   Updated: 2025/06/10 11:33:36 by lumiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_cmd_content(t_cmd *cmd)
{
	int	i;

	if (cmd->cmd)
	{
		i = 0;
		while (cmd->cmd[i])
			free(cmd->cmd[i++]);
		free(cmd->cmd);
	}
	if (cmd->redir)
		free_redirection(cmd->redir);
	if (cmd->env)
		free_env(cmd->env);
	if (cmd->fd[0] > 2)
		close(cmd->fd[0]);
	if (cmd->fd[1] > 2)
		close(cmd->fd[1]);
}

void	free_commands(t_shell *shell)
{
	t_cmd	*cmd;
	t_cmd	*tmp;

	cmd = shell->commands;
	while (cmd)
	{
		tmp = cmd->next;
		free_cmd_content(cmd);
		free(cmd);
		cmd = tmp;
	}
	shell->commands = NULL;
}

void	free_shell(t_shell *shell)
{
	if (shell->tokens)
	{
		free_tokens(shell);
		shell->tokens = NULL;
	}
	if (shell->commands)
	{
		free_commands(shell);
		shell->commands = NULL;
	}
	if (shell->pids)
	{
		free(shell->pids);
		shell->pids = NULL;
		shell->n_pids = 0;
	}
	if (shell->last_input)
	{
		free(shell->last_input);
		shell->last_input = NULL;
	}
	dup2(shell->stdin_backup, STDIN_FILENO);
	dup2(shell->stdout_backup, STDOUT_FILENO);
}

void	free_redirection(t_redirection *r)
{
	t_redirection	*tmp;

	while (r)
	{
		tmp = r->next;
		if (r->file)
			free(r->file);
		if (r->fd > 2)
			close(r->fd);
		free(r);
		r = tmp;
	}
}

void	cleanup_shell(t_shell *shell)
{
	free_shell(shell);
	if (shell->env)
	{
		free_env(shell->env);
		shell->env = NULL;
	}
	if (shell->shell_vars)
	{
		free_env(shell->shell_vars);
		shell->shell_vars = NULL;
	}
	if (shell->stdin_backup > 2)
		close(shell->stdin_backup);
	if (shell->stdout_backup > 2)
		close(shell->stdout_backup);
	if (shell->last_input)
	{
		free(shell->last_input);
		shell->last_input = NULL;
	}
	clear_history();
}
