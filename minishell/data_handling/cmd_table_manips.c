#include "../minishell.h"


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
	new_command->fd_in = STDIN_FILENO;
	new_command->fd_out = STDOUT_FILENO;
	new_command->check_pipe = false;
	new_command->check_redir = false;
	new_command->next = NULL;
	return (new_command);
}

/**
 *@brief séparée de parse_tokens_into_command_table pour des raisons des normes
 */
//t_token	*tokens_into_cmd_annex(t_command_table *cmd, t_token *current, int *i, t_shell_data *data, int *ret)
//{
//	if (!current)
//		return (NULL);
//
//	if (current->type == PIPE)
//	{
//		if (!current->next || current->next->type == PIPE)
//		{
//			set_error(data, "Syntax error near unexpected token '|'\n", 2);
//			*ret = 2;
//			return (NULL);
//		}
//		cmd->check_pipe = true;
//		return (current);
//	}
//	else if (current->type == REDIR)
//	{
//		cmd->check_redir = true;
//		if (!current->next)//si rien n'est écrit après REDIR
//		{
//			set_error(data, "Syntax error near unexpected token `newline'\n", 2);
//			*ret = 2;
//			return (NULL);
//		}
//		if (current->next->type == REDIR)//si REDIR consécutif, l'erreur est sur le deuxième REDIR
//		{
//			set_error(data, "Syntax error near unexpected token '", 2);
//			ft_putstr_fd(current->next->value, 2);
//			ft_putendl_fd("'", 2);
//			*ret = 2;
//			return (NULL);
//		}
//		if (handle_redirection(cmd, current, data) == -1)
//		{
//			*ret = 1;
//			return (NULL);
//		}
//		current = current->next;
//		if (current)
//			return (current->next);
//		else
//			return (NULL);
//	}
//	else
//	{
//		// Tok = partie de commande ou argument
//		cmd->parsed_command[*i] = ft_strdup(current->value);
//		if (!cmd->parsed_command[*i])
//		{
//			free_string_array(cmd->parsed_command);
//			*ret = 1;
//			return (NULL);
//		}
//		(*i)++;
//		return (current->next);
//	}
//}



static t_token	*handle_pipe_case(t_command_table *cmd, t_token *current, t_shell_data *data, int *ret)
{
	if (!current->next || current->next->type == PIPE)
	{
		set_error(data, "Syntax error near unexpected token '|'\n", 2);
		*ret = 2;
		return (NULL);
	}
	cmd->check_pipe = true;
	return (current);
}

static t_token	*handle_redir_case(t_command_table *cmd, t_token *current, t_shell_data *data, int *ret)
{
	cmd->check_redir = true;
	if (!current->next)
	{
		set_error(data, "Syntax error near unexpected token `newline'\n", 2);
		*ret = 2;
		return (NULL);
	}
	if (current->next->type == REDIR)
	{
		set_error(data, "Syntax error near unexpected token '", 2);
		ft_putstr_fd(current->next->value, 2);
		ft_putendl_fd("'", 2);
		*ret = 2;
		return (NULL);
	}
	if (handle_redirection(cmd, current, data) == -1)
	{
		*ret = 1;
		return (NULL);
	}
	return (current->next->next);
}

static t_token	*handle_regular_case(t_command_table *cmd, t_token *current, int *i, int *ret)
{
	cmd->parsed_command[*i] = ft_strdup(current->value);
	if (!cmd->parsed_command[*i])
	{
		free_string_array(cmd->parsed_command);
		*ret = 1;
		return (NULL);
	}
	(*i)++;
	return (current->next);
}

t_token	*tokens_into_cmd_annex(t_command_table *cmd, t_token *current, int *i, t_shell_data *data, int *ret)
{
	if (!current)
		return (NULL);
	if (current->type == PIPE)
		return (handle_pipe_case(cmd, current, data, ret));
	else if (current->type == REDIR)
		return (handle_redir_case(cmd, current, data, ret));
	else
		return (handle_regular_case(cmd, current, i, ret));
}

