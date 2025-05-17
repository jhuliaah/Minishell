/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:00:21 by jhualves          #+#    #+#             */
/*   Updated: 2025/05/17 17:20:52 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*expand_quote(char *value)
{
	return (ft_strtrim(value, '\''));
}

static char	*handle_dollar(char *str, int *i, t_context *ctx)
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

static char	*handle_space(char *str, int *i)
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

char	*expand_variable(char *value, char **envp)
{
	int		j;
	int		rest;
	int		count;
	char	*result;

	j = 0;
	count = 0;
	if (value[j] == '$' && value[j + 1] == ' ')
		return (ft_strdup('$'));
	while (value[j] == '$')
	{
		count++;
		j++;
	}
	rest = count % 2;
	if (count > 1)
	{
		count /= 2;
		result = expand_multi_variable(value, j, count, rest, envp);
	}
	else
		result = expand_one_variable(value, envp);
	return (result);
}
