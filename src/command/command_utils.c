/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: treis-ro <treis-ro@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:08:25 by treis-ro          #+#    #+#             */
/*   Updated: 2025/06/10 00:55:51 by treis-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = NULL;
	cmd->env = NULL;
	cmd->redir = NULL;
	cmd->prev_fd = STDIN_FILENO;
	cmd->fd[0] = STDIN_FILENO;
	cmd->fd[1] = STDOUT_FILENO;
	cmd->next = NULL;
	return (cmd);
}

void	cmd_lstadd_back(t_cmd **cmd_list, t_cmd *new_cmd)
{
	t_cmd	*tmp;

	if (!cmd_list || !new_cmd)
		return ;
	if (*cmd_list == NULL)
		*cmd_list = new_cmd;
	else
	{
		tmp = *cmd_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_cmd;
	}
}

char	**command_realloc(char **old_cmd, size_t new_size)
{
	char	**new_cmd;
	size_t	i;

	i = 0;
	new_cmd = malloc(new_size);
	if (!new_cmd)
		return (NULL);
	if (old_cmd)
	{
		while (old_cmd[i])
		{
			new_cmd[i] = old_cmd[i];
			i++;
		}
		free(old_cmd);
	}
	new_cmd[i] = NULL;
	return (new_cmd);
}

int	add_to_command_argument(t_cmd *cmd, t_token *token, t_shell *shell)
{
	char	*expanded_value;
	int		count;
	char	**new_cmd;

	count = 0;
	expanded_value = find_real_value(token, shell);
	if (!expanded_value)
		return (FATAL_ERR);
	if (cmd->cmd)
	{
		while (cmd->cmd[count])
			count++;
	}
	new_cmd = command_realloc(cmd->cmd, sizeof(char *) * (count + 2));
	if (!new_cmd)
		return (free(expanded_value), FATAL_ERR);
	new_cmd[count] = expanded_value;
	new_cmd[count + 1] = NULL;
	cmd->cmd = new_cmd;
	return (SUCCESS);
}

int	quote_expand(char quote, int expand)
{
	if (expand == 0)
	{
		if (quote == '\'')
			return (1);
		else
			return (2);
	}
	else
		return (0);
}
