/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: treis-ro <treis-ro@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:57:59 by treis-ro          #+#    #+#             */
/*   Updated: 2025/06/10 00:56:39 by treis-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*tild_expansion(char *real_value, int *j, int *i, t_shell *shell)
{
	char	*expanded_var;

	expanded_var = find_home_env(shell);
	if (!expanded_var)
	{
		free(real_value);
		return (NULL);
	}
	*j = ft_strlen(expanded_var);
	ft_memcpy(real_value, expanded_var, *j);
	real_value[*j] = '\0';
	(*i)++;
	free(expanded_var);
	return (real_value);
}

char	*handle_quotes(t_token *token, char *real_value, int *j, int *i)
{
	char	c;

	c = token->value[*i];
	if (token->expand == 1 && c == '\"')
		real_value[(*j)++] = c;
	else if (token->expand == 2 && c == '\'')
		real_value[(*j)++] = c;
	else
		token->expand = quote_expand(c, token->expand);
	(*i)++;
	real_value[*j] = '\0';
	return (real_value);
}

char	*process_var(t_val *val, char *token, t_shell *shell)
{
	char	*expanded_var;
	int		exp_len;

	expanded_var = expand_var(token, &val->i, shell);
	if (!expanded_var)
		return (NULL);
	exp_len = ft_strlen(expanded_var);
	if (exp_len + val->j >= val->buffer_size)
	{
		val->real_value = resize_buffer(val->real_value, &val->buffer_size);
		if (!val->real_value)
		{
			free(expanded_var);
			return (NULL);
		}
	}
	ft_memcpy(val->real_value + val->j, expanded_var, exp_len);
	val->j += exp_len;
	val->real_value[val->j] = '\0';
	free(expanded_var);
	return (val->real_value);
}

int	should_process(char c)
{
	if (c && (c == '?' || (ft_isalnum(c) || c == '_')))
	{
		return (1);
	}
	return (0);
}

char	*handle_token_value(t_val *val, t_token *token, t_shell *shell)
{
	char	*res;

	if (val->j + 1 >= val->buffer_size)
	{
		val->real_value = resize_buffer(val->real_value, &val->buffer_size);
		if (!val->real_value)
			return (NULL);
	}
	if (token->value[val->i] == '\'' || token->value[val->i] == '\"')
		res = handle_quotes(token, val->real_value, &val->j, &val->i);
	else if (token->value[val->i] == '$' && token->expand != 1
		&& should_process(token->value[val->i + 1]))
		res = process_var(val, token->value, shell);
	else
	{
		val->real_value[val->j++] = token->value[val->i++];
		val->real_value[val->j] = '\0';
		res = val->real_value;
	}
	return (res);
}
