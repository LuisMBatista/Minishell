/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumiguel <lumiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:03:37 by lumiguel          #+#    #+#             */
/*   Updated: 2025/06/10 11:53:20 by lumiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	child_ft_handler(t_cmd *cmd, t_pipex *pipex)
{
	if (cmd->fd[1] != STDOUT_FILENO)
		dup2(cmd->fd[1], STDOUT_FILENO);
	if (cmd->fd[0] != STDIN_FILENO)
		dup2(cmd->fd[0], STDIN_FILENO);
	if (cmd->fd[0] > 2)
		close(cmd->fd[0]);
	if (cmd->fd[1] > 2)
		close(cmd->fd[1]);
	if (pipex->prev_fd > 2)
		close(pipex->prev_fd);
	if (pipex->pipe_fd[0] > 2)
		close(pipex->pipe_fd[0]);
	if (pipex->pipe_fd[1] > 2)
		close(pipex->pipe_fd[1]);
	if (pipex->shell->stdin_backup > 2)
		close(pipex->shell->stdin_backup);
	if (pipex->shell->stdout_backup > 2)
		close(pipex->shell->stdout_backup);
}

void	close_child_fds(t_pipex *pipex)
{
	if (pipex->pipe_fd[0] > 2)
		close(pipex->pipe_fd[0]);
	if (pipex->pipe_fd[1] > 2)
		close(pipex->pipe_fd[1]);
	if (pipex->prev_fd > 2)
		close(pipex->prev_fd);
}
