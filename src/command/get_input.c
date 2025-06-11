/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: treis-ro <treis-ro@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 00:25:18 by treis-ro          #+#    #+#             */
/*   Updated: 2025/06/10 01:33:52 by treis-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exit_heredoc(char *line, char *del, size_t del_size, t_shell *shell)
{
	if (!line)
	{
		ft_putstr_fd("warning: here-document delimited by EOF (wanted `",
			STDERR_FILENO);
		ft_putstr_fd(del, STDERR_FILENO);
		ft_putstr_fd("')\n", STDERR_FILENO);
		cleanup_shell(shell);
		return (1);
	}
	if (ft_strlen(line) == del_size && !ft_strncmp(line, del, del_size))
	{
		free(line);
		cleanup_shell(shell);
		return (1);
	}
	return (0);
}

int	no_quote_heredoc(t_val *val, char *line, t_shell *shell)
{
	int	cb;

	cb = BUFFER_SIZE;
	while (line[val->i])
	{
		if (val->j >= cb - 1)
		{
			cb *= 2;
			val->real_value = realloc_value(val->real_value, cb / 2, cb);
			if (!val->real_value)
				return (free(line), FATAL_ERR);
		}
		if (line[val->i] == '$')
		{
			if (!process_var(val, line, shell))
			{
				free(val->real_value);
				return (free(line), FATAL_ERR);
			}
		}
		else
			val->real_value[val->j++] = line[val->i++];
	}
	val->real_value[val->j] = '\0';
	return (SUCCESS);
}

int	quoted_heredoc(t_val *val, char *line)
{
	free(val->real_value);
	val->real_value = ft_strdup(line);
	if (!val->real_value)
	{
		free(line);
		return (FATAL_ERR);
	}
	val->j = ft_strlen(val->real_value);
	return (SUCCESS);
}

int	heredoc_line(int quote, t_val *val, char *line, t_shell *shell)
{
	if (quote == 0)
	{
		if (no_quote_heredoc(val, line, shell) == FATAL_ERR)
			return (FATAL_ERR);
	}
	else
	{
		if (quoted_heredoc(val, line) == FATAL_ERR)
			return (FATAL_ERR);
	}
	return (SUCCESS);
}

int	get_here_input(t_shell *shell, char *del, int *pipe_fds, int quote)
{
	char	*line;
	t_val	val;
	size_t	del_size;

	del_size = ft_strlen(del);
	while (1)
	{
		init_val(&val);
		if (!val.real_value)
			return (FATAL_ERR);
		line = readline("> ");
		if (exit_heredoc(line, del, del_size, shell))
			break ;
		if (heredoc_line(quote, &val, line, shell) == FATAL_ERR)
			return (FATAL_ERR);
		write(pipe_fds[1], val.real_value, val.j);
		write(pipe_fds[1], "\n", 1);
		free(line);
		free(val.real_value);
	}
	close(pipe_fds[1]);
	free(val.real_value);
	return (SUCCESS);
}
