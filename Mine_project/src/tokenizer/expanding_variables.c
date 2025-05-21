/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_variables.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:20:31 by jhualves          #+#    #+#             */
/*   Updated: 2025/05/20 20:46:42 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*expand_variable(char *value, t_context *ctx)
{
	int		count;
	int		rest;

	count = count_dollars(value);
	rest = count % 2;
	if (count > 1)
		return (expand_multi_variable(value, count / 2, rest, ctx));
	else
		return (expand_one_variable(value, ctx));
}

char	*find_env_value(t_env *env, char *var)
{
	while (env)
	{
		if (ft_strcmp(env->key, var) == 0)
			return (safe_strdup(get_context(), env->value));
		env = env->next;
	}
	return (safe_strdup(get_context(), ""));
}

char	*expand_one_variable(char *var_name, t_context *ctx)
{
	char	*expanded_value;
	char	*status_str;

	if (var_name[0] == '?' && var_name[1] == '\0')
	{
		status_str = ft_itoa(ctx->exit_status);
		if (!status_str)
			return (safe_strdup(ctx, ""));
		expanded_value = safe_strdup(ctx, status_str);
		free(status_str);
		return (expanded_value);
	}
	expanded_value = find_env_value(ctx->env, var_name);
	return (expanded_value);
}

char	*expand_multi_variable(char *value, int count, int rest, t_context *ctx)
{
	char	*result;
	char	*temp;

	result = safe_strdup(ctx, "");
	while (count-- > 0)
	{
		temp = safe_strdup(ctx, get_pid());
		result = ft_strjoin_free(result, temp);
	}
	if (rest)
	{
		temp = expand_one_variable(value + 1, ctx);
		result = ft_strjoin_free(result, temp);
	}
	return (result);
}
