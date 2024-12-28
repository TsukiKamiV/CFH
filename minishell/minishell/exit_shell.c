#include "minishell.h"

void	error_exit(t_shell_data *data, const char *msg, int status)
{
	if (!data)
		return; // Safeguard against null pointer
	// Print error message to stderr
	if (msg)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd((char *)msg, 2);
		ft_putstr_fd("\n", 2);
	}
		//fprintf(stderr, "Error: %s\n", msg);
	// Update the shell's exit status
	data->exit_status = status;
	
	// Write a seperate function to free allocated memories
	if (data->prompt)
		free(data->prompt);
	if (data->line)
		free(data->line);
	// If you maintain a list of commands, free it as well
	t_command *current = data->commands;
	while (current)
	{
		t_command *next = current->next;
		if (current->argv)
		{
			for (int i = 0; current->argv[i]; i++)
				free(current->argv[i]);
			free(current->argv);
		}
		if (current->input_redir)
			free(current->input_redir);
		if (current->output_redir)
			free(current->output_redir);
		free(current);
		current = next;
	}
	
	// Clear readline history
	//rl_clear_history();
	
	// Exit the program with the provided status
	exit(status);
}
