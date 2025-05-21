/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:52:37 by jhualves          #+#    #+#             */
/*   Updated: 2025/05/20 23:14:51 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_env(t_context *ctx)
{
    t_env *current;  // Usamos t_env* para iterar na lista de ambiente
    
    if (!ctx || !ctx->env)
        return (1);  // Tratamento de erro se ctx ou env forem NULL
    
    current = ctx->env;  // Começamos do primeiro nó da lista de ambiente
    
    while (current)
    {
        if (current->value)  // Só imprime se tiver valor
            ft_printf("%s=%s\n", current->key, current->value);
        current = current->next;  // Avança para o próximo nó
    }
    
    return (0);
}