/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: treis-ro <treis-ro@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:12:13 by treis-ro          #+#    #+#             */
/*   Updated: 2025/06/05 16:54:25 by treis-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*find_home_env(t_shell *shell)
{
	t_env	*env_var;
	char	*dup;

	env_var = find_env(shell->env, "HOME");
	if (env_var && env_var->value)
	{
		dup = ft_strdup(env_var->value);
		return (dup);
	}
	return (NULL);
}

void	add_env_to_command(t_cmd *cmd, t_env *new_env)
{
	t_env	*tmp;

	if (!cmd->env)
		cmd->env = new_env;
	else
	{
		tmp = cmd->env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_env;
	}
}

int	chars_to_struc(t_cmd *cmd, char *expand, char *key)
{
	t_env	*new_env;

	new_env = malloc(sizeof(*new_env));
	if (!new_env)
		return (free(key), free(expand), FATAL_ERR);
	new_env->key = key;
	new_env->value = expand;
	new_env->next = NULL;
	add_env_to_command(cmd, new_env);
	return (SUCCESS);
}

int	add_to_command_env(t_cmd *cmd, t_token *token, t_shell *shell)
{
	char	*equal;
	char	*key;
	char	*expand;
	char	*tmp_str;

	equal = ft_strchr(token->value, '=');
	if (!equal)
		return (SYNTAX_ERR);
	key = ft_substr(token->value, 0, equal - token->value);
	if (!key)
		return (FATAL_ERR);
	tmp_str = ft_strdup(equal + 1);
	if (!tmp_str)
		return (free(key), FATAL_ERR);
	free(token->value);
	token->value = tmp_str;
	expand = find_real_value(token, shell);
	if (!expand)
		return (free(key), FATAL_ERR);
	if (chars_to_struc(cmd, expand, key))
		return (FATAL_ERR);
	return (SUCCESS);
}

char	*resize_buffer(char *real_value, int *buffer_size)
{
	char	*new_res;

	*buffer_size *= 2;
	new_res = realloc_value(real_value, *buffer_size / 2, *buffer_size);
	if (!new_res)
	{
		free(real_value);
		return (NULL);
	}
	return (new_res);
}
