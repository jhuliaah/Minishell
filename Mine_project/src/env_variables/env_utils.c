/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 23:35:06 by jhualves          #+#    #+#             */
/*   Updated: 2025/05/20 23:47:13 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*create_env_entry(t_context *ctx, const char *key, const char *value)
{
	char		*entry;
	size_t		key_len;
	size_t		val_len;
	size_t		total_len;

	key_len = ft_strlen(key);
	val_len = ft_strlen(value);
	total_len = key_len + val_len + 2;
	entry = safe_malloc(ctx, total_len);
	if (!entry)
		return (NULL);
	ft_memcpy(entry, key, key_len);
	entry[key_len] = '=';
	ft_memcpy(entry + key_len + 1, value, val_len);
	entry[total_len - 1] = '\0';
	return (entry);
}

int	cleanup_failed_entries(t_context *ctx, char **array, int last_index)
{
	while (last_index-- > 0)
		safe_free(ctx, array[last_index]);
	return (-1);
}

// Converte a lista de ambiente de volta para um formato char **
// Usa ctx para safe_malloc e safe_strdup
char	**env_to_array(t_context *ctx)
{
	char	**array;
	int		count;
	int		items_added;
	int		k;

	count = count_valid_env_vars(ctx->env);
	array = safe_malloc(ctx, sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	items_added = fill_env_array(ctx, array, ctx->env, count);
	if (items_added != count) // Se houve erro em fill_env_array
	{
		k = 0;
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
void	free_env_array(t_context *ctx, char **env_array)
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
