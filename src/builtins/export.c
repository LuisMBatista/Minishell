/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumiguel <lumiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:38:48 by lumiguel          #+#    #+#             */
/*   Updated: 2025/06/09 15:03:26 by lumiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_export(char **cmd, t_env *env)
{
	int	i;
	int	ret;

	ret = 0;
	i = 1;
	if (cmd[1] == NULL)
		return (export_sorter(env), print_export(env), SUCCESS);
	while (cmd[i])
	{
		if (!is_valid_identifier(cmd[i]))
		{
			ft_putstr_fd("export: '", STDERR_FILENO);
			ft_putstr_fd(cmd[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			ret = 1;
			i++;
			continue ;
		}
		if (!new_variable_env(cmd[i], env))
			return (FATAL_ERR);
		i++;
	}
	return (ret);
}

int	is_valid_identifier(const char *str)
{
	int	i;

	i = 1;
	if (!str || !(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

t_env	*find_env_key(t_env *env, const char *key)
{
	if (!env || !key)
		return (NULL);
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	new_variable(t_env *env, char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		perror("malloc");
		return ;
	}
	new->key = ft_strdup(key);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = ft_strdup("");
	new->next = NULL;
	ft_envlast(env)->next = new;
}

int	new_variable_env(char *cmd, t_env *env)
{
	char	**new_entry;
	char	*key;
	char	*value;
	t_env	*existing;

	new_entry = ft_split(cmd, '=');
	key = new_entry[0];
	value = new_entry[1];
	existing = find_env_key(env, key);
	if (existing)
	{
		if (value)
		{
			free(existing->value);
			existing->value = ft_strdup(value);
		}
	}
	else
	{
		new_variable(env, key, value);
		free_char_array(new_entry);
		return (FATAL_ERR);
	}
	return (free_char_array(new_entry), SUCCESS);
}
