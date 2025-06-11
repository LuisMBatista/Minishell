/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumiguel <lumiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:28:57 by treis-ro          #+#    #+#             */
/*   Updated: 2025/06/09 13:58:59 by lumiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	tokenize_input(t_shell *shell, char *input)
{
	char	**token_split;
	t_token	*current;
	int		i;

	shell->tokens = NULL;
	token_split = split_input(input);
	if (!token_split)
		return (print_error("Parsing error\n", 1));
	current = NULL;
	i = 0;
	while (token_split[i] != NULL)
	{
		if (create_token_node(shell, &current, token_split[i]) == -1)
		{
			free_char_array(token_split);
			return (print_error("Mem alloc error\n", 1));
		}
		i++;
	}
	free_char_array(token_split);
	return (SUCCESS);
}

int	valid_tokens(t_shell *shell)
{
	t_token	*current;

	if (!shell->tokens)
		return (SUCCESS);
	current = shell->tokens;
	if (current->type == TOKEN_PIPE)
		return (print_error("Syntax error near token '|'\n", 2));
	while (current)
	{
		if (current->type == TOKEN_PIPE)
		{
			if (!current->next || current->next->type == TOKEN_PIPE
				|| current->prev->type == TOKEN_REDIRECT)
				return (print_error("Syntax error near token |\n", 2));
		}
		else if (current->type == TOKEN_REDIRECT)
		{
			if (!current->next)
				return (print_error("Syntax error near token newline\n", 2));
			if (current->next->type == TOKEN_REDIRECT)
				return (print_error("Syntax error near redirection\n", 2));
		}
		current = current->next;
	}
	return (SUCCESS);
}

void	correct_env(t_shell *shell)
{
	t_token	*current;
	int		in_command;

	current = shell->tokens;
	in_command = 0;
	while (current)
	{
		if (current->type == TOKEN_PIPE)
			in_command = 0;
		else if (current->type == TOKEN_CMD)
			in_command = 1;
		else if (current->type == TOKEN_ENV && in_command)
			current->type = TOKEN_CMD;
		current = current->next;
	}
}

int	parse_main(t_shell *shell)
{
	char	*input;
	int		status;

	input = readline("minishell> ");
	if (!input)
		return (ft_putstr_fd("exit\n", STDOUT_FILENO), EOF_CODE);
	status = check_valid_input(shell, input);
	if (status != SUCCESS)
		return (status);
	status = tokenize_input(shell, input);
	free(input);
	if (status != SUCCESS)
		return (status);
	if (!shell->tokens)
		return (SUCCESS);
	correct_env(shell);
	status = valid_tokens(shell);
	if (status != SUCCESS)
		return (status);
	status = parse_tokens_into_commands(shell, SUCCESS, shell->tokens);
	return (status);
}
