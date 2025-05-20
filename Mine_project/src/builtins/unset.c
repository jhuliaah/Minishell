/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:53:54 by jhualves          #+#    #+#             */
/*   Updated: 2025/05/20 17:54:03 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_unset(t_cmd *cmd, t_env **env)
{
	int status = 0;

	if (!cmd->args[1])
		return (0);
	
	for (int i = 1; cmd->args[i]; i++)
	{
		if (!unset_env_value(env, cmd->args[i]))
			status = 1;
	}
	return (status);
}