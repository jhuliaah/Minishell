/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:08:43 by jhualves          #+#    #+#             */
/*   Updated: 2025/04/18 18:52:59 by jhualves         ###   ########.fr       */
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

void	test_token_pipe(void)
{
	t_token	*tok_head;

	tok_head = tokenizer_input("ls | grep");
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

void test_single_quotes()
{
	t_token *tokens = tokenizer_input("echo 'hello world'");

	assert(tokens != NULL);
	assert(tokens->type == TOKEN_WORD);
	assert(strcmp(tokens->value, "echo") == 0);

	assert(tokens->next != NULL);
	assert(tokens->next->type == TOKEN_WORD);
	assert(strcmp(tokens->next->value, "hello world") == 0);

	assert(tokens->next->next == NULL);
	free_tokens(tokens);
	printf("✅ test_single_quotes passed\n");
}

void test_double_quotes()
{
	t_token *tokens = tokenizer_input("echo \"hello $USER\"");

	assert(tokens != NULL);
	assert(tokens->type == TOKEN_WORD);
	assert(strcmp(tokens->value, "echo") == 0);

	assert(tokens->next != NULL);
	assert(tokens->next->type == TOKEN_WORD);
	assert(strcmp(tokens->next->value, "hello $USER") == 0);

	assert(tokens->next->next == NULL);
	free_tokens(tokens);
	printf("✅ test_double_quotes passed\n");
}

void test_unclosed_single_quote()
{
	t_token *tokens = tokenizer_input("echo 'unclosed");
	assert(tokens == NULL);
	printf("✅ test_unclosed_single_quote passed (error handled)\n");
}

void	run_all_tests(void)
{
	test_token_word();
	test_token_pipe();
	test_token_variables();
	test_single_quotes();
	test_double_quotes();
	test_unclosed_single_quote();

}

int	main(void)
{
	run_all_tests();
	return (0);
}

