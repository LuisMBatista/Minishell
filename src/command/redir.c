/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumiguel <lumiguel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:58:33 by treis-ro          #+#    #+#             */
/*   Updated: 2025/06/05 14:17:31 by lumiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	redir_check(t_redirection *r)
{
	if (r->type != HEREDOC)
	{
		if (ft_strlen(r->file) > 255)
		{
			ft_putstr_fd("File name too long\n", STDERR_FILENO);
			return (FATAL_ERR);
		}
		if (r->type == INPUT)
		{
			if (access(r->file, F_OK) == -1)
			{
				ft_putstr_fd(" No such file or directory\n", STDERR_FILENO);
				return (FATAL_ERR);
			}
			if (access(r->file, R_OK) == -1)
			{
				ft_putstr_fd("Permission denied\n", STDERR_FILENO);
				return (FATAL_ERR);
			}
		}
	}
	return (SUCCESS);
}

int	apply_redirections(t_cmd *cmd, t_redirection *r)
{
	int	fd;

	if (redir_check(r) != SUCCESS)
		return (FATAL_ERR);
	if (r->type == HEREDOC)
		fd = r->fd;
	else if (r->type == INPUT)
		fd = open(r->file, O_RDONLY);
	else if (r->type == APPEND)
		fd = open(r->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd = open(r->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(r->file);
		return (FATAL_ERR);
	}
	r->fd = fd;
	if (r->type == APPEND || r->type == OUTPUT)
		cmd->fd[1] = fd;
	else
		cmd->fd[0] = fd;
	return (SUCCESS);
}

void	append_redir(t_cmd *cmd, t_redirection *r)
{
	t_redirection	**head;
	t_redirection	*tmp;

	head = &cmd->redir;
	if (*head == NULL)
		*head = r;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = r;
	}
}

int	redir_prepare(t_redirection *r, t_token *token, t_shell *shell)
{
	char	*name;

	name = find_real_value(token->next, shell);
	if (!name)
		return (FATAL_ERR);
	if (ft_strcmp(token->value, ">>") == 0)
		r->type = APPEND;
	else if (ft_strcmp(token->value, ">") == 0)
		r->type = OUTPUT;
	else
		r->type = INPUT;
	r->file = name;
	r->fd = -1;
	r->next = NULL;
	return (SUCCESS);
}

int	add_redirection(t_cmd *cmd, t_token *token, t_shell *shell)
{
	t_redirection	*r;
	int				status;

	r = malloc(sizeof(t_redirection));
	if (!r)
		return (FATAL_ERR);
	r->next = NULL;
	r->fd = -1;
	r->file = NULL;
	if (ft_strcmp(token->value, "<<") == 0)
	{
		status = redir_heredoc(r, token, shell, cmd);
		if (status != SUCCESS)
			return (free(r), status);
	}
	else
	{
		status = redir_prepare(r, token, shell);
		if (status != SUCCESS)
			return (free(r), status);
	}
	append_redir(cmd, r);
	return (SUCCESS);
}
