/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:06:51 by jhualves          #+#    #+#             */
/*   Updated: 2025/05/20 16:10:26 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*dquote_token(char *input, int *i)
{
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
	word = ft_strndup(&input[start], j - start);
	new_node = new_token(TOKEN_DQUOTE, word);
	*i = j + 1;
	return (new_node);
}

t_token	*quote_token(char *input, int *i)
{
	char	*word;
	t_token	*new_node;
	int		start;
	int		j;

	start = *i + 1;
	j = start;
	while (input[j] && input[j] != '\'')
		j++;
	if (!input[j])
		return (NULL);
	word = ft_strndup(&input[start], j - start);
	new_node = new_token(TOKEN_QUOTE, word);
	*i = j + 1;
	return (new_node);
}

char	*expand_quote(char *value)
{
	return (ft_strtrim(value, '\''));
}
