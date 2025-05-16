/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:42:26 by jhualves          #+#    #+#             */
/*   Updated: 2025/05/16 16:30:44 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*GLOBAL VARIABLE FUNCTION*/

t_context	*get_context(void)
{
	return (get_ctx());
}

/*tokens_utils*/

void	free_tokens(t_token *tok)
{
	t_token	*tmp;

	while (tok)
	{
		tmp = tok;
		tok = tok->next;
		free(tmp->value);
		free(tmp);
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
