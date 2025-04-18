char	*special_token(char *input, t_token *curr)
{
	t_token	*new_node;

	new_node = NULL;
	if (input[0] == '|' && input[1] != '|')
		new_node = new_token(TOKEN_PIPE, ft_strdup("|"));
	else if (input[0] == '>' && input[1] == '>')
		new_node = new_token(TOKEN_REDIR_APPEND, ft_strdup(">>"));
	else if (input[0] == '<' && input[1] == '<')
		new_node = new_token(TOKEN_HEREDOC, ft_strdup("<<"));
	else if (input[0] == '>' && input[1] != '>')
		new_node = new_token(TOKEN_REDIR_OUT, ft_strdup(">"));
	else if (input[0] == '<' && input[1] != '<')
		new_node = new_token(TOKEN_REDIR_IN, "<");
	else if (input[0] == '$')
		return (variable_token(input, curr));
	if (!(new_node))
		return (NULL);
	if ((input[0] == '|' && input[1] != '|')
		|| (input[0] == '>' && input[1] != '>')
		|| (input[0] == '<' && input[1] != '<'))
		input++;
	else
		input += 2;
	curr->next = new_node;
	return (input);
}