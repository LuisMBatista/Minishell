/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumiguel <lumiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:53:46 by lumiguel          #+#    #+#             */
/*   Updated: 2025/06/09 16:09:02 by lumiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_path(char **env, char *cmd)
{
	char	*cmd_with_slash;
	char	*final_path;

	if (cmd == NULL)
	{
		ft_putstr_fd("Error: cmd empty\n", STDERR_FILENO);
		exit(FATAL_ERR);
	}
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
		{
			if (access(cmd, X_OK) == 0)
				return (cmd);
			errno = EACCES;
		}
		else
			errno = ENOENT;
		return (NULL);
	}
	cmd_with_slash = ft_strjoin("/", cmd);
	final_path = get_right_path(env, cmd_with_slash);
	free(cmd_with_slash);
	return (final_path);
}

char	*get_right_path(char **env, char *cmd_with_slash)
{
	int		i;
	char	**path;
	char	*full_path;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = ft_split(env[i] + 5, ':');
			if (!path)
				return (NULL);
			full_path = try_paths(path, cmd_with_slash);
			free_char_array(path);
			return (full_path);
		}
		i++;
	}
	errno = ENOENT;
	return (NULL);
}

char	*try_paths(char **path, char *cmd_with_slash)
{
	int		j;
	int		exec;
	char	*potential_path;

	j = 0;
	exec = ENOENT;
	while (path[j] != NULL)
	{
		potential_path = ft_strjoin(path[j], cmd_with_slash);
		if (!potential_path)
		{
			errno = ENOMEM;
			return (NULL);
		}
		if (access(potential_path, F_OK) == 0)
		{
			if (access(potential_path, X_OK) == 0)
				return (potential_path);
			exec = EACCES;
		}
		free(potential_path);
		j++;
	}
	errno = exec;
	return (NULL);
}

size_t	count_cmds(t_cmd *cmd)
{
	size_t	n;

	n = 0;
	while (cmd)
	{
		n++;
		cmd = cmd->next;
	}
	return (n);
}

void	init_pipe(t_pipex *pipex, t_shell *shell)
{
	pipex->fd = -1;
	pipex->pid = -1;
	pipex->prev_fd = STDIN_FILENO;
	pipex->pipe_fd[0] = -1;
	pipex->pipe_fd[1] = -1;
	pipex->in_fd = STDIN_FILENO;
	pipex->out_fd = STDOUT_FILENO;
	pipex->i = 0;
	pipex->shell = shell;
}
