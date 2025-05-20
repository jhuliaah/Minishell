/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:00:18 by jhualves          #+#    #+#             */
/*   Updated: 2025/05/20 17:43:10 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	redirect_input(char *command)
{
	char	*input_redirect;
	char	*file_name;
	int		fd;

	input_redirect = get_redirect_position(command, '<');
	if (!input_redirect)
		return (SUCCESS);
	file_name = get_label_name(input_redirect);
	if (!file_name)
		return (FAILED);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		print_error("open", file_name, strerror(errno));
		free(file_name);
		return (FAILED);
	}
	redirect_fd(fd, STDIN_FILENO);
	free(file_name);
	return (SUCCESS);
}
