/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:49:53 by jhualves          #+#    #+#             */
/*   Updated: 2025/05/20 23:35:33 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Mantida a sua lógica original de free_env_list, adaptada para usar safe_free se necessário
// e para ser chamada a partir do contexto.
void	free_env_list(t_context *ctx, t_env *env_list)
{
	t_env	*next;

	while (env_list)
	{
		next = env_list->next;
		safe_free(ctx, env_list->key);
		safe_free(ctx, env_list->value);
		safe_free(ctx, env_list);
		env_list = next;
	}
}

t_env	*create_and_link_node(t_context *ctx, char *env_var_str)
{
	t_env	*node;
	char	*eq_ptr;

	node = safe_malloc(ctx, sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = safe_strdup(ctx, env_var_str);
	if (!node->key)
	{
		safe_free(ctx, node);
		return (NULL);
	}
	eq_ptr = ft_strchr(node->key, '=');
	*eq_ptr = '\0';
	node->value = safe_strdup(ctx, eq_ptr + 1);
	if (!node->value)
	{
		safe_free(ctx, node->key);
		safe_free(ctx, node);
		return (NULL);
	}
	node->next = ctx->env;
	ctx->env = node;
	return (node);
}

int	load_environment(t_context *ctx, char **envp)
{
	int		i;
	char	*current_env_var;

	i = 0;
	while (envp && envp[i])
	{
		current_env_var = envp[i];
		if (ft_strchr(current_env_var, '='))
		{
			if (!create_and_link_node(ctx, current_env_var))
				return (0); // Falha na criação do nó
		}
		i++;
	}
	return (1);
}

// Funções adicionadas/adaptadas do environment_yuri/env.c

// Cria um novo nó t_env usando safe_malloc
t_env	*new_env_node(t_context *ctx, char *key, char *value)
{
	t_env	*node;

	node = safe_malloc(ctx, sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = safe_strdup(ctx, key);
	if (!node->key)
	{
		safe_free(ctx, node);
		return (NULL);
	}
	if (value)
	{
		node->value = safe_strdup(ctx, value);
		if (!node->value)
		{
			safe_free(ctx, node->key);
			safe_free(ctx, node);
			return (NULL);
		}
	}
	else
		node->value = NULL;
	node->next = NULL;
	return (node);
}

// Encontra um nó na lista de ambiente pela chave
t_env	*find_env_node(t_env *env_list, char *key)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->key, key) == 0)
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}
