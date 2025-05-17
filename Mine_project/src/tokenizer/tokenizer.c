/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:41:46 by jhualves          #+#    #+#             */
/*   Updated: 2025/05/17 19:14:38 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
# This function creates a linked-list with all types of tokens and it's value
# so we can do the proper verification and parsing.
*/

// t_token	*new_token(t_token_type type, char *word)
// {
// 	t_token	*new_token;

// 	new_token = malloc(sizeof (t_token));
// 	if (!new_token)
// 		return (NULL);
// 	new_token->type = type;
// 	new_token->value = word;
// 	new_token->next = NULL;
// 	return (new_token);
// }

static t_token	*process_next_token(char *input, int *i)
{
    if (input[*i] == '\'')
        return (quote_token(input, i));
    else if (input[*i] == '\"')
        return (dquote_token(input, i));
    else if (is_special_char(input[*i]))
        return (special_token(input, i));
    else
        return (word_token(input, i));
}

t_token	*tokenizer_input(char *input)
{
    t_context *ctx = get_context();
    t_token *head = NULL;
    t_token *curr = NULL;
    int i = 0;

    while (input[i])
    {
        t_token *new_node = process_next_token(input, &i);
        if (!new_node)
            return (free_tokens(ctx, head)); // Libera tokens em caso de erro
        
        if (!head)
            head = new_node;
        else
            curr->next = new_node;
        curr = new_node;
    }
    return (head);
}

/*
# The function word_token takes every part of the input that is a word.
# This function takes the input and the pointer for int i, que é o indice que 
# esta percorrendo o input na função principal e cria um novo token.
# Por fim limpando a variavel word e retornando o novo token criado.
*/
t_token	*word_token(char *input, int *i)
{
    t_context *ctx = get_context();
    int start = *i;
    char *word;

    while (input[*i] && !ft_isspace(input[*i]) && !is_special_char(input[*i]))
        (*i)++;
    
    word = safe_strndup(ctx, input + start, *i - start);
    return (new_token(TOKEN_WORD, word));
}

t_token	*special_token(char *input, int *i)
{
    t_token *new_node = NULL;

    if (input[*i] == '$')
        return (variable_token(input, i));
    
    handle_operator(input, i, &new_node);
    return (new_node);
}


// t_token	*special_token(char *input, int *i)
// {
// 	t_token	*new_node;
// 	int		j;

// 	j = *i;
// 	new_node = NULL;
// 	if (input[j] == '|' && input[j + 1] != '|')
// 		new_node = new_token(TOKEN_PIPE, ft_strdup("|"));
// 	else if (input[j] == '>' && input[j + 1] == '>')
// 		new_node = new_token(TOKEN_REDIR_APPEND, ">>");
// 	else if (input[j] == '<' && input[j + 1] == '<')
// 		new_node = new_token(TOKEN_HEREDOC, "<<");
// 	else if (input[j] == '>' && input[j + 1] != '>')
// 		new_node = new_token(TOKEN_REDIR_OUT, ">");
// 	else if (input[j] == '<' && input[j + 1] != '<')
// 		new_node = new_token(TOKEN_REDIR_IN, "<");
// 	else if (input[j] == '$')
// 		return (variable_token(input, i));
// 	if (!new_node)
// 		return (NULL);
// 	if ((input[j] == '|' && input[j + 1] != '|')
// 		|| (input[j] == '>' && input[j + 1] != '>')
// 		|| (input[j] == '<' && input[j + 1] != '<'))
// 		j++;
// 	else
// 		j += 2;
// 	*i = j;
// 	return (new_node);
// }


t_token	*handle_dollar_groups(int count, int rest, int *i)
{
    t_context *ctx = get_context();
    t_token *result = NULL;
    int j = 0;

    while (j++ < count)
        add_token(ctx, &result, "$$", TOKEN_VARIABLE);
    
    if (rest)
        add_token(ctx, &result, "$", TOKEN_VARIABLE);
    
    *i += (count * 2) + rest;
    return (result);
}

t_token	*variable_token(char *input, int *i)
{
    int count = count_consecutive_chars(input + *i, '$');
    int rest = count % 2;

    return (handle_dollar_groups(count / 2, rest, i));
}

// t_token	*variable_token(char *input, int *i)
// {
// 	int		j;
// 	int		rest;
// 	int		count;
// 	t_token	*result;

// 	j = *i;
// 	count = 0;
// 	while (input[j] == '$')
// 	{
// 		count++;
// 		j++;
// 	}

// 	rest = count % 2;

// 	if (count > 1)
// 	{
// 		count /= 2;
// 		result = variable_token_utils(i, count, rest);
// 	}
// 	else
// 		result = variable_token_utils_1(&input[*i], i);

// 	return (result);
// }

void	handle_operator(char *input, int *i, t_token **new_node)
{
	t_token_type	type;
	char			operator_str[2];

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
		operator_str[2] = {input[*i], '\0'}; //ARRUMAR ISSO AQUI
		*new_node = new_token(type, operator_str);
		(*i)++;
	}
}

