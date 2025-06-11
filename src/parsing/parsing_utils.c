/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: treis-ro <treis-ro@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:22:04 by treis-ro          #+#    #+#             */
/*   Updated: 2025/06/06 03:33:03 by treis-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_tokens(t_shell *shell)
{
	t_token	*tmp;

	while (shell->tokens)
	{
		tmp = shell->tokens;
		if (shell->tokens->value)
		{
			free(shell->tokens->value);
			shell->tokens->value = NULL;
		}
		shell->tokens = tmp->next;
		free(tmp);
	}
	shell->tokens = NULL;
}

int	special_char(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

char	**ft_realloc(char **ptr, size_t size)
{
	char	**new_ptr;
	size_t	i;

	new_ptr = ft_calloc(size + 1, sizeof(char *));
	if (!new_ptr)
		return (NULL);
	i = 0;
	if (ptr)
	{
		while (ptr[i])
		{
			new_ptr[i] = ptr[i];
			i++;
		}
		free(ptr);
	}
	new_ptr[i] = NULL;
	return (new_ptr);
}

void	free_char_array(char **tokens)
{
	size_t	i;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

int	check_quotes(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\"')
		{
			i++;
			while (input[i] && input[i] != '\"')
				i++;
			if (input[i] == '\0')
				return (-1);
		}
		if (input[i] == '\'')
		{
			i++;
			while (input[i] && input[i] != '\'')
				i++;
			if (input[i] == '\0')
				return (-1);
		}
		i++;
	}
	return (0);
}
