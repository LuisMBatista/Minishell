/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: treis-ro <treis-ro@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:47:07 by treis-ro          #+#    #+#             */
/*   Updated: 2025/06/10 00:56:47 by treis-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_shell(t_env *env, char *value)
{
	free(env->value);
	env->value = ft_strdup(value);
	if (!env->value)
		return (FATAL_ERR);
	return (SUCCESS);
}

int	else_env(t_env *env, char *key, char *value, t_shell *shell)
{
	t_env	*i_node;

	env = malloc(sizeof(t_env));
	if (!env)
		return (FATAL_ERR);
	env->key = ft_strdup(key);
	if (!env->key)
		return (free(env), FATAL_ERR);
	env->value = ft_strdup(value);
	if (!env->value)
		return (free(env->key), free(env), FATAL_ERR);
	env->next = NULL;
	if (!shell->shell_vars)
		shell->shell_vars = env;
	else
	{
		i_node = shell->shell_vars;
		while (i_node->next)
			i_node = i_node->next;
		i_node->next = env;
	}
	return (SUCCESS);
}

int	shell_var(t_shell *shell, char *key, char *value)
{
	t_env	*env;

	env = find_env_key(shell->env, key);
	if (env)
		return (check_shell(env, value));
	env = find_env_key(shell->shell_vars, key);
	if (env)
		return (check_shell(env, value));
	else
		if (else_env(env, key, value, shell))
			return (FATAL_ERR);
	return (SUCCESS);
}

int	add_shell_vars(t_shell *shell, t_env *cmd_vars)
{
	t_env	*cur;

	cur = cmd_vars;
	while (cur)
	{
		if (shell_var(shell, cur->key, cur->value) != SUCCESS)
			return (FATAL_ERR);
		cur = cur->next;
	}
	return (SUCCESS);
}

char	*expand_var(char *token, int *index, t_shell *shell)
{
	char	var_name[256];
	int		i;

	i = 0;
	ft_bzero(var_name, 256);
	(*index)++;
	if (token[*index] == '?')
		return ((*index)++, ft_itoa(g_exit_signal));
	while (token[*index]
		&& (ft_isalnum(token[*index]) || token[*index] == '_'))
	{
		var_name[i++] = token[*index];
		(*index)++;
		if (i >= 255)
			break ;
	}
	var_name[i] = '\0';
	return (search_var(shell, var_name));
}
