/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourLogin <yourLogin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:18:12 by yourLogin         #+#    #+#             */
/*   Updated: 2025/01/06 17:39:00 by yourLogin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*create_token(const char *value, int type)
{
	t_token	*new_token;
	
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = ft_strdup(value);
	new_token->type = type;
	new_token->quote_state = NO_QUOTE;
	new_token->previous = NULL;
	new_token->next = NULL;
	return (new_token);
}

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

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return  ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
/*int determine_token_type(const char *value, const t_token *previous_token)
{
	if (is_separator(value))
		return (SEPARATOR);
	if (is_operator(value))
		return (OPERATOR);
	if (is_pipe(value))
		return (PIPE);
	if (is_redirection(value))
		return (REDIR);
	if (ft_strlen(value) == 1 && (value[0] == ' ' || value[0] == '\t' || value[0] == '\n'))
		return (WHITESPACE);
	if (is_builtin(value))
		return (BUILTIN);
	
	// If there is no previous token OR it's a separator, it's a command
	if (!previous_token || previous_token->type == SEPARATOR)
		return (COMMAND);
	
	// Handle redirection cases properly
	if (previous_token->type == ARGUMENT && previous_token->previous &&
		is_operator(previous_token->previous->value))
		return (COMMAND);
	
	// If none of the above cases apply, it's an argument
	return (ARGUMENT);
}*/

int determine_token_type(const char *value, const t_token *previous_token, bool *command_found)
{
	if (is_separator(value)) 
	{
		*command_found = false;
		return (SEPARATOR);
	}
	if (is_pipe(value)) 
	{
		*command_found = false;
		return (PIPE);
	}
	if (is_redirection(value)) 
		return (REDIR);
	if (is_operator(value))
		return (OPERATOR);
	if (previous_token)
	{
		if (previous_token->type == REDIR)
			return (FILENAME);
	}
	if (is_builtin(value))
	{
		*command_found = true;
		return (BUILTIN);
	}
	// Si pas de commande trouvée avant et
	if (!*command_found && (!previous_token || previous_token->type == SEPARATOR ||
							previous_token->type == PIPE || previous_token->type == FILENAME))
	{
		*command_found = true;
		return (COMMAND);
	}
	return (ARGUMENT);
}

void	finalize_token(t_tokenizer *t)
{
	if (t->buf_i > 0)
	{
		t->buffer[t->buf_i] = '\0';
		add_token(&t->data->tokens, create_token(t->buffer, determine_token_type(t->buffer, t->prev, &t->command_found)));
		if (!t->prev)
			t->prev = t->data->tokens;
		else
			t->prev = t->prev->next;
		t->buf_i = 0;
	}
}
