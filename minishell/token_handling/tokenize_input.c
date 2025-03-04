#include "../minishell.h"

bool	handle_whitespace(t_tokenizer *t)
{
	if (t->q_state == NO_QUOTE && is_whitespace(*t->line))
	{
		finalize_token(t);
		while (*t->line && is_whitespace(*t->line))
			t->line++;
		return (true);
	}
	return (false);
}

void	parse_loop(t_tokenizer *t)
{
	while (*(t->line))
	{
		if (handle_quote_or_operator(t))
			continue ;
		if (handle_whitespace(t))
			continue ;
		if (t->buf_i < PARSER_BUFFER_SIZE - 1)
			t->buffer[t->buf_i++] = *t->line;
		t->line++;
	}
	finalize_token(t);
}

void	tokenize_line_new(t_shell_data *data)
{
	t_tokenizer tok;

	tok.line = data->line;
	tok.q_state = NO_QUOTE;
	tok.buf_i = 0;
	tok.prev = NULL;
	tok.data = data;
	tok.expanding = false;
	parse_loop(&tok);
	//if (tok.q_state != NO_QUOTE)
	//{
	//	ft_putstr_fd("Warning: Unclosed quotes.\n", 2);
	//	// Example: free_tokens(data->tokens); data->tokens = NULL
	//}
}

//fonction outil à supprimer
void print_tab(char **tab)
{
	int i = 0;

	while (tab[i] != NULL)
	{
		printf("%s\n", tab[i]);
		i++;
	}
}
/**
*Parse_line appel la tokenization en passent le shell_data comme argument
*@param shell_data
*@return void (tout est stocke ds le structure)
*/
int parse_line(t_shell_data *data)
{
	if (!validate_quotes(data->line))
	{
		printf("Invalid quotes\n");
		if (data->tokens)
		{
			free_token_list(data->tokens);
			data->tokens = NULL;
		}
		return (2);
	}
	if (is_line_empty_or_whitespace(data->line))//free data->line?
		return (0);
	tokenize_line_new(data);
	if (!data->tokens)
		return (2);
	expand_cmd_token(data->tokens, data);
	return (fill_command_table(data));
}
