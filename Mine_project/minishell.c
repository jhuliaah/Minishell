/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:27:33 by jhualves          #+#    #+#             */
/*   Updated: 2025/05/07 21:46:52 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_context	*ctx;
	char		*prompt;
	char		*input;

	ctx = init_context(envp);
	if (!ctx)
		return (EXIT_FAILURE);
	while (1)
	{
		if (ctx->is_interactive)
			prompt = "minishell> ";
		else
			prompt = "";
		input = readline(prompt);
		if (!input)
			break ;
		if (input[0] != '\0')
		{
			add_history(input);
			process_input(ctx, input);
			free_all_allocations(ctx);
		}
		free(input);
	}
	return (free_context(ctx), EXIT_SUCCESS);
}

