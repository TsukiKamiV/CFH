#include "../minishell.h"

/*
void	print_command_table(t_command_table *head)
{
	t_command_table	*current;
	int				cmd_index;
	int				i;

	current = head;
	cmd_index = 0;
	while (current)
	{
		printf("\n===== Command Table #%d =====\n", cmd_index);

		// Print all arguments in parsed_command
		if (current->parsed_command)
		{
			i = 0;
			while (current->parsed_command[i])
			{
				printf("  Arg[%d]: %s\n", i, current->parsed_command[i]);
				i++;
			}
		}
		else
			printf("  No parsed_command found.\n");

		// Print file descriptors
		printf("  fd_in = %d, fd_out = %d\n", current->fd_in, current->fd_out);

		// Print pipe and redirection checks
		printf("  check_pipe = %s\n", current->check_pipe ? "true" : "false");
		printf("  check_redir = %s\n", current->check_redir ? "true" : "false");

		// Print token list info (if present)
		if (current->token_list)
		{
			t_token *tok = current->token_list;
			printf("  Token list:\n");
			while (tok)
			{
				printf("    Value: '%s', Type: %d\n", tok->value, tok->type);
				tok = tok->next;
			}
		}
		else
			printf("  No token list.\n");

		// Move to the next command
		current = current->next;
		cmd_index++;
	}
	printf("\n");
}
*/

/**
 * @brief Boucle principale de minishell
 * @param shell_data La structure principale de minishell
 
void	minishell_mainloop(t_shell_data *shell_data)
{
	int status;

	status = 0;
	int i = 0;
	while (1)
	{
		shell_data->line = readline(shell_data->prompt);
		if (!shell_data->line) // EOF (Ctrl-D), évite de segfault
			return (printf("exit\n"), free(shell_data->line));
		if (*shell_data->line)
		{
			add_history(shell_data->line);
			parse_line(shell_data);
			// while (shell_data->command_table->token_list)
			// {
			// 	printf("Value: %s\n", shell_data->command_table->token_list->value);
			// 	printf("Type: %d\n", shell_data->command_table->token_list->type);
			// 	shell_data->tokens = shell_data->command_table->token_list;
			// 	shell_data->command_table->token_list = shell_data->command_table->token_list->next;
			// 	i++;
			// }
			while (shell_data->tokens)
			{
				printf("Value: %s\n", shell_data->tokens->value);
				printf("Type: %d\n", shell_data->tokens->type);
				shell_data->tokens = shell_data->tokens->next;
				i++;
			}
			status = exec_simple_command(shell_data->command_table, shell_data);
		}
		free(shell_data->line);
		free_tokens(shell_data->tokens);
		free_command_table(&shell_data->command_table);
		shell_data->tokens = NULL;
	}
	(void)status;
}*/

void minishell_mainloop(t_shell_data *shell_data)
{
    int status;
    int i = 0;

    status = 0;
    while (1)
    {
        shell_data->line = readline(shell_data->prompt);
        if (!shell_data->line) // EOF (Ctrl-D), avoid segfault
        {
            printf("exit\n");
            break; // Exit the loop instead of returning
        }

        if (*shell_data->line)
        {
            add_history(shell_data->line);
            parse_line(shell_data);

            // Traverse the tokens without modifying shell_data->tokens
            t_token *current = shell_data->tokens;
            while (current)
            {
                //printf("Value: %s\n", current->value);
                //printf("Type: %d\n", current->type);
                current = current->next;
                i++;
            }

            // Execute command
            status = exec_simple_command(shell_data->command_table, shell_data);
        }

        // Cleanup
        free(shell_data->line);
        free_tokens(shell_data->tokens);
        free_command_table(&shell_data->command_table);
	free (shell_data->prompt);

        // Reset pointers
        shell_data->line = NULL;
        shell_data->tokens = NULL;
    }

    // Additional cleanup if needed before exiting the shell
    free(shell_data->line);
    free_tokens(shell_data->tokens);
    free_command_table(&shell_data->command_table);
	free_shell_data(shell_data);
    shell_data->line = NULL;
    shell_data->tokens = NULL;
}

