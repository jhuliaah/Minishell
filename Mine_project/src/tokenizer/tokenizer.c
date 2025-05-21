/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:41:46 by jhualves          #+#    #+#             */
/*   Updated: 2025/05/21 14:42:25 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*tokenizer_input(char *input)
{
	t_context	*ctx;
	t_token		*head;
	t_token		*curr;
	t_token		*new_node;
	int			i;

	ctx = get_context();
	head = NULL;
	curr = NULL;
	i = 0;
	if (!input || !ctx)
		return (NULL);
	while (input[i])
	{
		new_node = process_next_token(input, &i);
		if (!new_node)
			return (free_tokens(ctx, head), NULL);
		if (!head)
			head = new_node;
		else
			curr->next = new_node;
		curr = new_node;
	}
	add_eof_token(ctx, &head);
	return (head);
}

t_token	*process_next_token(char *input, int *i)
{
	t_context	*ctx;
	t_token		*new_node;

	ctx = get_context();
	new_node = NULL;
	if (input[*i] == '\'')
		new_node = quote_token(input, i);
	else if (input[*i] == '\"')
		new_node = dquote_token(input, i);
	else if (is_special_char(input[*i]))
		new_node = special_token(input, i);
	else
		new_node = word_token(input, i);
	if (!new_node)
		return (NULL);
	return (new_node);
}

t_token	*word_token(char *input, int *i)
{
	t_context	*ctx;
	int			start;
	char		*word;

	ctx = get_context();
	start = *i;
	while (input[*i] && !ft_isspace(input[*i]) && !is_special_char(input[*i]))
		(*i)++;
	word = safe_strndup(ctx, input + start, *i - start);
	return (new_token(TOKEN_WORD, word));
}

t_token	*special_token(char *input, int *i)
{
	t_token	*new_node;

	new_node = NULL;
	if (input[*i] == '$')
		return (variable_token(input, i));
	handle_operator(input, i, &new_node);
	return (new_node);
}
