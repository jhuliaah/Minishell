/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:51:20 by jhualves          #+#    #+#             */
/*   Updated: 2025/05/20 22:28:07 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_cd(t_cmd *cmd, t_context *ctx)
{
	char *path;
	char cwd[PATH_MAX];
	char *oldpwd;

	if (!getcwd(cwd, sizeof(cwd)))
		return (print_error("cd", NULL, "getcwd failed"), 1);
	oldpwd = ft_strdup(cwd);
	
	if (!cmd->args[1] || ft_strcmp(cmd->args[1], "~") == 0)
		path = get_env_value(ctx->env, "HOME");
	else if (ft_strcmp(cmd->args[1], "-") == 0)
		path = get_env_value(ctx->env, "OLDPWD");
	else
		path = cmd->args[1];
	
	if (!path)
		return (free(oldpwd), print_error_msg(cmd->args[0], "HOME not set"), 1);
	
	if (chdir(path) != 0)
	{
		free(oldpwd);
		return (print_error("cd", path, strerror(errno)), 1);
	}
	
	set_env_value(ctx, "OLDPWD", oldpwd);
	free(oldpwd);
	
	if (!getcwd(cwd, sizeof(cwd)))
		return (print_error("cd", NULL, "getcwd failed"), 1);
	set_env_value(ctx, "PWD", cwd);
	
	return (0);
}

