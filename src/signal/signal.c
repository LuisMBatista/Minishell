/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumiguel <lumiguel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 23:00:30 by lumiguel          #+#    #+#             */
/*   Updated: 2025/06/05 23:01:56 by lumiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

void	putendl_fd(char *s, int fd)
{
	if (s)
	{
		write(fd, s, strlen(s));
		write(fd, "\n", 1);
	}
}

void	sig_int(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_signal = 130;
}

void	sig_quit(int code, t_pipex *pipex)
{
	char	*nbr;

	nbr = ft_itoa(code);
	if (pipex->pid != 0)
	{
		putstr_fd("exit: ", STDERR);
		putendl_fd(nbr, STDERR);
		g_exit_signal = 1;
	}
	else
		putstr_fd("\b\b  \b\b", STDERR);
	free(nbr);
	nbr = NULL;
}

void	display_prompt_msg(void)
{
	char	*cwd;
	char	buff[4096 + 1];

	cwd = getcwd(buff, 4096);
	putstr_fd(cwd, 1);
	free(cwd);
}
