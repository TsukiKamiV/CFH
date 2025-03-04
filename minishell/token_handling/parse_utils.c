/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpantign <maildelulua42@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 19:19:06 by luxu              #+#    #+#             */
/*   Updated: 2025/03/01 14:06:10 by lpantign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
 * Toggle between NO_QUOTE <-> SINGLE_QUOTE or NO_QUOTE <-> DOUBLE_QUOTE,
 * ignoring if we are in the other quote type.
 */
void	toggle_quote_state(t_quote_state *q_state, char c)
{
	/*
	 * Only toggle to SINGLE_QUOTE if currently NO_QUOTE,
	 * or toggle back to NO_QUOTE if we’re in SINGLE_QUOTE.
	 */
	if (*q_state == NO_QUOTE && c == '\'')
		*q_state = SINGLE_QUOTE;
	else if (*q_state == SINGLE_QUOTE && c == '\'')
		*q_state = NO_QUOTE;
	/*
	 * Only toggle to DOUBLE_QUOTE if currently NO_QUOTE,
	 * or toggle back to NO_QUOTE if we’re in DOUBLE_QUOTE.
	 */
	else if (*q_state == NO_QUOTE && c == '\"')
		*q_state = DOUBLE_QUOTE;
	else if (*q_state == DOUBLE_QUOTE && c == '\"')
		*q_state = NO_QUOTE;
}

void	parse_operator(t_tokenizer *t)
{
	char first;

	first = *t->line;
	if (t->buf_i > 0)
		finalize_token(t);
	t->buffer[0] = first;
	t->buffer[1] = '\0';
	t->line++;
	if ((*t->line == first) && (first == '|' || first == '&'
								|| first == '<' || first == '>'))
	{
		t->buffer[1] = *t->line;
		t->buffer[2] = '\0';
		t->line++;
	}
	add_token(&t->data->tokens,
			  create_token(t->buffer, determine_token_type(t->buffer, t->prev)));
	if (!t->prev)
		t->prev = t->data->tokens;
	else
		t->prev = t->prev->next;
}

void	add_char_to_buffer(t_tokenizer *t, char c)
{
	if (t->buf_i < PARSER_BUFFER_SIZE - 1)
	{
		t->buffer[t->buf_i] = c;
		t->buf_i++;
		t->buffer[t->buf_i] = '\0';
	}
	else
		/*
		 * Option A: Ignore character if buffer is full.
		 * Option B: finalize_token(t) and then start new token logic.
		 * For now, we'll just ignore it.
		 */
		return ;
}


/*bool	handle_quote_or_operator(t_tokenizer *t)
{
	char	c;
	bool	escaped;
	char	next;

	c = *t->line;

	if (t->q_state == DOUBLE_QUOTE && c == '\\' && *(t->line + 1)) //Gestion de backslash 0 supprimer???
	{
		if (*(t->line + 1) == '\\' || *(t->line + 1) == '\"' || *(t->line + 1) == '$')
		{
			add_char_to_buffer(t, '\\'); // stocker le backslash
			t->line++; //gérerecho  le caractère suivant
		}
		add_char_to_buffer(t, *t->line);
		t->line++;
		return (true);
	}
	//expansion seulement entre doubles quotes entiers ou sans quotes
	if ((t->q_state == NO_QUOTE || t->q_state == DOUBLE_QUOTE) && c == '$')
	{
		next = *(t->line + 1);
		if (next != '0' && next != '$' && next != '?')
		{
			add_char_to_buffer(t, '$');
			t->line++;
			t->expanding = true;
			return (true);
		}
	}
	if (c == '\'' || c == '\"')
	{
		escaped = (t->line > t->start && *(t->line - 1) == '\\');
		
		// 处理关闭引号
		if (!escaped)
		{
			if ((t->q_state == SINGLE_QUOTE && c == '\'') ||
				(t->q_state == DOUBLE_QUOTE && c == '\"'))
			{
				toggle_quote_state(&t->q_state, c);
				
				// 关闭引号后，如果前面是环境变量扩展，则 finalize_token()
				if (t->expanding)
				{
					finalize_token(t);
					//t->line++;
					t->expanding = false;
				}
				if (*(t->line + 1) != '\0' && (*(t->line + 1) == '\'' || *(t->line + 1) == '\"'))
				{
					t->line++;
					return (false);
				}
				t->line++;
				return (true);
			}
			else if (t->q_state == NO_QUOTE)
				toggle_quote_state(&t->q_state, c);
			t->line++;
			return (true);
		}
		
		// **如果 `"` 被转义，则正常存入 buffer**
		add_char_to_buffer(t, c);
		t->line++;
		return (false);
	}	
	if (t->q_state == NO_QUOTE && (c == '|' || c == '<' || c == '>' || c == '&'))
	{
		//if (t->buf_i > 0)
			//finalize_token(t);
		parse_operator(t);
		return (true);
	}
	return (false);
}*/

bool	handle_quote_or_operator(t_tokenizer *t)
{
	char	c;

	c = *t->line;
	if (c == '\'' || c == '\"')
	{
		add_char_to_buffer(t, c);
		toggle_quote_state(&t->q_state, c);
		t->line++;
		return (true);
	}
	if (t->q_state == NO_QUOTE && (c == '|' || c == '<' || c == '>' || c == '&'))
	{
		parse_operator(t);
		return (true);
	}
	return (false);
}


