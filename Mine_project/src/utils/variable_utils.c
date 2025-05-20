/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:23:22 by jhualves          #+#    #+#             */
/*   Updated: 2025/05/20 18:28:23 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*safe_strdup(t_context *ctx, const char *s)
{
	char	*dup;

	dup = safe_malloc(ctx, ft_strlen(s) + 1);
	ft_strlcpy(dup, s, ft_strlen(s) + 1);
	return (dup);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (result);
}

char	*ft_safe_strndup(t_context *ctx, const char *s, size_t size)
{
	size_t	i;
	char	*dup;

	dup = safe_malloc(ctx, size + 1);
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
