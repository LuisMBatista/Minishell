/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: treis-ro <treis-ro@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 02:07:37 by treis-ro          #+#    #+#             */
/*   Updated: 2025/06/06 03:45:02 by treis-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	var_creation_check(char *token)
{
	int	i;

	i = 0;
	if (!token || *token == '=' || ft_isdigit(*token))
		return (0);
	while (token[i] && token[i] != '=')
	{
		if (!ft_isalnum(token[i]) && token[i] != '_')
			return (0);
		i++;
	}
	if (token[i] == '=')
		return (1);
	return (0);
}

int	token_type(char *token)
{
	if ((ft_strncmp(token, ">", 2) == 0 || ft_strncmp(token, ">>", 3) == 0))
		return (TOKEN_REDIRECT);
	if ((ft_strncmp(token, "<", 2) == 0 || ft_strncmp(token, "<<", 3) == 0))
		return (TOKEN_REDIRECT);
	if (ft_strncmp(token, "|", 2) == 0)
		return (TOKEN_PIPE);
	if (var_creation_check(token))
		return (TOKEN_ENV);
	return (TOKEN_CMD);
}

int	check_valid_input(t_shell *shell, char *input)
{
	if (input[0] && !is_whitespace(input[0])
		&& (!shell->last_input || ft_strcmp(input, shell->last_input) != 0))
	{
		add_history(input);
		free(shell->last_input);
		shell->last_input = ft_strdup(input);
	}
	if (check_quotes(input) == -1)
	{
		ft_putstr_fd("unclosed quotes\n", STDERR_FILENO);
		free(input);
		return (SYNTAX_ERR);
	}
	return (SUCCESS);
}

int	create_token_node(t_shell *shell, t_token **current, char *str)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (-1);
	new->value = ft_strdup(str);
	if (!new->value)
	{
		free(new);
		return (-1);
	}
	new->type = token_type(new->value);
	new->expand = 0;
	new->next = NULL;
	new->prev = *current;
	if (!shell->tokens)
		shell->tokens = new;
	else
		(*current)->next = new;
	*current = new;
	return (0);
}
