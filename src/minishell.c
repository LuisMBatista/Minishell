/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: treis-ro <treis-ro@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:45:13 by treis-ro          #+#    #+#             */
/*   Updated: 2025/06/06 21:17:50 by treis-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile sig_atomic_t	g_exit_signal = 0;

int	main(int ac, char **av, char **env)
{
	static t_shell	shell;
	int				status;

	(void)ac;
	(void)av;
	signal(SIGINT, sig_int);
	signal(SIGQUIT, SIG_IGN);
	shell_init(&shell, env);
	while (1)
	{
		status = parse_main(&shell);
		if (status == EOF_CODE)
		{
			g_exit_signal = SUCCESS;
			break ;
		}
		if (status == SUCCESS && shell.commands)
			g_exit_signal = start_exec(&shell);
		else
			g_exit_signal = status;
		free_shell(&shell);
	}
	cleanup_shell(&shell);
	return (g_exit_signal & 0xFF);
}
