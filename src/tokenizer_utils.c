/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 22:52:37 by jhualves          #+#    #+#             */
/*   Updated: 2025/04/16 20:38:15 by jhualves         ###   ########.fr       */
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
char	*variable_token_utils(char *input, t_token **curr, int count, int rest)
{
	int	i;

	i = count * 2 + rest;
	while (count >= 1)
	{
		*curr = new_token(TOKEN_VARIABLE, "$$");
		curr = &(*curr)->next;
		count--;
	}
	while (rest > 0)
	{
		*curr = new_token(TOKEN_VARIABLE, "$");
		curr = &(*curr)->next;
		rest--;
	}
	input = input + i;
	return (input);
}

char	*variable_token_utils_1(char *input, t_token **curr)
{
	size_t	i;
	char	*word;

	word = NULL;
	i = 0;
	if (*input == '$')
		input++;
	while (input[i] != ' ')
		i++;
	word = ft_strndup(input, i);
	*curr = new_token(TOKEN_VARIABLE, word);
	curr = &(*curr)->next;
	input = input + i;
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
