/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:41:53 by jhualves          #+#    #+#             */
/*   Updated: 2025/05/07 20:21:33 by jhualves         ###   ########.fr       */
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

/******************************
 *          TOKENS            *
 ******************************/

typedef enum e_token_type
{
	TOKEN_WORD, //Comando ou argumento (ex: "ls", "-l")
	TOKEN_PIPE, // |
	TOKEN_REDIR_IN, // <
	TOKEN_REDIR_OUT, // >
	TOKEN_REDIR_APPEND, // >>
	TOKEN_HEREDOC, // <<
	TOKEN_QUOTE, // ''
	TOKEN_DQUOTE, // ""
	TOKEN_VARIABLE, // Variáveis (ex. $$ $HOME)
	TOKEN_EOF, //fim da entrada;
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

/******************************
 *         ENVIRONMENT        *
 ******************************/
// Nome da variável (ex: "PATH")
// Valor da variável (ex: "/usr/bin")
// Próximo nó (lista encadeada)
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

/******************************
 *         COMMANDS           *
 ******************************/

typedef struct s_redir
{
	char			*file; //nome do arquivo (ex: "output.txt")
	t_token_type	type; //tipo de redirecionamento ( >, >>, <, <<)
	struct s_redir	*next; // próximo redirecionamento
}	t_redir;

typedef struct s_cmd
{
	char			**args; // Argumentos do comando (ex: {"ls", "-l", NULL})
	t_redir			*redirs; // Lista de redirecionamentos
	struct s_cmd	*next; // Próximo comando (para pipelines)
	struct s_cmd	*prev; // comando anterior (caso necessário)
}	t_cmd;

 /******************************
 *        MEMORY MANAGEMENT    *
 ******************************/
typedef struct s_allocation
{
	void				*ptr; // ponteiro alocado
	struct s_allocation	*next;
}	t_allocation;

 /******************************
 *         CONTEXT            *
 ******************************/
typedef struct s_context
{
	t_env			*env; //variáveis de ambiente
	t_allocation	*allocations; // Lista de alocações de memória
	int				exit_status; // Status de de saída do último comando
	pid_t			*child_pids; // Lista de PIDs de processos filhos (opcional)
	int				child_count; // Número de processos filhos
}	t_context;


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
