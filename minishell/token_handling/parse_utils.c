/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 19:19:06 by luxu              #+#    #+#             */
/*   Updated: 2024/12/28 19:28:18 by luxu             ###   ########.fr       */
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
			  create_token(t->buffer, determine_token_type(t->buffer, t->prev), t->q_state));
	if (!t->prev)
		t->prev = t->data->tokens;
	else
		t->prev = t->prev->next;
}
/*
bool handle_quote_or_operator(t_tokenizer *t)
{
	char c;
	
	c = *t->line;
	if (c == '\'' || c == '\"')
	{
		//If the buffer is not empty, and either we are entering a new quote (when not in quotes), or we are closing the matching quote (when we see the corresponding ' or "), then finalize the current token
		if (t->buf_i > 0 && ( (t->q_state == NO_QUOTE) || \
							 ((t->q_state == SINGLE_QUOTE || t->q_state == DOUBLE_QUOTE) && \
							  ((t->q_state == SINGLE_QUOTE && c == '\'') || \
							   (t->q_state == DOUBLE_QUOTE && c == '\"')) ) ))
			finalize_token(t);
		toggle_quote_state(&t->q_state, c);
		t->line++;
		return (true);
	}
	if (t->q_state == NO_QUOTE &&
		(c == '|' || c == '<' || c == '>' || c == '&'))
	{
		parse_operator(t);
		return (true);
	}
	return (false);
}*/

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

//bool	handle_quote_or_operator(t_tokenizer *t)
//{
//	char	c;
//
//	c = *t->line;
//	//if (t->q_state != SINGLE_QUOTE && c == '\\' && *(t->line + 1))
//	//{
//	//	t->line++;
//	//	add_char_to_buffer(t, *t->line);
//	//	t->line++;
//	//	return (true);
//	//}
//	if (c == '\'' || c == '\"')
//	{
//		if ((t->q_state == SINGLE_QUOTE && c == '\'') ||
//			(t->q_state == DOUBLE_QUOTE && c == '\"'))
//		{
//			finalize_token(t);
//			toggle_quote_state(&t->q_state, c);
//		}
//		else if (t->q_state == NO_QUOTE)
//		{
//			toggle_quote_state(&t->q_state, c);
//		}
//		t->line++;
//		return (true);
//	}
//	if (t->q_state == NO_QUOTE && (c == '|' || c == '<' || c == '>' || c == '&'))
//	{
//		parse_operator(t);
//		return (true);
//	}
//	return (false);
//}
/*
bool	handle_quote_or_operator(t_tokenizer *t)
{
	char	c;
	
	c = *t->line;
	// Handle backslashes inside double quotes for specific cases
	if (t->q_state == DOUBLE_QUOTE && c == '\\' && *(t->line + 1))
	{
		// Only escape \, " and $
		if (*(t->line + 1) == '\\' || *(t->line + 1) == '\"' || *(t->line + 1) == '$')
		{
			t->line++; // Move past the backslash
		}
		// Always store the next character
		add_char_to_buffer(t, *t->line);
		t->line++;
		return (true);
	}
	// Handle single and double quotes
	if (c == '\'' || c == '\"')
	{
		// Closing the current quote
		if ((t->q_state == SINGLE_QUOTE && c == '\'') ||
			(t->q_state == DOUBLE_QUOTE && c == '\"'))
		{
			finalize_token(t);
			toggle_quote_state(&t->q_state, c);
		}
		// Opening a new quote
		else if (t->q_state == NO_QUOTE)
		{
			toggle_quote_state(&t->q_state, c);
		}
		t->line++;
		return (true);
	}
	// Handle operators (|, <, >, &) only outside of quotes
	if (t->q_state == NO_QUOTE && (c == '|' || c == '<' || c == '>' || c == '&'))
	{
		parse_operator(t);
		return (true);
	}
	return (false);
}*/
/**
 *@brief this version works with double qoutes without backslashes - echo "$HOME" does the expansion
 *echo "\\" - \
 *echo "Hello\\nworld" - Hello\nworld
 */
//bool	handle_quote_or_operator(t_tokenizer *t)
//{
//	char	c;
//
//	c = *t->line;
//
//	// Handle backslashes inside double quotes for specific cases
//	if (t->q_state == DOUBLE_QUOTE && c == '\\' && *(t->line + 1))
//	{
//		// Only escape \ and " but NOT $
//		if (*(t->line + 1) == '\\' || *(t->line + 1) == '\"')
//		{
//			t->line++; // Move past the backslash
//		}
//		// Preserve `\$` as-is inside the token
//		else if (*(t->line + 1) == '$')
//		{
//			add_char_to_buffer(t, '\\');  // Keep the backslash
//			t->line++;  // Move past the backslash
//		}
//
//		// Always store the next character
//		add_char_to_buffer(t, *t->line);
//		t->line++;
//		return (true);
//	}
//
//	// Handle single and double quotes
//	if (c == '\'' || c == '\"')
//	{
//		// Closing the current quote
//		if ((t->q_state == SINGLE_QUOTE && c == '\'') ||
//			(t->q_state == DOUBLE_QUOTE && c == '\"'))
//		{
//			finalize_token(t);
//			toggle_quote_state(&t->q_state, c);
//		}
//		// Opening a new quote
//		else if (t->q_state == NO_QUOTE)
//		{
//			toggle_quote_state(&t->q_state, c);
//		}
//		t->line++;
//		return (true);
//	}
//	// Handle operators (|, <, >, &) only outside of quotes
//	if (t->q_state == NO_QUOTE && (c == '|' || c == '<' || c == '>' || c == '&'))
//	{
//		parse_operator(t);
//		return (true);
//	}
//	return (false);
//}

