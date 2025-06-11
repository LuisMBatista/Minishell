/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumiguel <lumiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:29:03 by treis-ro          #+#    #+#             */
/*   Updated: 2025/06/10 11:51:45 by lumiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	child_process(t_cmd *cmd, t_pipex *pipex, t_shell *shell)
{
	t_redirection	*r;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	if (cmd->next)
		dup2(pipex->pipe_fd[1], STDOUT_FILENO);
	if (pipex->prev_fd != STDIN_FILENO)
		dup2(pipex->prev_fd, STDIN_FILENO);
	r = cmd->redir;
	while (r)
	{
		if (apply_redirections(cmd, r) != SUCCESS)
		{
			close_child_fds(pipex);
			cleanup_shell(shell);
			exit(FATAL_ERR);
		}
		r = r->next;
	}
	child_ft_handler(cmd, pipex);
	if (cmd->cmd)
		(ft_execve(cmd, shell));
	cleanup_shell(shell);
	exit(EXIT_SUCCESS);
}

int	ft_final_status(t_shell *shell, int last_status)
{
	size_t	i;
	int		status;

	i = 0;
	while (i < shell->n_pids)
	{
		waitpid(shell->pids[i], &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			ft_putchar_fd('\n', STDERR_FILENO);
			signal(SIGINT, sig_int);
			signal(SIGQUIT, SIG_IGN);
			cleanup_shell(shell);
			free(shell->pids);
			shell->pids = NULL;
			shell->n_pids = 0;
			return (SIGINT_ERR);
		}
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			last_status = INVALID_EXIT + WTERMSIG(status);
		i++;
	}
	return (last_status);
}

//Osso da execução, filho lá no meio
int	ft_exec_core(t_cmd *cmd, t_shell *shell)
{
	t_pipex	pipex;
	pid_t	pid;

	init_pipe(&pipex, shell);
	while (cmd)
	{
		if (cmd->next && pipe(pipex.pipe_fd) == -1)
			return (perror("pipe"), FATAL_ERR);
		pid = fork();
		if (pid < 0)
			return (perror("fork"), FATAL_ERR);
		if (pid == 0)
			child_process(cmd, &pipex, shell);
		shell->pids[shell->n_pids++] = pid;
		if (pipex.prev_fd > 2)
			close(pipex.prev_fd);
		if (cmd->next)
		{
			pipex.prev_fd = pipex.pipe_fd[0];
			close(pipex.pipe_fd[1]);
		}
		cmd = cmd->next;
	}
	return (SUCCESS);
}

int	execute_pipeline(t_cmd *cmd, t_shell *shell)
{
	int	last_status;

	shell->pids = malloc(count_cmds(cmd) * sizeof(pid_t));
	if (!shell->pids)
		return (FATAL_ERR);
	shell->n_pids = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	last_status = 0;
	if (ft_exec_core(cmd, shell))
		return (FATAL_ERR);
	last_status = ft_final_status(shell, last_status);
	signal(SIGINT, sig_int);
	signal(SIGQUIT, SIG_IGN);
	free(shell->pids);
	shell->pids = NULL;
	shell->n_pids = 0;
	return (last_status);
}
