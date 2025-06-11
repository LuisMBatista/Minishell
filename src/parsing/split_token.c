/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: treis-ro <treis-ro@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:55:46 by treis-ro          #+#    #+#             */
/*   Updated: 2025/06/06 03:42:51 by treis-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_special_token(char **input)
{
	char	*start;
	char	redir;

	start = *input;
	if (**input == '|')
	{
		(*input)++;
	}
	else if (**input == '>' || **input == '<')
	{
		redir = **input;
		(*input)++;
		if (**input == redir)
			(*input)++;
	}
	return (ft_substr(start, 0, *input - start));
}

static char	*get_basic_token(char **input)
{
	char	*start;
	char	*token;
	char	quote;

	start = *input;
	quote = '\0';
	while ((**input && !is_whitespace(**input) && !special_char(**input))
		|| quote != '\0')
	{
		if (quote && **input == quote)
			quote = '\0';
		else if (quote == '\0' && (**input == '\'' || **input == '\"'))
			quote = **input;
		(*input)++;
	}
	token = ft_substr(start, 0, *input - start);
	return (token);
}

char	*get_token(char **input)
{
	if (special_char(**input))
		return (get_special_token(input));
	return (get_basic_token(input));
}

static int	process_next_token(char **input, char ***tokens,
								int *token_count, int *capacity)
{
	char	*token;

	while (*input && is_whitespace(**input))
		(*input)++;
	if (**input == '\0')
		return (1);
	token = get_token(input);
	if (!token)
	{
		free_char_array(*tokens);
		return (-1);
	}
	(*tokens)[(*token_count)++] = token;
	if (*token_count == *capacity)
	{
		*capacity *= 2;
		*tokens = (char **)ft_realloc(*tokens, *capacity);
		if (!*tokens)
			return (-1);
	}
	return (0);
}

char	**split_input(char *input)
{
	char	**tokens;
	int		token_count;
	int		capacity;
	int		ret;

	token_count = 0;
	capacity = 4;
	tokens = ft_calloc(capacity + 1, sizeof(char *));
	if (!tokens)
		return (NULL);
	while (*input)
	{
		ret = process_next_token(&input, &tokens, &token_count, &capacity);
		if (ret == 1)
			break ;
		else if (ret == -1)
			return (NULL);
	}
	while (token_count < capacity)
		tokens[token_count++] = NULL;
	return (tokens);
}
