/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 22:52:37 by jhualves          #+#    #+#             */
/*   Updated: 2025/04/17 22:16:08 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '$');
}

/*
# The expected behaviour for de values "$$" in bash is to get 
# the pid of the current process; and when the value "$" is to create a variable
*/
t_token	*variable_token_utils(char *input, int *i, int count, int rest)
{
	int		i;
	t_token	*new_node;
	t_token	*temp;

	new_node = NULL;
	temp = new_node;
	i = count * 2 + rest;
	while (count >= 1)
	{
		new_node = new_token(TOKEN_VARIABLE, "$$");
		new_node = new_node->next;
		count--;
	}
	while (rest > 0)
	{
		new_node = new_token(TOKEN_VARIABLE, "$");
		new_node = new_node->next;
		rest--;
	}
	input = input + i;
	return (input);
}

char	*variable_token_utils_1(char *input, int *i)
{
	size_t	i;
	char	*word;
	t_token	*new_node;

	new_node = NULL;
	word = NULL;
	i = 0;
	if (*input == '$')
		input++;
	while (input[i] != ' ')
		i++;
	word = ft_strndup(input, i);
	new_node = new_token(TOKEN_VARIABLE, word);
	input = input + i;
	if (curr == NULL)
		curr = &new_node;
	else
	{
		(*curr)->next = new_node;
		curr = &(*curr)->next;
	}
	return (input);
}

void	free_tokens(t_token *tok)
{
	t_token	*tmp;

	while (tok)
	{
		tmp = tok;
		tok = tok->next;
		free(tmp->value);
		free(tmp);
	}
}
