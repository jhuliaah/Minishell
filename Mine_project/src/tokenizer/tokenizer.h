/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:41:53 by jhualves          #+#    #+#             */
/*   Updated: 2025/04/29 20:06:42 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "../../minishell.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>

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

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

int		is_special_char(char c);
void	free_tokens(t_token *tok);
t_token	*tokenizer_input(char *input);
t_token	*word_token(char *input, int *i);
t_token	*special_token(char *input, int *i);
t_token	*new_token(t_token_type type, char *word);
t_token *quote_token(char *input, int *i);
t_token *dquote_token(char *input, int *i);
t_token	*variable_token(char *input, int *i);
t_token	*variable_token_utils_1(char *input, int *i);
// void	link_node(t_token **head, t_token **curr, t_token **new_node);
t_token	*variable_token_utils(int *i, int count, int rest);

t_env	*init_env(char **envp);

#endif
