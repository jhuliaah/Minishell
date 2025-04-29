/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:49:53 by jhualves          #+#    #+#             */
/*   Updated: 2025/04/28 22:48:08 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tokenizer.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

t_env	*new_env_node(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

t_env	*init_env(char **envp)
{
	t_env *head = NULL;
	t_env *tail = NULL;
	int i = 0;

	while (envp[i])
	{
		// 1. Separar key e value
		char *equal_sign = strchr(envp[i], '=');
		if (!equal_sign)
		{
			i++;
			continue; // Não é uma variável de ambiente válida
		}
		int key_len = equal_sign - envp[i];
		char *key = strndup(envp[i], key_len);
		char *value = strdup(equal_sign + 1);

		// 2. Criar novo nó
		t_env *new_node = new_env_node(key, value);
		if (!new_node)
			return (NULL); // erro

		// 3. Encadear na lista
		if (!head)
		{
			head = new_node;
			tail = new_node;
		}
		else
		{
			tail->next = new_node;
			tail = new_node;
		}
		i++;
	}
	return (head);
}
