#include "../minishell.h"

/**
 * @brief init une table de commandes
 * @param
 * @return t_command_table* Un nouveau pointeur vers la table de commandes

t_command_table	*init_command_table(char **parsed_command)
{
	t_command_table	*new_command;

	new_command = (t_command_table *)malloc(sizeof(t_command_table));
	if (!new_command)
		return (NULL);
	new_command->parsed_command = copy_string_array(parsed_command);
	new_command->token_list = NULL;
	new_command->fd_in = STDIN;
	new_command->fd_out = STDOUT;
	new_command->next = NULL;
	new_command->check_pipe = false;
	new_command->check_redir = false;
	return (new_command);
}
*/

/**
 * @param	void
 * @return	t_command_table
 * the parsed command will be appended in fill_command_table function
 */
t_command_table	*init_command_table(void)
{
	t_command_table	*new_command;

	new_command = (t_command_table *)malloc(sizeof(t_command_table));
	if (!new_command)
		return (NULL);
	new_command->parsed_command = NULL;
	new_command->token_list = NULL;
	new_command->fd_in = STDIN;
	new_command->fd_out = STDOUT;
	new_command->check_pipe = false;
	new_command->check_redir = false;
	new_command->next = NULL;
	return (new_command);
}

/**
 * e.g input "ls -l | grep .c | wc -l > output.txt", First command: ["ls", "-l"]; Second command: ["grep", ".c"]
 * @param (command table) (current token passed by the caller function fill_command_table)
 * @return - current->next -- if pipe in command line, return the next token to fill another command table
 * ++ATTENTOIN++ Eventuel segfault pour command complexe!!
 *         - NULL -- if no pipe in command line
 */
t_token *parse_tokens_into_command_table(t_command_table *cmd, t_token *current)
{
	t_token *start_of_cmd;
	int     i = 0;

	start_of_cmd = current;
	cmd->parsed_command = malloc(sizeof(char *) * 256);
	if (!cmd->parsed_command)
		error_exit(NULL, "Failed to allocate parsed_command.", 1);
	while (current)
	{
		if (current->type == OPERATOR && !ft_strcmp(current->value, "|"))
		{
			cmd->check_pipe = true;
			break;
		}
		// handle redirection for exec
		else if (current->type == OPERATOR && (!ft_strcmp(current->value, ">") || !ft_strcmp(current->value, ">>") || !ft_strcmp(current->value, "<") || !ft_strcmp(current->value, "<<")))
		{
			cmd->check_redir = true;
			handle_redirection(cmd, current);
		}
		else
			cmd->parsed_command[i++] = ft_strdup(current->value);
		current = current->next;
	}
	cmd->parsed_command[i] = NULL;
	// build the token list from start_of_cmd to (but not including) current
	cmd->token_list = init_token_list(start_of_cmd, current);
	// If pipe, skip it
	if (cmd->check_pipe == true && current)
		return current->next;  // move to the token after "|"
	return (NULL);
}

/**
 * remplir le tableau de commande avec les booleans et des commandes (commandes divisées par des pipes)
 * @param un pointeur du tableau de cmd et un double pointeur pour naviguer dans les tokens
 * @return remplissage du structure, ne retourne rien
 */
void	fill_command_table(t_shell_data *data)
{
	t_token	*current;
	t_command_table	*new_cmd;
	t_command_table	*last_cmd;

	current = data->tokens;
	last_cmd = NULL;
	while (current)
	{
		//create a new command table
		new_cmd = init_command_table();
		if (!new_cmd)
			error_exit(data, "Failed to create command table.", 1);
		//parse the tokens for this command
		//printf("Parsing will start\n");
		current = parse_tokens_into_command_table(new_cmd, current);
		//link the new command table to the shell data
		if (!data->command_table)
			data->command_table = new_cmd;//first command table
		else
			last_cmd->next = new_cmd;//Link to the previous command
		last_cmd = new_cmd;
	}
}

/**
 * Créer un tableau de commande, appel de la fonction d'initialisation et du remplissage
 * @param	data
 * @return	void
 */
void	create_command_table(t_shell_data *data)
{
	t_token			*current_token;
	t_command_table	*new_cmd;
	t_command_table	*last_cmd;

	current_token = data->tokens;
	last_cmd = NULL;
	while (current_token)
	{
		new_cmd = init_command_table();
		if (!new_cmd)
			error_exit(data, "Failed to create command table.", 1);
		fill_command_table(data);
		if (!data->command_table)
			data->command_table = new_cmd;
		else
			last_cmd->next = new_cmd;
		last_cmd = new_cmd;
	}
}

/**
 * @brief Ajoute une liste de tokens

void	add_token(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!*head)
	{
		*head = new_token;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_token;
	new_token->previous = current;
	new_token->next = NULL;
	new_token->type = DEFAULT;
	new_token->value = NULL;
}*/

/**
 * Build a fresh token list by iterating from `start` up to (but not including) a pipe '|'
 * or the end of the token list. Creates *new* t_token nodes (copies values/types).
 */
