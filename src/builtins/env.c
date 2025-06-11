/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumiguel <lumiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:38:35 by lumiguel          #+#    #+#             */
/*   Updated: 2025/06/10 12:00:54 by lumiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_env_cmd(t_env *env, t_cmd *cmd)
{
	char	**exec_env;
	int		i;

	if (cmd->cmd[1])
		return (SYNTAX_ERR);
	exec_env = create_exec_env(env, cmd->env);
	if (!exec_env)
		return (FATAL_ERR);
	i = 0;
	while (exec_env[i])
	{
		ft_putstr_fd(exec_env[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
	free_char_array(exec_env);
	return (SUCCESS);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void	unset_env(int i, char **keys, t_env *env)
{
	t_env	*curr;
	t_env	*prev;

	while (keys[i])
	{
		curr = env;
		prev = NULL;
		while (curr)
		{
			if (ft_strcmp(curr->key, keys[i]) == 0)
			{
				if (prev)
					prev->next = curr->next;
				else
					env = curr->next;
				free(curr->key);
				free(curr->value);
				free(curr);
				break ;
			}
			prev = curr;
			curr = curr->next;
		}
		i++;
	}
}

int	force_env(t_env **env, t_env **curr)
{
	char	*temp;
	char	buff[BUFFER_SIZE];

	temp = ft_strjoin("PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:",
			"/usr/local/sbin:/snap/bin:");
	if (add_env_node(temp, env, curr) == FATAL_ERR)
		return (FATAL_ERR);
	free(temp);
	temp = ft_strjoin("PWD=", getcwd(buff, 1024));
	if (!temp)
		return (FATAL_ERR);
	if (add_env_node(temp, env, curr) == FATAL_ERR)
		return (FATAL_ERR);
	free(temp);
	if (add_env_node("SHLVL=1", env, curr) == FATAL_ERR)
		return (FATAL_ERR);
	return (SUCCESS);
}

int	slash_check(char *path)
{
	int	i;

	i = 0;
	while (path[i])
		i++;
	if (path[--i] == '/')
		return (1);
	return (0);
}
