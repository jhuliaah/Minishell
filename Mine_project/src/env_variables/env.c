/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:49:53 by jhualves          #+#    #+#             */
/*   Updated: 2025/05/20 21:01:12 by jhualves         ###   ########.fr       */
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

static t_env *create_and_link_node(t_context *ctx, char *env_var_str)
{
	t_env   *node;
	char    *eq_ptr;

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
		node->value = NULL; // Permitir valores NULL, como no original do Yuri
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

// Obtém o valor de uma variável de ambiente
char	*get_env_value(t_env *env_list, char *key)
{
	t_env	*node;

	node = find_env_node(env_list, key);
	if (!node)
		return (NULL);
	return (node->value); // Retorna ponteiro direto, não duplica aqui. A duplicação ocorre se necessário no chamador.
}

// Define/atualiza o valor de uma variável de ambiente (ou cria uma nova se não existir)
// Usa ctx para safe_malloc e safe_free
void	set_env_value(t_context *ctx, char *key, char *value)
{
	t_env	*node;

	node = find_env_node(ctx->env, key);
	if (node)
	{
		safe_free(ctx, node->value); // Libera o valor antigo
		if (value)
			node->value = safe_strdup(ctx, value);
		else
			node->value = NULL; // Permite definir valor como NULL
		// A checagem de falha de alocação para o novo valor foi removida
		// para simplificar e reduzir linhas, assumindo que safe_strdup lidará com isso
		// ou que o erro será tratado em outro lugar se for crítico.
	}
	else
	{
		node = new_env_node(ctx, key, value);
		if (node) // Apenas liga se new_env_node for bem sucedido
		{
			node->next = ctx->env;
			ctx->env = node;
		}
	}
}

// Remove uma variável de ambiente
// Usa ctx para safe_free
int	unset_env_value(t_context *ctx, char *key)
{
	t_env	*prev;
	t_env	*current;

	prev = NULL;
	current = ctx->env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				ctx->env = current->next;
			safe_free(ctx, current->key);
			safe_free(ctx, current->value);
			safe_free(ctx, current);
			return (1); // Sucesso
		}
		prev = current;
		current = current->next;
	}
	return (0); // Não encontrado
}

static int count_valid_env_vars(t_env *env_list)
{
	int count;
	t_env *current;

	count = 0;
	current = env_list;
	while (current)
	{
		if (current->value)
			count++;
		current = current->next;
	}
	return (count);
}

static int fill_env_array(t_context *ctx, char **array, t_env *env_list, int count)
{
	t_env	*current_env;
	int		i;
	char	*key_eq_val;
	size_t	key_len;
	size_t	val_len;

	current_env = env_list;
	i = 0;
	while (current_env && i < count) // Adicionado i < count para segurança
	{
		if (current_env->value)
		{
			key_len = ft_strlen(current_env->key);
			val_len = ft_strlen(current_env->value);
			key_eq_val = safe_malloc(ctx, key_len + 1 + val_len + 1);
			if (!key_eq_val)
				return (-1); // Sinaliza erro
			ft_memcpy(key_eq_val, current_env->key, key_len);
			key_eq_val[key_len] = '=';
			ft_memcpy(key_eq_val + key_len + 1, current_env->value, val_len);
			key_eq_val[key_len + 1 + val_len] = '\0';
			array[i] = key_eq_val;
			i++;
		}
		current_env = current_env->next;
	}
	array[i] = NULL; // Garante terminação nula
	return (i); // Retorna o número de itens realmente adicionados
}

// Converte a lista de ambiente de volta para um formato char **
// Usa ctx para safe_malloc e safe_strdup
char	**env_to_array(t_context *ctx)
{
	char	**array;
	int		count;
	int     items_added;

	count = count_valid_env_vars(ctx->env);
	array = safe_malloc(ctx, sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);

	items_added = fill_env_array(ctx, array, ctx->env, count);

	if (items_added != count) // Se houve erro em fill_env_array
	{
		int k = 0;
		while (k < items_added && k >= 0)
		{
			safe_free(ctx, array[k]);
			k++;
		}
		safe_free(ctx, array);
		return (NULL);
	}
	return (array);
}

// Função para liberar o array retornado por env_to_array
void free_env_array(t_context *ctx, char **env_array)
{
	int	i;

	if (!env_array)
		return ;
	i = 0;
	while (env_array[i])
	{
		safe_free(ctx, env_array[i]);
		i++;
	}
	safe_free(ctx, env_array);
}
