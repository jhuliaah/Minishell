/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:41:53 by jhualves          #+#    #+#             */
/*   Updated: 2025/04/17 17:49:44 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "../Libft42/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>

/*
# Creating a enum struct with all the types of tokens;
#
*/

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	TOKEN_QUOTE,
	TOKEN_DQUOTE,
	TOKEN_VARIABLE,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

t_token	*new_token(t_token_type type, char *word);
t_token	*tokenizer_input(char *input);
t_token	*word_token(char *input, int *i);
// t_token	*word_token(char *input, t_token *curr);
int		is_special_char(char c);
// t_token	*special_token(char *input, t_token *curr);
t_token	*special_token(char *input, int *i);
// char	*variable_token(char *input, t_token **curr);
// char	*variable_token_utils(char *input, t_token **curr, int count, int rest);
// char	*variable_token_utils_1(char *input, t_token **curr);
void	free_tokens(t_token *tok);

#endif



// Token Type	Valor na string de entrada	Descrição
// TOKEN_PIPE	`	`
// TOKEN_REDIR_IN	<	Redirecionamento de entrada
// TOKEN_REDIR_OUT	>	Redirecionamento de saída
// TOKEN_REDIR_APPEND	>>	Redirecionamento de saída (append)
// TOKEN_HEREDOC	<<	Heredoc (leitura até delimitador)
// TOKEN_QUOTE	'	Aspas simples (delimitador de string)
// TOKEN_DQUOTE	"	Aspas duplas (delimitador de string)
// TOKEN_VARIABLE	$VAR, $?, etc.	Variável de ambiente ou especial