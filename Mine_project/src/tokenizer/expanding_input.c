/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:00:21 by jhualves          #+#    #+#             */
/*   Updated: 2025/05/20 23:44:16 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*expand_dquote(char *value)
{
	t_context	*ctx;
	char		*result;
	int			i;

	ctx = get_context();
	result = safe_strdup(ctx, "");
	i = 0;
	while (value[i])
	{
		if (value[i] == '$')
			result = ft_strjoin_free(result, handle_dollar(value, &i, ctx));
		else if (value[i] == ' ')
			result = ft_strjoin_free(result, handle_space(value, &i));
		else
			result = ft_strjoin_free(result, handle_other_chars(value, &i));
	}
	return (result);
}

char	*handle_dollar(char *str, int *i, t_context *ctx)
{
	char	*temp;
	char	*result;

	temp = expand_variable(str + *i, ctx);
	result = ft_strndup(str, *i);
	result = ft_strjoin_free(result, temp);
	free(temp);
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
	return (result);
}

char	*handle_even_dollars(int count, char *value, t_context *ctx)
{
	char	*result;

	result = safe_strdup(ctx, "");
	while (count-- > 0)
		result = ft_strjoin_free(result, safe_strdup(ctx, "$$"));
	return (result);
}

t_token	*handle_dollar_groups(int count, int rest, int *i)
{
	t_context	*ctx;
	t_token		*result;
	int			j;

	ctx = get_context();
	result = NULL;
	j = 0;
	while (j++ < count)
		add_token(ctx, &result, "$$", TOKEN_VARIABLE);
	if (rest)
		add_token(ctx, &result, "$", TOKEN_VARIABLE);
	*i += (count * 2) + rest;
	return (result);
}

char	*handle_space(char *str, int *i)
{
	int		j;
	char	*temp;

	j = 0;
	while (str[*i] == ' ')
	{
		(*i)++;
		j++;
	}
	temp = ft_strndup(str + *i - j, j);
	return (temp);
}
