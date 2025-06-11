/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: treis-ro <treis-ro@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 01:51:44 by treis-ro          #+#    #+#             */
/*   Updated: 2025/06/06 03:54:06 by treis-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_quotes(char *s)
{
	int	q;
	int	i;

	i = 0;
	q = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			q++;
		i++;
	}
	return (q);
}

char	*remove_quotes(t_token *token, int *quote)
{
	int		i;
	int		j;
	int		size;
	char	*del;

	i = 0;
	size = ft_strlen(token->value);
	*quote = count_quotes(token->value);
	del = (char *)malloc((size - *quote + 1) * sizeof(char));
	if (!del)
		return (NULL);
	i = 0;
	j = 0;
	while (token->value[i])
	{
		if (!(token->value[i] == '\'' || token->value[i] == '\"'))
			del[j++] = token->value[i];
		i++;
	}
	del[j] = '\0';
	return (del);
}
