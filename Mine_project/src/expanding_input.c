/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:00:21 by jhualves          #+#    #+#             */
/*   Updated: 2025/04/28 23:56:22 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

char	*expand_quote(char *value)
{
	return (ft_strtrim(value, '\''));
}

char	*expand_dquote(char *value, char **envp)
{
	int		i;
	int		j;
	char	*str;
	char	*result;
	char	*temp;
	char	*temp1;

	result = "";
	str = value;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			temp = expand_variable(value + i, envp);
			if (!result)
				result = ft_strndup(value, (size_t)i);
			result = ft_strjoin(result, temp);
			free (temp);
			while (ft_isalnum(str[i]) && str[i] == '_')
				i++;
		}
		else if (str[i] == ' ') //não precisa, ele só considera um espaço hehehe verificar bash (JULIO NÃP CONSEGUIU AFIRMAR)
		{
			while (str[i] == ' ')
				i++;
			result = ft_strjoin(result, ' ');
		}
		else
		{
			temp1 = str + i;
			j = 0;
			while (str[i] != ' ' && str[i] != '$')
			{
				i++;
				j++;
			}
			if (!result)
				result = ft_strndup(value, (size_t)i);
			temp = ft_strndup(temp1, j);
			result = ft_strjoin(result, temp);
		}
	}
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

char	*expand_multi_variable(char *value, int j, int count, int rest,
	char **envp)
{
	char	*result;
	char	*temp;

	result = "";
	while (count > 0)
	{
		temp = ft_strdup(getpid());
		if (!result)
			result = temp;
		result = ft_strjoin(result, temp);
		free(temp);
		count--;
	}
	if (rest == 1)
	{
		j--;
		temp = expand_one_variable(value + j, envp);
		result = ft_strjoin(result, temp);
		free(temp);
	}
	return (result);
}

char	*expand_one_variable(char *value, char **envp)
{
	size_t	i;
	t_env	*env;
	char	*variable;
	char	*result;

	if (value[i] == '$' && value[i + 1] == ' ')
		return (ft_strdup('$'));
	while (value[i] != ' ')
		i++;
	variable = ft_strndup(value, i);
	env = init_env(envp);
	while (env)
	{
		if (ft_strcmp(env->key, variable))
		{
			result = ft_strdup(env->value);
			return (result);
		}
		env = env->next;
	}
	//criar verificação se não achou a variavel de ambiente
}
