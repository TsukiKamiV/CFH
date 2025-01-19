/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 15:53:01 by luxu              #+#    #+#             */
/*   Updated: 2025/01/09 19:20:22 by yourLogin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//ou remplacer par ft_strncmp dans libft, a voir si eventuel conflit avec tous les cas extremes
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return  ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

//initialiser le structure token et former la liste
t_token	*create_token(const char *value, int type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = ft_strdup(value);
	new_token->type = type;
	new_token->previous = NULL;
	new_token->next = NULL;
	//printf("Creating token: %s\n", value);
	return (new_token);
}

//remplir la liste avec des elements
void	add_token(t_token **head, t_token *new_token)
{
	t_token	*tmp;

	if (!*head)
	{
		*head = new_token;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_token;
	new_token->previous = tmp;
}

//fonction boolean pour builtin
bool	is_builtin(const char *value)
{
	return (!ft_strcmp(value, "cd") || !ft_strcmp(value, "echo") || !ft_strcmp(value, "exit") ||\
	 !ft_strcmp(value, "pwd") || !ft_strcmp(value, "export") || !ft_strcmp(value, "unset") ||\
	  !ft_strcmp(value, "env"));
}

//separator a ajouter?
bool	is_separator(const char *value)
{
	return (!ft_strcmp(value, "||") || !ft_strcmp(value, "&&") || !ft_strcmp(value, ";"));
}

//les pipes sont une categorie ???
bool	is_operator(const char *value)
{
	return (!ft_strcmp(value, "|") || !ft_strcmp(value, ">") || !ft_strcmp(value, ">>") ||\
	 !ft_strcmp(value, "<") || !ft_strcmp(value, "<<") || !ft_strcmp(value, "&"));
}

//For now, the commands are taken as arguments too.
bool is_argument(const char *value)
{
	return (value[0] != '\0' && value[0] != '-' && !is_operator(value) && !is_separator(value));
}

//assigner une valeur enum selon type
int	determine_token_type(const char *value, const t_token *previous_token)
{
	if (is_separator(value))
		return (SEPARATOR);
	if (is_operator(value))
		return (OPERATOR);
	if (ft_strlen(value) == 1 && (value[0] == ' ' || value[0] == '\t' || value[0] == '\n'))
		return (WHITESPACE);
	if (is_builtin(value))
		return (BUILTIN);
	if (!previous_token || previous_token->type == SEPARATOR || (previous_token->type == OPERATOR && (strcmp(previous_token->value, ">") && strcmp(previous_token->value, ">>") && strcmp(previous_token->value, "<") && strcmp(previous_token->value, "<<"))))
		return (COMMAND);
	return (ARGUMENT);
}

void free_tokens(t_token *tokens)
{
    t_token *temp;
    while (tokens)
    {
        temp = tokens;
        tokens = tokens->next;
        free(temp->value);
        free(temp);
    }
}

/**
 * MAJ de la fonction le 07/01
 * Le double tableau (splitted processed input) est néanmoins stocké directement ds le structure data
 * @param shell_data (au lieu de const char *input)
 * @return void 
*/
void tokenize(t_shell_data *data)
{
    char 	*processed;
	char	**tab;
	int		i;
	t_token *new_token;
	t_token	*previous;
	
	processed = prepare_input(data->line);
    if (!processed || processed[0] == '\0')
        error_exit(data, "Failed to process input.", 1);
	//printf("Processed line: %s\n.", processed);
    tab = ft_split(processed, ' ');
	free(processed);
    if (!tab)
        error_exit(data, "Failed to split input.", 1);
	//data->tokens = NULL;
    i = 0; 
	previous = NULL;
	while (tab[i])
    {
        new_token = create_token(tab[i], determine_token_type(tab[i], previous));
		if (!new_token)
		{
			free_string_array(tab);
			free_tokens(data->tokens);
			error_exit(data, "Failed to create token.", 1);
		}
        add_token(&data->tokens, new_token);
		previous = new_token;
		i++;
    }
    free_string_array(tab);
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
void	parse_line(t_shell_data *data)
{
	//if (!validate_quotes(data->line))
		//error_exit(data, "Invalid quotes.", 2);
	
	tokenize(data);
	if (!data->tokens)
		error_exit(data, "Tokenization failed.", 1);
	fill_command_table(data);
}