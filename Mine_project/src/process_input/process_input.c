/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:40:09 by jhualves          #+#    #+#             */
/*   Updated: 2025/05/20 16:11:32 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	process_input(t_context *ctx, char *input)
{
	t_token	*tokens;
	t_cmd	*ast;

	tokens = tokenizer_input(input);
	if (!tokens)
	{
		ctx->exit_status = 2;
		return ;
	}
	if (!validate_syntax(tokens))
	{
		ctx->exit_status = 2;
		free_tokens(ctx, tokens);
		return ;
	}
	ast = parse_tokens(tokens);
	free_tokens(ctx, tokens);
	if (!ast)
	{
		ctx->exit_status = 2;
		return ;
	}
	expand_ast(ctx, ast);
	execute_ast(ctx, ast);
	free_ast(ctx, ast);
}

bool	validate_syntax(t_token *tokens)
{
	t_token	*prev;

	prev = NULL;
	while (tokens)
	{
		if (tokens->type == TOKEN_PIPE && (!prev || is_redirection(prev->type)))
		{
			print_syntax_error("|");
			return (false);
		}
		if (is_redirection(tokens->type) && \
			(!tokens->next || tokens->next->type != TOKEN_WORD))
		{
			print_syntax_error("newline");
			return (false);
		}
		prev = tokens;
		tokens = tokens->next;
	}
	return (true);
}

void	expand_ast(t_context *ctx, t_cmd *ast)
{
	t_cmd	*current;
	int		i;

	current = ast;
	while (current)
	{
		i = 0;
		while (current->args[i])
		{
			expand_variables(ctx, &current->args[i]);
			remove_quotes(current->args[i]);
			i++;
		}
		current = current->next;
	}
}

// void	execute_ast(t_context *ctx, t_cmd *ast) // verificar se essa função precisa ou se o Yuri fez
// {
// 	t_cmd   *current = ast;
// 	int     pipe_fd[2];
// 	int     in_fd = STDIN_FILENO;

// 	while (current)
// 	{
// 		// Cria pipe se houver próximo comando
// 		if (current->next && pipe(pipe_fd) == -1)
// 		{
// 			perror("minishell");
// 			ctx->exit_status = 1;
// 			return ;
// 		}

// 		execute_command(ctx, current, in_fd, current->next ? pipe_fd[1] : STDOUT_FILENO);
// 		// Prepara para o próximo comando no pipeline
// 		if (in_fd != STDIN_FILENO)
// 			close(in_fd);
// 		if (current->next)
// 		{
// 			close(pipe_fd[1]);
// 			in_fd = pipe_fd[0];
// 		}

// 		current = current->next;
// 	}
// }
