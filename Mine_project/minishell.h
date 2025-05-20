/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:01:02 by jhualves          #+#    #+#             */
/*   Updated: 2025/05/20 16:52:24 by jhualves         ###   ########.fr       */
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
# include <signal.h>
# include <fcntl.h>
# include <stdbool.h>

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

typedef struct s_redir {
    t_token_type      type;
    char              *file;
    struct s_redir    *next;
} t_redir;

typedef struct s_cmd {
    char            **args;     // Argumentos (ex: ["ls", "-l", NULL])
    t_redir          *redirs;    // Redirecionamentos
    struct s_cmd     *next;      // Próximo comando (para pipes)
} t_cmd;

/******************************
 *         ENVIRONMENT        *
 ******************************/

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
	bool			no_newline; // Flag para -n (novo campo!)
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
	t_env			*env;          // Variáveis de ambiente
	t_allocation	*allocations;  // Alocações rastreadas
	bool			is_interactive;// Modo de execução
	int				exit_status;   // Último status de saída (0-255)
	bool			fatal_error;   // Erro crítico detectado
	pid_t			last_child_pid;// PID do último processo executado
}	t_context;

 /******************************
 *         FUNCTIONS           *
 ******************************/

/* Main.c */

t_context	**get_ctx_handle(void);
void		set_context(t_context *new_ctx);
t_context	*get_context(void);
void		main_loop(t_context *ctx);
int			main(int argc, char **argv, char **envp);

/*env.c*/
void		free_env_list(t_env *env_list);
int			load_environment(t_context *ctx, char **envp);

/*memory.c*/
void		*safe_malloc(t_context *ctx, size_t size);
void		add_allocation(t_context *ctx, void *ptr);
void		remove_allocation(t_context *ctx, void *ptr);
void		safe_free(t_context *ctx, void *ptr);
void		free_all_allocations(t_context *ctx);

/*parsing.c*/

t_cmd		*parse_tokens(t_token **tokens);
t_cmd		*create_cmd_node(t_context *ctx);
void		add_redirection(t_context *ctx, t_redir **redirs, t_token **tokens);
void		add_arg_to_cmd(t_context *ctx, t_cmd *cmd, char *value);

/*process_input.c*/
void		process_input(t_context *ctx, char *input);
bool		validate_syntax(t_token *tokens);
void		expand_ast(t_context *ctx, t_cmd *ast);
//void		execute_ast(t_context *ctx, t_cmd *ast);

/*signals.c*/


/*expanding_input.c*/
char		*expand_dquote(char *value);
char		*handle_dollar(char *str, int *i, t_context *ctx);
char		*handle_even_dollars(int count, char *value, t_context *ctx);
t_token		*handle_dollar_groups(int count, int rest, int *i);
char		*handle_space(char *str, int *i);

/*expanding_variables.c*/
char		*expand_variable(char *value, t_context *ctx);
char		*find_env_value(t_env *env, char *var);
char		*expand_one_variable(char *value, t_context *ctx);
char		*expand_multi_variable(char *value, int count, int rest, \
			t_context *ctx);

/*handle_quote_tokens.c*/
t_token		*dquote_token(char *input, int *i);
t_token		*quote_token(char *input, int *i);
char		*expand_quote(char *value);

/*tokenizer_variables.c*/
t_token		*variable_token(char *input, int *i);
t_token		*variable_token_get_pid(int *index, int num_pairs, int remainder);
t_token		*variable_token_env(char *input, int *i);
int			create_double_dollar_tokens(t_token **head, int count);
int			create_single_dollar_token(t_token **head, int remainder);

/*tokenizer.c*/
t_token		*tokenizer_input(char *input);
t_token		*process_next_token(char *input, int *i);
t_token		*word_token(char *input, int *i);
t_token		*special_token(char *input, int *i);

/*main_utils.c*/
t_context	*init_context(char **envp);
int			load_environment(t_context *ctx, char **envp);
void		print_prompt(t_context *ctx);
char		*get_prompt(t_context *ctx);
bool		should_process_input(char *input);

/*token_utils_1.c*/
void		add_token(t_context *ctx, t_token **list, \
			char *value, t_token_type type);
void		add_eof_token(t_context *ctx, t_token **head);
int			count_consecutive_chars(char *str, char c);
void		handle_operator(char *input, int *i, t_token **new_node);

/*token_utils.c*/
t_token		*new_token(t_token_type type, char *word);
void		free_tokens(t_context *ctx, t_token *tok);
char		*get_pid(void);
int			is_special_char(char c);
int			add_token_node(t_token **head, t_token **tail, t_token *new_node);

/*variable_utils.c*/
char		*safe_strdup(t_context *ctx, const char *s);
char		*ft_strjoin_free(char *s1, char *s2);



#endif