/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:27:33 by jhualves          #+#    #+#             */
/*   Updated: 2025/05/11 02:38:28 by jhualves         ###   ########.fr       */
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

t_context	*init_context(char **envp)
{
	t_context	*ctx;

	ctx = malloc(sizeof(t_context));
	if (!ctx)
		return (NULL);
	ctx->env = NULL;
	ctx->allocations = NULL;
	ctx->is_interactive = isatty(STDIN_FILENO);
	if (!load_environment(ctx, envp))
	{
		free(ctx);
		return (NULL);
	}
	return (ctx);
}

int	load_environment(t_context *ctx, char **envp)
{
	int		i;
	t_env	*node;
	char	*eq;

	i = 0;
	while (envp[i] != NULL)
	{
		eq = strchr(envp[i], '=');
		if (!eq)
			continue ;
		node = safe_malloc(ctx, sizeof(t_env));
		if (!node)
			return (0);

		node->key = strndup(envp[i], eq - envp[i]);
		node->value = strdup(eq + 1);
		node->next = ctx->env;
		ctx->env = node;
		i++;
	}

	return (1);
}
