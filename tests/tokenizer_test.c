/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:08:43 by jhualves          #+#    #+#             */
/*   Updated: 2025/04/17 22:01:37 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "tokenizer.h"

#include "../src/tokenizer.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void	free_tokens(t_token *tok_head);

void	test_token_word(void)
{
	t_token	*tok_head;

	tok_head = tokenizer_input("ls");
	assert(tok_head && tok_head->type == TOKEN_WORD);
	assert(strcmp(tok_head->value, "ls") == 0);
	assert(tok_head->next == NULL);
	free_tokens(tok_head);
	printf("✅ test_token_word passed\n");
}

void	go_through_every_token_node(t_token	*tok_head)
{
	t_token	*node;

	node = tok_head;
	ft_printf("Vamos printar agora:\n");
	fflush(stdout);
	while (node->next != NULL)
	{
		printf("Token type: %d, value: %s\n", node->type, node->value);
		fflush(stdout);
		node = node->next;
	}
}

void	test_token_pipe(void)
{
	t_token	*tok_head;

	tok_head = tokenizer_input("ls | grep");
	go_through_every_token_node(tok_head);
	assert(tok_head->type == TOKEN_WORD);
	assert(strcmp(tok_head->value, "ls") == 0);
	assert(tok_head->next->type == TOKEN_PIPE);
	assert(tok_head->next->next->type == TOKEN_WORD);
	assert(strcmp(tok_head->next->next->value, "grep") == 0);
	free_tokens(tok_head);
	printf("✅ test_token_pipe passed\n");
}

void	test_token_variables(void)
{
	t_token	*tok_head;

	tok_head = tokenizer_input("echo $$ $HOME");
	assert(tok_head->type == TOKEN_WORD);
	assert(strcmp(tok_head->value, "echo") == 0);
	assert(tok_head->next->type == TOKEN_VARIABLE);
	assert(strcmp(tok_head->next->value, "$$") == 0);
	assert(tok_head->next->next->type == TOKEN_VARIABLE);
	assert(strcmp(tok_head->next->next->value, "HOME") == 0);
	free_tokens(tok_head);
	printf("✅ test_token_variables passed\n");
}

void	run_all_tests(void)
{
	test_token_word();
	test_token_pipe();
	//test_token_variables();
}

int	main(void)
{
	run_all_tests();
	
	return (0);
}

