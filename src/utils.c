/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumiguel <lumiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:27:05 by treis-ro          #+#    #+#             */
/*   Updated: 2025/06/10 12:00:36 by lumiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*new_env_node(char *env_var)
{
	t_env	*node;
	char	*equal_sign;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	equal_sign = strchr(env_var, '=');
	if (!equal_sign)
	{
		free(node);
		return (NULL);
	}
	node->key = strndup(env_var, equal_sign - env_var);
	node->value = strdup(equal_sign + 1);
	node->next = NULL;
	return (node);
}

t_env	*ft_tmp_maker(t_env *tmp, char *envp, char *sep, t_env *env)
{
	tmp->key = ft_substr(envp, 0, sep - envp);
	tmp->value = ft_substr(sep + 1, 0, ft_strlen(sep + 1));
	if (!tmp->key || !tmp->value)
	{
		if (tmp->key)
			free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		return (free_env(env), free(tmp), NULL);
	}
	if (!ft_strcmp(tmp->key, "SHLVL"))
		tmp->value = lvlupdate(tmp);
	return (env);
}

int	add_env_node(char *envp, t_env **env, t_env **current)
{
	t_env	*tmp;
	char	*sep;

	tmp = malloc(sizeof(t_env));
	if (!tmp)
		return (FATAL_ERR);
	tmp->next = NULL;
	sep = ft_strchr(envp, '=');
	if (!sep)
		return (free(tmp), 0);
	ft_tmp_maker(tmp, envp, sep, *env);
	if (!*env)
		*env = tmp;
	else
		(*current)->next = tmp;
	*current = tmp;
	return (SUCCESS);
}

t_env	*env_init(char **envp)
{
	t_env	*env;
	t_env	*current;
	int		i;

	env = NULL;
	current = NULL;
	i = 0;
	if (!envp || !envp[0])
	{
		if (force_env(&env, &current) == FATAL_ERR)
			return (free_env(env), NULL);
	}
	while (envp[i])
	{
		if (add_env_node(envp[i], &env, &current))
			return (free_env(env), NULL);
		i++;
	}
	return (env);
}

t_shell	shell_init(t_shell *shell, char **envp)
{
	t_env	*env;

	env = env_init(envp);
	shell->env = env;
	shell->pids = NULL;
	shell->n_pids = 0;
	shell->shell_vars = NULL;
	shell->tokens = NULL;
	shell->commands = NULL;
	shell->last_input = NULL;
	shell->stdin_backup = dup(STDIN_FILENO);
	shell->stdout_backup = dup(STDOUT_FILENO);
	g_exit_signal = 0;
	return (*shell);
}
