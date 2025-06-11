/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumiguel <lumiguel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:52:37 by lumiguel          #+#    #+#             */
/*   Updated: 2025/05/28 09:34:56 by lumiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	export_sorter(t_env *env)
{
	int		swapped;
	t_env	*ptr;
	t_env	*lptr;

	swapped = 0;
	lptr = NULL;
	if (!env || !env->next)
		return ;
	while (!swapped)
	{
		ptr = env;
		while (ptr && ptr->next && ptr->next != lptr)
		{
			if (ptr->key && ptr->next->key && (
					ft_strcmp(ptr->key, ptr->next->key)) > 0)
				swapped = exp_sorter(ptr);
			ptr = ptr->next;
		}
		lptr = ptr;
	}
}

int	exp_sorter(t_env *ptr)
{
	char	*tmp_key;
	char	*tmp_value;

	tmp_key = ptr->key;
	tmp_value = ptr->value;
	ptr->key = ptr->next->key;
	ptr->value = ptr->next->value;
	ptr->next->key = tmp_key;
	ptr->next->value = tmp_value;
	return (1);
}

t_env	*ft_envlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	print_export(t_env *env)
{
	while (env)
	{
		if (env->key)
		{
			printf("%s", env->key);
			if (env->value)
				printf("=\"%s\"", env->value);
			printf("\n");
		}
		env = env->next;
	}
}
