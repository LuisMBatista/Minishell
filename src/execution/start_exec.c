/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumiguel <lumiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 02:52:36 by treis-ro          #+#    #+#             */
/*   Updated: 2025/06/10 11:11:07 by lumiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	special_exit(t_shell *shell)
{
	int	status;
	int	flag;

	ft_putendl_fd("exit", STDOUT_FILENO);
	status = exit_shell(shell->commands->cmd, &flag);
	if (status != FATAL_ERR || (status == FATAL_ERR && flag == 0))
	{
		if (status != SUCCESS)
			g_exit_signal = status;
		cleanup_shell(shell);
		exit(status);
	}
	return (status);
}

int	exec_command_type(t_shell *shell)
{
	int				status;
	t_redirection	*r;

	status = SUCCESS;
	if (builtin_check(shell->commands))
	{
		r = shell->commands->redir;
		while (r && status == SUCCESS)
		{
			if (apply_redirections(shell->commands, r) != SUCCESS)
				status = FATAL_ERR;
			r = r->next;
		}
		if (status != SUCCESS)
			return (status);
		if (shell->commands->fd[0] != STDIN_FILENO)
			dup2(shell->commands->fd[0], STDIN_FILENO);
		if (shell->commands->fd[1] != STDOUT_FILENO)
			dup2(shell->commands->fd[1], STDOUT_FILENO);
		if (ft_strcmp(shell->commands->cmd[0], "exit") == 0)
			return (special_exit(shell));
		return (builtin(shell->commands, shell));
	}
	return (execute_pipeline(shell->commands, shell));
}

int	exec_single_cmd(t_shell *shell)
{
	int				status;
	t_redirection	*r;

	status = SUCCESS;
	if (!shell->commands->cmd && shell->commands->env)
		status = add_shell_vars(shell, shell->commands->env);
	if (status != SUCCESS)
		return (status);
	if (!shell->commands->cmd && shell->commands->redir)
	{
		r = shell->commands->redir;
		while (r && status == SUCCESS)
		{
			if (apply_redirections(shell->commands, r) != SUCCESS)
				status = FATAL_ERR;
			r = r->next;
		}
	}
	if (status != SUCCESS)
		return (status);
	if (shell->commands->cmd)
		return (exec_command_type(shell));
	return (SUCCESS);
}

int	start_exec(t_shell *shell)
{
	if (!shell->commands->next)
		return (exec_single_cmd(shell));
	return (execute_pipeline(shell->commands, shell));
}