t_token *init_token_list(t_token *start, t_token *end)
{
	t_token *head = NULL;
	t_token *tail = NULL;

	// Copy tokens from `start` up to `end` (not including `end`)
	while (start && start != end)
	{
		t_token *new_token = malloc(sizeof(t_token));
		if (!new_token)
			return (NULL);
		new_token->value = ft_strdup(start->value);
		new_token->type = start->type;
		new_token->next = NULL;
		new_token->previous = tail;
		if (!head)
			head = new_token;
		else
			tail->next = new_token;
		tail = new_token;
		start = start->next;
	}
	return head;
}

/**
 * @brief Free une liste de tokens en entier
 * @param head La liste de tokens à free
 */
void	free_token_list(t_token *head)
{
	t_token	*current;
	t_token	*next;

	current = head;
	if (!current)
		return ;
	while (current)
	{
		next = current->next;
		if (current->value)
		{
			printf("Freeing token: %s\n", current->value);
			free(current->value);
		}
		free(current);
		current = next;
	}
}

/**
 * @brief Free une table de commandes
 * @param head La table de commandes à free
 */
void	free_command_table(t_command_table **head)
{
	t_command_table	*current;
	t_command_table	*next;

	if (!head | !*head)
		return ;
	current = *head;
	while (current)
	{
		next = current->next;
		if (current->parsed_command)
			free_string_array(current->parsed_command);
		if (current->token_list)
			free_token_list(current->token_list);
		free (current);
		current = next;
	}
	*head = NULL;
}

/**
 * @brief Ajoute à shell_data->command_table une nouvelle commande (avec pipes, non parsés)
 * @param shell_data La structure shell_data
 * @param new_command La nouvelle commande à ajouter
 *

*/
// int cmd_table_to_shell_data(t_shell_data *shell_data, char **parsed_command)
// {
// 	t_command_table	*current;
// 	t_command_table	*new_command;
// 	t_token	*token_list;

// 	current = shell_data->command_table;
// 	new_command = init_command_table(parsed_command);
// 	if (!new_command)
// 		return (1);
// 	token_list = init_token_list(parsed_command);



// 	return (0);

// }

// int main(int argc, char **argv, char **env)
// {
// 	char	**parsed_command;
// 	t_command_table	*command_table;
// 	t_token	*token_list;
// 	int	i;

// 	parsed_command = ft_split("ls -lRa /home/ | cat", ' ');
// 	if (!parsed_command)
// 		return (1);
// 	token_list = init_token_list(parsed_command); // Crée une liste de tokens, un par élément de la commande parsée
// 	command_table = init_command_table(parsed_command); // Crée une table de commandes, une par commande séparée par un pipe (encore à faire)
// 	if (!token_list)
// 	{
// 		free_string_array(parsed_command);
// 		return (1);
// 	}
// 	t_token *tmp = token_list;

// 	i = 0;
// 	printf("Commande parsée dans une liste de tokens :\n");
// 	while (tmp)
// 	{
// 		printf("token_list[%d] Value = %s\n", i, tmp->value);
// 		printf("token_list[%d] Type = %d\n", i, tmp->type);
// 		tmp = tmp->next;
// 		i++;
// 	}
// 	printf("\n");
// 	printf("Attributs tableau de commandes :\n");
// 	printf("command_table - check_pipe = %d\n", command_table->check_pipe);
// 	printf("command_table - check_redir = %d\n", command_table->check_redir);
// 	printf("command_table - fd_in = %d\n", command_table->fd_in);
// 	printf("command_table - fd_out = %d\n", command_table->fd_out);
// 	printf("command_table - next = %p\n", command_table->next);

// 	// t_shell_data	*shell_data;
// 	// shell_data = init_shell_data(env);
// 	// if (!shell_data)
// 	// {
// 	// 	free_string_array(parsed_command);
// 	// 	free_token_list(token_list);
// 	// 	free_command_table(command_table);
// 	// 	return (1);
// 	// }
// 	// t_command_table	*new_command;
// 	// new_command = init_command_table(parsed_command);
// 	// if (!new_command)
// 	// {
// 	// 	free_string_array(parsed_command);
// 	// 	free_token_list(token_list);
// 	// 	free_command_table(command_table);
// 	// 	free_shell_data(shell_data);
// 	// 	return (1);
// 	// }
// 	// cmd_table_to_shell_data(shell_data, parsed_command);
// 	// printf("Attributs shell_data->command_table :\n");
// 	// printf("shell_data->command_table - check_pipe = %d\n", shell_data->command_table->check_pipe);
// 	// printf("shell_data->command_table - check_redir = %d\n", shell_data->command_table->check_redir);
// 	// printf("shell_data->command_table - fd_in = %d\n", shell_data->command_table->fd_in);
// 	// printf("shell_data->command_table - fd_out = %d\n", shell_data->command_table->fd_out);
// 	// printf("shell_data->command_table - next = %p\n", shell_data->command_table->next);


// 	free_string_array(parsed_command);
// 	free_command_table(command_table);
// 	free_token_list(token_list);

// 	(void)argc;
// 	(void)argv;
//     (void)env;
// 	return (0);
// }

