/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:23:21 by jhualves          #+#    #+#             */
/*   Updated: 2025/05/21 00:05:17 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*safe_malloc(t_context *ctx, size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	if (!(add_allocation(ctx, ptr)))
	{
		free (ptr);
		return (NULL);
	}
	return (ptr);
}

int	add_allocation(t_context *ctx, void *ptr)
{
	t_allocation	*new;

	new = malloc(sizeof(t_allocation));
	if (!new)
	{
		free(new);
		return (0);
	}
	new->ptr = ptr;
	new->next = ctx->allocations;
	ctx->allocations = new;
	return (1);
}

void	remove_allocation(t_context *ctx, void *ptr)
{
	t_allocation	*current;
	t_allocation	*prev;

	current = ctx->allocations;
	prev = NULL;
	while (current)
	{
		if (current->ptr == ptr)
		{
			if (prev)
				prev->next = current->next;
			else
				ctx->allocations = current->next;
			free (current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	safe_free(t_context *ctx, void *ptr)
{
	if (!ptr)
		return ;
	if (ptr)
	{
		remove_allocation(ctx, ptr);
		free(ptr);
	}
}

void	free_all_allocations(t_context *ctx)
{
	t_allocation	*current;
	t_allocation	*next;

	current = ctx->allocations;
	while (current)
	{
		next = current->next;
		free(current->ptr);
		free(current);
		current = next;
	}
	ctx->allocations = NULL;
}
//CRIAR FREE CMD; FREE AST; FREE REDIR