/**
 * Construit le tableau de commande et la liste de tokens associés à partir de la liste
 * de tokens complète. Dans le cas d'une redirection placée en début de ligne (ex: "< file cat"),
 * handle_redirection est exécuté et le token de commande (ici "cat") est correctement récupéré.
 *
 * @param cmd La commande à remplir.
 * @param current Le token courant dans la liste.
 * @return Le token à traiter pour la commande suivante (si PIPE) ou NULL.
 */
t_token	*parse_tokens_into_command_table(t_command_table *cmd, t_token *current, t_shell_data *data, int *ret)
{
	t_token	*start_of_cmd;
	int		i;

	i = 0;
	start_of_cmd = current;
	cmd->parsed_command = calloc(256, sizeof(char *));
	if (!cmd->parsed_command)
	{
		*ret = 1;
		return (NULL);
	}
	while (current)
	{
		current = tokens_into_cmd_annex(cmd, current, &i, data, ret);
		if (*ret != 0)
			break;
		if (cmd->check_pipe)
			break;
	}
	cmd->parsed_command[i] = NULL;
	cmd->token_list = init_token_list(start_of_cmd, current);
	if (cmd->check_pipe && current)
		return (current->next);
	return (NULL);
}

/**
 * remplir le tableau de commande avec les booleans et des commandes (commandes divisées par des pipes)
 * @param un pointeur du tableau de cmd et un double pointeur pour naviguer dans les tokens
 * @return remplissage du structure, ne retourne rien
 */
int	fill_command_table(t_shell_data *data)
{
	t_token	*current;
	t_command_table	*new_cmd;
	t_command_table	*last_cmd;
	int				ret;

	current = data->tokens;
	last_cmd = NULL;
	ret = 0;
	while (current)
	{
		new_cmd = init_command_table();
		if (!new_cmd)
			error_exit(data, "Failed to create command table.", 1);//quel est le code d'erreur ici?
		current = parse_tokens_into_command_table(new_cmd, current, data, &ret);
		if (!data->command_table)
			data->command_table = new_cmd;
		else
			last_cmd->next = new_cmd;
		last_cmd = new_cmd;
	}
	//print_tab(data->command_table->parsed_command);
	return (ret);
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
 * Build a fresh token list by iterating from `start` up to (but not including) a pipe '|'
 * or the end of the token list. Creates *new* t_token nodes (copies values/types).
 */
t_token *init_token_list(t_token *start, t_token *end)
{
	t_token *head;
	t_token *tail;
	t_token	*new_token;
	
	head = NULL;
	tail = NULL;
	// Copy tokens from `start` up to `end` (not including `end`)
	while (start && start != end)
	{
		new_token = malloc(sizeof(t_token));
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
	return (head);
}

/**
 * @brief Free une liste de tokens en entier
 * @param head La liste de tokens à free
 */
/*
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
			printf("Freeing: %s\n", current->value);
			free(current->value);
		}
		free(current);
		current = next;
	}
}*/

void free_token_list(t_token *head)
{
	t_token *current = head;
	t_token *next;

	if (!current)
		return;

	while (current)
	{
		next = current->next;
		if (current->value != NULL)
		{
			free(current->value);
			current->value = NULL;
		}
		free(current);
		current = next;
	}
	current = NULL;
}

/**
 * @brief Free une table de commandes
 * @param head La table de commandes à free
 */
void	free_command_table(t_command_table **head)
{
	t_command_table *current;
	t_command_table *next;

	if (!head || !*head)
		return;
	current = *head;
	while (current)
	{
		next = current->next;
		if (current->parsed_command)
		{
			free_string_array(current->parsed_command);
			current->parsed_command = NULL;  // Éviter les doubles free
		}
		if (current->token_list)
		{
			free_token_list(current->token_list);
			current->token_list = NULL;
		}
		free(current);
		current = next;
	}
	*head = NULL;
}
