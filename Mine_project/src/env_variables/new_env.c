/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 23:33:50 by jhualves          #+#    #+#             */
/*   Updated: 2025/05/20 23:40:18 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

int	count_valid_env_vars(t_env *env_list)
{
	int		count;
	t_env	*current;

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

// Preenche o array de ambiente com os valores válidos
int	fill_env_array(t_context *ctx, char **array, t_env *env_list, int count)
{
	t_env	*current;
	int		i;
	char	*entry;

	if (!array || count < 0) // Validação básica dos parâmetros
		return (-1);
	current = env_list;
	i = 0;
	while (current && i < count)
	{
		if (current->value)
		{
			entry = create_env_entry(ctx, current->key, current->value);
			if (!entry)
				return (cleanup_failed_entries(ctx, array, i)); // Limpeza segura
			array[i++] = entry;
		}
		current = current->next;
	}
	array[i] = NULL; // Garante terminação NULL mesmo se count for maior que itens válidos
	return (i);
}
