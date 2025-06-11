/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: treis-ro <treis-ro@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:52:55 by treis-ro          #+#    #+#             */
/*   Updated: 2025/06/10 00:31:19 by treis-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

pid_t	p_f_heredoc(int pipe_fds[2])
{
	pid_t	pid;

	if (pipe(pipe_fds) == -1)
	{
		perror("pipe");
		return (-1);
	}
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		signal(SIGINT, sig_int);
		return (-1);
	}
	return (pid);
}

void	here_child(int pipe_fds[2], char *del, int *quote, t_shell *shell)
{
	int	status;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	close(pipe_fds[0]);
	free_shell(shell);
	cleanup_shell(shell);
	status = get_here_input(shell, del, pipe_fds, *quote);
	close(pipe_fds[1]);
	free(del);
	exit(status);
}

int	here_papa(pid_t pid, int pipe_fds[2], char *delimiter)
{
	int	status;

	close(pipe_fds[1]);
	waitpid(pid, &status, 0);
	signal(SIGINT, sig_int);
	signal(SIGQUIT, SIG_IGN);
	free(delimiter);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(pipe_fds[0]);
		ft_putchar_fd('\n', STDERR_FILENO);
		return (SIGINT_ERR);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) != SUCCESS)
	{
		close(pipe_fds[0]);
		return (FATAL_ERR);
	}
	return (SUCCESS);
}

int	redir_heredoc(t_redirection *r, t_token *token, t_shell *shl, t_cmd *cmd)
{
	int		pipe_fds[2];
	char	*del;
	int		quote;
	pid_t	pid;
	int		res;

	del = remove_quotes(token->next, &quote);
	if (!del)
		return (FATAL_ERR);
	pid = p_f_heredoc(pipe_fds);
	if (pid < 0)
		return (free(del), FATAL_ERR);
	if (pid == 0)
	{
		free_redirection(r);
		free_ucommands(cmd);
		here_child(pipe_fds, del, &quote, shl);
	}
	res = here_papa(pid, pipe_fds, del);
	if (res != SUCCESS)
		return (res);
	r->fd = pipe_fds[0];
	r->type = HEREDOC;
	return (SUCCESS);
}
