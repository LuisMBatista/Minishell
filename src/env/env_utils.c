/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: treis-ro <treis-ro@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 23:40:15 by lumiguel          #+#    #+#             */
/*   Updated: 2025/06/10 01:03:38 by treis-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*lvlupdate(t_env *env)
{
	int		lvl;
	char	*new_value;

	lvl = ft_atoi(env->value);
	lvl += 1;
	new_value = ft_itoa(lvl);
	if (!new_value)
		return (NULL);
	free(env->value);
	return (new_value);
}

int	env_list_size(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

t_env	*find_env(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

char	*search_var(t_shell *shell, char *var_name)
{
	t_env	*env_var;
	t_env	*superior_env;

	env_var = find_env(shell->shell_vars, var_name);
	superior_env = find_env(shell->env, var_name);
	if (superior_env && superior_env->value)
		return (ft_strdup(superior_env->value));
	else if (env_var && env_var->value)
	{
		return (ft_strdup(env_var->value));
	}
	else
		return (ft_strdup(""));
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		free(env);
		env = tmp;
	}
}
