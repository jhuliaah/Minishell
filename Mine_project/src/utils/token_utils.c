/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:42:26 by jhualves          #+#    #+#             */
/*   Updated: 2025/05/20 16:04:39 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*new_token(t_token_type type, char *word)
{
	t_context	*ctx;
	t_token		*new_token;

	ctx = get_context();
	new_token = safe_malloc(ctx, sizeof(t_token));
	new_token->type = type;
	new_token->value = safe_strdup(ctx, word);
	new_token->next = NULL;
	return (new_token);
}

void	free_tokens(t_context *ctx, t_token *tok)
{
	t_token	*tmp;

	if (!ctx || !tok) // Verifica contexto e tokens
		return ;
	while (tok)
	{
		tmp = tok;
		tok = tok->next;
		if (tmp->value)
			safe_free(ctx, tmp->value); // Libera valor usando o contexto
		safe_free(ctx, tmp); // Libera o nó do token
	}
}

char	*get_pid(void)
{
	pid_t	pid;
	char	*pid_str;

	pid = getpid();
	pid_str = ft_itoa(pid);
	return (pid_str);
}

int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '$');
}

int	add_token_node(t_token **head, t_token **tail, t_token *new_node)
{
	if (!new_node)
		return (0);
	if (!*head)
	{
		*head = new_node;
		*tail = new_node;
	}
	else
	{
		(*tail)->next = new_node;
		*tail = new_node;
	}
	return (1);
}
