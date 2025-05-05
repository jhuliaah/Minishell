/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:27:33 by jhualves          #+#    #+#             */
/*   Updated: 2025/04/29 20:29:52 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*get_shell_ptr(t_shell *passed_shell_ptr)
{
	static t_shell	*shell_ptr;

	if (passed_shell_ptr)
		shell_ptr = passed_shell_ptr;
	return (shell_ptr);
}
