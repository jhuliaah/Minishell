/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:01:13 by jhualves          #+#    #+#             */
/*   Updated: 2025/05/20 16:13:36 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_token(t_context *ctx, t_token **list, \
	char *value, t_token_type type)
{
	t_token	*new_node;
	t_token	*curr;

	new_node = new_token(type, value);
	curr = *list;
	if (!curr)
		*list = new_node;
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = new_node;
	}
}

void	add_eof_token(t_context *ctx, t_token **head)
{
	t_token	*eof_token;
	t_token	*curr;

	eof_token = safe_malloc(ctx, sizeof(t_token));
	eof_token->type = TOKEN_EOF;
	eof_token->value = NULL;
	eof_token->next = NULL;
	if (!*head)
		*head = eof_token;
	else
	{
		curr = *head;
		while (curr->next)
			curr = curr->next;
		curr->next = eof_token;
	}
}

int	count_consecutive_chars(char *str, char c)
{
	int	count;

	count = 0;
	while (str[count] == c)
		count++;
	return (count);
}

void	handle_operator(char *input, int *i, t_token **new_node)
{
	t_token_type	type;

	type = NULL;
	if (input[*i] == '>' && input[*i + 1] == '>')
	{
		*new_node = new_token(TOKEN_REDIR_APPEND, ">>");
		(*i) += 2;
	}
	else if (input[*i] == '<' && input[*i + 1] == '<')
	{
		*new_node = new_token(TOKEN_HEREDOC, "<<");
		(*i) += 2;
	}
	else
	{
		if (input[*i] == '>')
			type = TOKEN_REDIR_OUT;
		else if (input[*i] == '<')
			type = TOKEN_REDIR_IN;
		else
			type = TOKEN_PIPE;
		*new_node = new_token(type, "|");
		(*i)++;
	}
}
