/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumiguel <lumiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:54:07 by lumiguel          #+#    #+#             */
/*   Updated: 2025/06/10 11:53:11 by lumiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	missing_path_exit(t_cmd *cmd, t_shell *shell, char **array, char *path)
{
	free_char_array(array);
	free(path);
	ft_putstr_fd(cmd->cmd[0], STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	cleanup_shell(shell);
	exit(CMD_NOT_FOUND);
}

void	error_handler_execve(int code, t_cmd *cmd, t_shell *shell, char **e_v)
{
	free_char_array(e_v);
	perror(cmd->cmd[0]);
	free(shell->path);
	cleanup_shell(shell);
	exit(code);
}

void	ftf_execve(char *path, t_cmd *cmd, char **exec_env, t_shell *shell)
{
	execve(path, cmd->cmd, exec_env);
	cleanup_shell(shell);
	perror(cmd->cmd[0]);
	if (errno == EACCES)
		exit(CANNOT_EXECUTE);
	if (errno == ENOENT)
		exit(CMD_NOT_FOUND);
	exit(CANNOT_EXECUTE);
}

void	handle_builtin(t_cmd *cmd, t_shell *shell)
{
	int	status;

	if (builtin_check(cmd))
	{
		status = builtin(cmd, shell);
		cleanup_shell(shell);
		exit(status);
	}
}

void	ft_execve(t_cmd *cmd, t_shell *shell)
{
	char			**exec_env;
	struct stat		st;

	handle_builtin(cmd, shell);
	exec_env = create_exec_env(shell->env, cmd->env);
	if (!exec_env)
		exit(FATAL_ERR);
	if (ft_strchr(cmd->cmd[0], '/'))
		shell->path = ft_strdup(cmd->cmd[0]);
	else
		shell->path = get_path(exec_env, cmd->cmd[0]);
	if (!shell->path || slash_check(shell->path))
		missing_path_exit(cmd, shell, exec_env, shell->path);
	if (stat(shell->path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		errno = EISDIR;
		error_handler_execve(CANNOT_EXECUTE, cmd, shell, exec_env);
	}
	if (access(shell->path, F_OK) != 0)
		error_handler_execve(CMD_NOT_FOUND, cmd, shell, exec_env);
	if (access(shell->path, X_OK) != 0)
		error_handler_execve(CANNOT_EXECUTE, cmd, shell, exec_env);
	ftf_execve(shell->path, cmd, exec_env, shell);
}
