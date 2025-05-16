/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:27:33 by jhualves          #+#    #+#             */
/*   Updated: 2025/05/16 17:14:48 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Retorna o endereço do ponteiro, não o ponteiro em si
static t_context	**get_ctx_handle(void)
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

int	main(int argc, char **argv, char **envp)
{
	static t_context	*ctx;
	char				*prompt;
	char				*input;

	ctx = init_context(envp);
	if (!ctx)
		return ((ft_putstr("Erro: Contexto não inicializado!")), EXIT_FAILURE);
	set_context(ctx);
	while (1)
	{
		//TODO - CREATE A FUNCTION TO THE MAIN LOOP
		prompt = "";
		if (ctx->is_interactive)
			prompt = "minishell> ";
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
	return (free_context(ctx), ctx->exit_status);
}
