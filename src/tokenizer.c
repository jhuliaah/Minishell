/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:41:46 by jhualves          #+#    #+#             */
/*   Updated: 2025/04/16 21:32:48 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

/*
# TODO 
# - FAZER AS ASPAS E DUPLAS ASPAS
# - VERIFICAR SE A LISTA ESTA ATUALIZANDO CORRETAMENTE
# - FAZER OS TESTES
*/

/*
# This function creates a linked-list with all types of tokens and it's value
# so we can do the proper verification and parsing.
*/

t_token	*new_token(t_token_type type, char *word)
{
	t_token	*new_token;

	new_token = malloc(sizeof (t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->value = word;
	new_token->next = NULL;
	return (new_token);
}

t_token	*tokenizer_input(char *input)
{
	t_token	*head;
	t_token	**curr;
	t_token	*temp;

	head = NULL;
	curr = &head;
	while (*input)
	{
		if (is_special_char(*input))
		{
			input = special_token(input, curr);
			if (!*curr) // Verifica se o token foi criado corretamente
				return (NULL);
			printf("Token type: %d, value: %s\n", (*curr)->type, (*curr)->value);
			fflush(stdout);
		}
		else if (*input == ' ')
			input++;
		else
		{
			input = word_token(input, curr);
			if (!*curr) // Verifica se o token foi criado corretamente
				return (NULL);
			printf("Token type: %d, value: %s\n", (*curr)->type, (*curr)->value);
			fflush(stdout);
		}	
	}
// 	testes
	temp = head;
	while (temp)
	{
		printf("Token type: %d, value: %s\n", temp->type, temp->value);
		fflush(stdout);
		temp = temp->next;
	}

	return (head);
}

char	*word_token(char *input, t_token **curr)
{
	int		i;
	char	*word;

	i = 0;
	while (input[i] && input[i] != ' ' && !is_special_char(input[i]))
		i++;
	word = ft_strndup(input, i);
	*curr = new_token(TOKEN_WORD, word);
	if (!*curr)
	{
		free(word);
		return (NULL);
	}
	curr = &(*curr)->next;
	input += i;
	return (input);
}

char	*special_token(char *input, t_token **curr)
{
	if (input[0] == '|' && input[1] != '|')
		*curr = new_token(TOKEN_PIPE, ft_strdup("|"));
	else if (input[0] == '>' && input[1] == '>')
		*curr = new_token(TOKEN_REDIR_APPEND, ">>");
	else if (input[0] == '<' && input[1] == '<')
		*curr = new_token(TOKEN_HEREDOC, "<<");
	else if (input[0] == '>' && input[1] != '>')
		*curr = new_token(TOKEN_REDIR_OUT, ">");
	else if (input[0] == '<' && input[1] != '<')
		*curr = new_token(TOKEN_REDIR_IN, "<");
	else if (input[0] == '$')
		return (variable_token(input, curr));
	if (!*curr)
		return (NULL);
	if ((input[0] == '|' && input[1] != '|')
		|| (input[0] == '>' && input[1] != '>')
		|| (input[0] == '<' && input[1] != '<'))
		input++;
	else
		input += 2;
	curr = &(*curr)->next;
	return (input);
}

char	*variable_token(char *input, t_token **curr)
{
	int	i;
	int	count;
	int	rest;

	count = 0;
	i = 0;
	while (input[count] == '$')
		count++;
	rest = count % 2;
	if (count > 1)
	{
		count /= 2;
		input = variable_token_utils(input, curr, count, rest);
	}
	else
		input = variable_token_utils_1(input, curr);
	if(!*curr)
		return (NULL);
	return (input);
}
