#include "../minishell.h"

extern volatile sig_atomic_t sig_interrupt_flag;

const char *token_type_to_string(int type)
{
	if (type == COMMAND) return "COMMAND";
	if (type == BUILTIN) return "BUILTIN";
	if (type == ARGUMENT) return "ARGUMENT";
	if (type == SEPARATOR) return "SEPARATOR";
	if (type == PIPE) return "PIPE";
	if (type == REDIR) return "REDIR";
	if (type == OPERATOR) return "OPERATOR";
	if (type == WHITESPACE) return "WHITESPACE";
	return "DEFAULT";
}

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
				printf("Token: %s, Type: %s\n", tok->value, token_type_to_string(tok->type));
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

bool is_incomplete_command(const char *line)
{
	int len;

	len = ft_strlen(line);
	// Ignorer les espaces ou tabulations en fin de ligne
	while (len > 0 && (line[len - 1] == ' ' || line[len - 1] == '\t'))
		len--;
	// Si la dernière non-espace est un pipe, la commande est incomplète
	if (len > 0 && line[len - 1] == '|')
		return true;
	return false;
}


/**
 * @brief Boucle principale de minishell
 * @param shell_data La structure principale de minishell
 */
int	minishell_mainloop(t_shell_data *shell_data)
{
	int status = 0;
	int	parse_ret = 0;
	// int i;
	// t_token	*current;

	char *tmp;
	char *old_line;

	old_line = NULL;
	tmp = NULL;

	// i = 0;
	while (1)
	{
		// if (shell_data->exit_status > 0)
		// 	printf("%s➜ %s", RED, RESET);
		// else
		// 	printf("%s➜ %s", GREEN, RESET);
		// printf("%d\n", sig_interrupt_flag);
		// Vérifier si un SIGINT a été reçu avant le readline suivant
		// if (sig_interrupt_flag != 0)
		// {
		// 	// Cleans ?
		// 	sig_interrupt_flag = 0;
		// 	shell_data->exit_status = 130;
		// }

		if (sig_interrupt_flag != 0)
		{
			shell_data->exit_status = sig_interrupt_flag;
			sig_interrupt_flag = 0;
		}

		if (shell_data->is_interactive)
			shell_data-> line = readline(shell_data->prompt);
		//printf("%s", RESET);
		if (!shell_data->line) // EOF (Ctrl-D), évite de segfault
		{
			if (shell_data->is_interactive)
				ft_putendl_fd("exit", STDOUT);
			return (shell_data->exit_status);
		}


		// Si la commande est incomplète (| à la fin), on continue de lire. ça nous évite de devoir modifier le fonctionnement des tables de commandes ou autre
		while (is_incomplete_command(shell_data->line))
		{
			tmp = readline("> ");
			if (!tmp) // En cas de Ctrl-D sur le prompt de continuation
				break;
			{
				old_line = shell_data->line;
				shell_data->line = ft_strjoin(old_line, tmp);
				free(old_line);
				free(tmp);
			}
		}
		// Si la ligne est vide (uniquement des espaces), on passe à la prochaine itération
		if (!(*shell_data->line))
		{
			free(shell_data->line);
			shell_data->line = NULL;
			continue;
		}

		// Vérifier si une des variables d'environnement vitale (PATH, HOME, etc.) a été supprimée
		// Créer fonction séparée et ajouter autres checks de l'env si besoin
		if (check_env_var("PATH", shell_data->env) == 0 || check_env_var("HOME", shell_data->env) == 0 ||
			check_env_var("USER", shell_data->env) == 0 || /*check_env_var("HOST", shell_data->env) == 0 ||*/
			check_env_var("PWD", shell_data->env) == 0)
		{
			ft_putendl_fd("Error: One or more vital environment variables have been removed.", STDERR);
			return (1);
		}
		else if (*shell_data->line)
		{
			add_history(shell_data->line);
			parse_ret = parse_line(shell_data);
			if (parse_ret == 0)
				shell_data->parse_state = 0;
			if (parse_ret != 0)
			{
				free (shell_data->line);
				free_token_list(shell_data->tokens);
				free_command_table(&shell_data->command_table);
				shell_data->line = NULL;
				shell_data->tokens = NULL;
				shell_data->command_table = NULL;
				shell_data->parse_state = parse_ret;
				continue;
			}
			//parse_line(shell_data);

			// Partie pour gérer les futures retours d'erreurs de parse_line (condition à adapter)
			// if (shell_data->exit_status != 0)
			// {
			// 	// Libération des élements crees jusqu'à trouver l'erreur
			// 	if (shell_data->tokens)
			// 	{
			// 		free_token_list(shell_data->tokens);
			// 		shell_data->tokens = NULL;
			// 	}
			// 	if (shell_data->command_table)
			// 	{
			// 		free_command_table(&shell_data->command_table);
			// 	}
			// 	shell_data->line = NULL;
			// 	shell_data->exit_status = 0;
			// 	continue;

			// }
			//////// shell_data->tokens et pas shell_data->command_table->token_list ? ///////////////
			if (!shell_data->tokens)
				continue;//Pour gérer la ligne de commande avec que des whitespaces ------- On devrait free line ou quelque chose ici non ?
			//print_command_table(shell_data->command_table);

			// On choisit quel protocole utiliser (pipe ou non)
			if (!shell_data->command_table->check_pipe)
				status = exec_simple_command(shell_data->command_table, shell_data);
			 else
			 	status = execute_piped_commands(shell_data->command_table, shell_data);

			if (shell_data->command_table->fd_in != STDIN_FILENO && shell_data->command_table->fd_in != -1)
				close(shell_data->command_table->fd_in);
			if (shell_data->command_table->fd_out != STDOUT_FILENO && shell_data->command_table->fd_out != -1)
				close(shell_data->command_table->fd_out);
			if (status == -1)
				break;
			//if (shell_data->exit_status == 1)
			//	break;
			shell_data->exit_status = status;
		}
		free(shell_data->line);
		free_token_list(shell_data->tokens);
		free_command_table(&shell_data->command_table);
		shell_data->line = NULL;
		shell_data->tokens = NULL;
		shell_data->command_table = NULL;
	}
	// free (shell_data->line);
	// free_token_list(shell_data->tokens);
	// free_command_table(&shell_data->command_table);
	// free_shell_data(shell_data);
	// shell_data->line = NULL;
	// shell_data->tokens = NULL;
	return (status);
}
