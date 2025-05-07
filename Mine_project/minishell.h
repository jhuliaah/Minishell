/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:01:02 by jhualves          #+#    #+#             */
/*   Updated: 2025/05/07 20:31:26 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft42/libft.h"
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


#endif