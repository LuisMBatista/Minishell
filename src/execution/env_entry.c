/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_entry.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumiguel <lumiguel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:03:37 by lumiguel          #+#    #+#             */
/*   Updated: 2025/06/05 13:07:08 by lumiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*key_value_join(char *key, char *value)
{
	size_t	key_size;
	size_t	value_size;
	char	*key_value;

	key_size = ft_strlen(key);
	value_size = ft_strlen(value);
	key_value = (char *)malloc((key_size + value_size + 2) * sizeof(char));
	if (!key_value)
	{
		errno = ENOMEM;
		return (NULL);
	}
	ft_memcpy(key_value, key, key_size);
	key_value[key_size] = '=';
	ft_memcpy(key_value + key_size + 1, value, value_size);
	key_value[key_size + 1 + value_size] = '\0';
	return (key_value);
}

int	add_env_entry(char **final_env, size_t *i, t_env *entry)
{
	final_env[*i] = key_value_join(entry->key, entry->value);
	if (!final_env[*i])
		return (FATAL_ERR);
	(*i)++;
	return (SUCCESS);
}

// passa o src para o final_env
int	fill_env(char **final_env, t_env *src, t_env *other, size_t *i)
{
	while (src)
	{
		if (!find_env_key(other, src->key))
		{
			if (add_env_entry(final_env, i, src) != SUCCESS)
				return (FATAL_ERR);
		}
		src = src->next;
	}
	return (SUCCESS);
}

//se houver erro a dar fill, da free ao env
void	free_partial_env(char **env, size_t size)
{
	size_t	j;

	j = 0;
	while (j < size)
		free(env[j++]);
	free(env);
}

// Função principal
char	**create_exec_env(t_env *env, t_env *l_env)
{
	size_t	i_env;
	size_t	c_env_size;
	char	**final_env;

	i_env = env_list_size(env);
	c_env_size = env_list_size(l_env);
	final_env = malloc((i_env + c_env_size + 1) * sizeof(char *));
	if (!final_env)
		return (NULL);
	i_env = 0;
	if ((l_env && fill_env(final_env, l_env, l_env->next, &i_env) == FATAL_ERR)
		|| fill_env(final_env, env, l_env, &i_env) == FATAL_ERR)
	{
		free_partial_env(final_env, i_env);
		return (NULL);
	}
	final_env[i_env] = NULL;
	return (final_env);
}
