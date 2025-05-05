/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:01:02 by jhualves          #+#    #+#             */
/*   Updated: 2025/04/29 20:27:19 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft42/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>


typedef struct minishell
{
	void				*pointer;
	struct t_minishell	*next;
}	t_minishell;

typedef struct shell
{
	void				*pointer;
	struct t_minishell	*next;
}	t_shell;


t_shell	*get_shell_ptr(t_shell *passed_shell_ptr);



#endif