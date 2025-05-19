/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:27:33 by jhualves          #+#    #+#             */
/*   Updated: 2025/05/19 16:17:54 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Retorna o endereço do ponteiro, não o ponteiro em si
t_context	**get_ctx_handle(void)
{
	static t_context	*ctx;

	ctx = NULL;
	return (&ctx);
}

// Define o contexto (chamado APENAS uma vez no main)
// Atribui o contexto válido
void	set_context(t_context *new_ctx)
{
	t_context	**ctx_handle;

	ctx_handle = get_ctx_handle();
	*ctx_handle = new_ctx;
}

// Retorna o contexto para uso em outros arquivos
// Retorna o valor do ponteiro estático
t_context	*get_context(void)
{
	return (*get_ctx_handle());
}

void	main_loop(t_context *ctx)
{
	char	*input;
	char	*prompt;

	while (1)
	{
		prompt = get_prompt(ctx);
		input = readline(prompt);
		if (!input)
			break ;
		if (input[0] != '\0')
		{
			add_history(input);
			process_input(ctx, input);
			if (ctx->fatal_error)
				break ;
		}
		free(input);
		free_all_allocations(ctx);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_context	*ctx;
	int			exit_status;

	ctx = init_context(envp);
	if (!ctx)
		return (ft_putstr_fd("minishell: initialization error\n", 2), \
				EXIT_FAILURE);
	set_context(ctx);
	main_loop(ctx);
	exit_status = ctx->exit_status;
	free_context(ctx);
	return (exit_status);
}

void	print_prompt(t_context *ctx)
{
	if (ctx->is_interactive)
		ft_putstr_fd("minishell> ", STDOUT_FILENO);
}

char	*get_prompt(t_context *ctx)
{
	if (ctx->is_interactive)
		return ("minishell> ");
	else
		return ("");
}

bool	should_process_input(char *input)
{
	return (input[0] != '\0');
}