/*bool	handle_quote_or_operator(t_tokenizer *t)
{
	char	c;
	bool	escaped;
	
	c = *t->line;
	//Gérer les backslashes dans double quotes
	if (t->q_state == DOUBLE_QUOTE && c == '\\' && *(t->line + 1))
	{
		if (*(t->line + 1) == '\\' || *(t->line + 1) == '\"')
			t->line++; //skip backslash
		else if (*(t->line + 1) == '$')//   \$, \', \" après corriger validate_quote dans parse_line
		{
			add_char_to_buffer(t, '\\');  // Keep the backslash
			t->line++;  // Move past the backslash
		}
		add_char_to_buffer(t, *t->line);
		t->line++;
		return (true);
	}
	if (c == '\'' || c == '\"')
	{
		escaped = (t->line > t->start && *(t->line - 1) == '\\');
		if (!escaped)  // Only toggle quote state if NOT escaped
		{
			if ((t->q_state == SINGLE_QUOTE && c == '\'') ||
				(t->q_state == DOUBLE_QUOTE && c == '\"'))
			{
				finalize_token(t);
				toggle_quote_state(&t->q_state, c);
			}
			else if (t->q_state == NO_QUOTE)
			{
				toggle_quote_state(&t->q_state, c);
			}
		}
		add_char_to_buffer(t, c);
		t->line++;
		return (true);
	}
	if (t->q_state == NO_QUOTE && (c == '|' || c == '<' || c == '>' || c == '&'))
	{
		parse_operator(t);
		return (true);
	}
	return (false);
}*/

bool	handle_quote_or_operator(t_tokenizer *t)
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
	if ((t->q_state == NO_QUOTE || t->q_state == DOUBLE_QUOTE) && c == '$')
	{
		next = *(t->line + 1);
		if (next != '0' && next != '$' && next != '?')
		{
			add_char_to_buffer(t, '$');
			t->line++;
			return (true);
		}
	}
	 //处理引号切换
	if (c == '\'' || c == '\"')
	{
		escaped = (t->line > t->start && *(t->line - 1) == '\\');
	
		if (!escaped)  // 只有未被 `\` 保护的引号才切换状态
		{
			if ((t->q_state == SINGLE_QUOTE && c == '\'') ||
				(t->q_state == DOUBLE_QUOTE && c == '\"'))
			{
				finalize_token(t);  // 关闭引号时，完成当前 token
				toggle_quote_state(&t->q_state, c);
			}
			else if (t->q_state == NO_QUOTE)
			{
				toggle_quote_state(&t->q_state, c);
			}
			else if ((t->q_state == SINGLE_QUOTE && c == '\"') || \
					 (t->q_state == DOUBLE_QUOTE && c == '\''))
				add_char_to_buffer(t, c);
			t->line++;
			return (true);  // **这里提前返回，不存储 `"`**
		}
		add_char_to_buffer(t, c);  // 只存入实际字符（非 `"`）
		t->line++;
		return (true);
	}
	
	// **在无引号状态下解析操作符**
	if (t->q_state == NO_QUOTE && (c == '|' || c == '<' || c == '>' || c == '&'))
	{
		parse_operator(t);
		return (true);
	}
	return (false);
	//if (c == '\'' || c == '\"')
	//{
	//	escaped = (t->line > t->start && *(t->line - 1) == '\\');
	//
	//	if (!escaped)
	//	{
	//		if ((t->q_state == SINGLE_QUOTE && c == '\'') ||
	//			(t->q_state == DOUBLE_QUOTE && c == '\"'))
	//			toggle_quote_state(&t->q_state, c);
	//		//pour gérer les quotes consécutifs comme echo 'h''e''l''l''o'
	//		else if (t->q_state == NO_QUOTE)
	//			toggle_quote_state(&t->q_state, c);
	//		t->line++;
	//		return (true);
	//	}
	//	add_char_to_buffer(t, c);
	//	t->line++;
	//	return (true);
	//}
	//if (t->q_state == NO_QUOTE && (c == '|' || c == '<' || c == '>' || c == '&'))
	//{
	//	if (t->buf_i > 0)
	//		finalize_token(t);
	//	parse_operator(t);
	//	return (true);
	//}
	//return (false);
}


