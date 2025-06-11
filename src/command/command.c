/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumiguel <lumiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 19:28:30 by treis-ro          #+#    #+#             */
/*   Updated: 2025/06/10 11:31:34 by lumiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*realloc_value(char *old_value, int old_size, int new_size)
{
	char	*new_value;
	int		i;

	if (!old_value)
		return (malloc(new_size * sizeof(char)));
	if (new_size <= old_size)
		return (old_value);
	new_value = malloc(new_size * sizeof(char));
	if (!new_value)
		return (NULL);
	i = 0;
	while (i < old_size)
	{
		((unsigned char *)new_value)[i] = ((unsigned char *)old_value)[i];
		i++;
	}
	free(old_value);
	return (new_value);
}

void	init_val(t_val *val)
{
	val->buffer_size = BUFFER_SIZE;
	val->i = 0;
	val->j = 0;
	val->real_value = malloc(BUFFER_SIZE * sizeof(char));
	if (!val->real_value)
		return ;
	val->real_value[0] = '\0';
}

char	*find_real_value(t_token *token, t_shell *shell)
{
	t_val	val;

	init_val(&val);
	if (!val.real_value)
		return (NULL);
	if (token->value[val.i] == '~'
		&& (token->value[val.i + 1] == '\0' || token->value[val.i + 1] == '/'))
	{
		val.real_value = tild_expansion(val.real_value, &val.j, &val.i, shell);
		if (!val.real_value)
			return (NULL);
	}
	while (token->value[val.i])
	{
		if (!handle_token_value(&val, token, shell))
		{
			free(val.real_value);
			return (NULL);
		}
	}
	return (val.real_value);
}

int	add_token_to_command(t_shell *shell, t_cmd **cmd,
	t_cmd **cmd_list, t_token **token)
{
	if ((*token)->type == TOKEN_CMD)
		return (add_to_command_argument(*cmd, *token, shell));
	else if ((*token)->type == TOKEN_ENV)
		return (add_to_command_env(*cmd, *token, shell));
	else if ((*token)->type == TOKEN_REDIRECT)
	{
		*token = (*token)->next;
		return (add_redirection(*cmd, (*token)->prev, shell));
	}
	else if ((*token)->type == TOKEN_PIPE)
	{
		cmd_lstadd_back(cmd_list, *cmd);
		*cmd = NULL;
	}
	return (SUCCESS);
}

int	parse_tokens_into_commands(t_shell *shell, int status, t_token *token)
{
	t_cmd	*cmd_list;
	t_cmd	*cmd;

	cmd_list = NULL;
	cmd = NULL;
	while (token && status == SUCCESS)
	{
		if (!cmd && (!token->prev || token->prev->type == TOKEN_PIPE))
			cmd = init_cmd();
		if (!cmd)
			return (FATAL_ERR);
		status = add_token_to_command(shell, &cmd, &cmd_list, &token);
		token = token->next;
	}
	if (status != SUCCESS)
	{
		free_commands(shell);
		return (status);
	}
	if (cmd)
		cmd_lstadd_back(&cmd_list, cmd);
	else
		return (FATAL_ERR);
	shell->commands = cmd_list;
	return (SUCCESS);
}
