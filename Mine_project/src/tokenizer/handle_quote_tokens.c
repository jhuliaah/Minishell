/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:06:51 by jhualves          #+#    #+#             */
/*   Updated: 2025/05/20 19:13:23 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*dquote_token(char *input, int *i)
{
	char	*quotation;
	char	*word;
	t_token	*new_node;
	int		start;
	int		j;

	start = *i + 1;
	j = start;
	while (input[j] && input[j] != '\"')
		j++;
	if (!input[j])
		return (NULL);
	quotation = ft_safe_strndup(get_context(), &input[start], j - start);
	word = expand_dquote(quotation); //VERIFICAR NA PARTE DE EXECUÇÃO
	new_node = new_token(TOKEN_DQUOTE, word);
	*i = j + 1;
	return (new_node);
}

t_token	*quote_token(char *input, int *i)
{
	char	*word;
	char	*quotation;
	t_token	*new_node;
	int		start;
	int		j;

	start = *i + 1;
	j = start;
	while (input[j] && input[j] != '\'')
		j++;
	if (!input[j])
		return (NULL);
	word = ft_safe_strndup(get_context(), &input[start], j - start);
	new_node = new_token(TOKEN_QUOTE, word);
	*i = j + 1;
	return (new_node);
}
