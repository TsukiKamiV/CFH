/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourLogin <yourLogin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:52:50 by yourLogin         #+#    #+#             */
/*   Updated: 2025/01/09 19:01:23 by yourLogin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
static void handle_double_symbols(char *processed, size_t *i, size_t *j, char symbol)
{
    processed[(*j)++] = ' ';
    processed[(*j)++] = symbol;
    processed[(*j)++] = symbol;
    processed[(*j)++] = ' ';
    *i += 2;
}

static void handle_single_symbol(const char *input, char *processed, size_t *i, size_t *j)
{
    processed[(*j)++] = ' ';
    processed[(*j)++] = input[*i];
    processed[(*j)] = ' ';
    (*i)++;
}

static void handle_whitespace(char *processed, size_t *i, size_t *j)
{
    processed[(*j)] = ' ';
    (*i)++;
}

static void handle_regular_char(const char *input, char *processed, size_t *i, size_t *j)
{
    processed[(*j)] = input[*i];
    (*i)++;
}

char    *prepare_input(const char *input)
{
    size_t  len;
    size_t  i;
    size_t  j;
    char    *processed;

    len = ft_strlen(input);
    i = 0;
    j = 0;
    processed = malloc((len * 3) + 1);
    if (!processed)
        return (NULL);
    while (i < len)
    {
        if (input[i] == '|' && input[i + 1] == '|')
            handle_double_symbols(processed, &i, &j, '|');
        else if (input[i] == '&' && input[i + 1] == '&')
            handle_double_symbols(processed, &i, &j, '&');
        else if (input[i] == '<' && input[i + 1] == '<')
            handle_double_symbols(processed, &i, &j, '<');
        else if (input[i] == '>' && input[i + 1] == '>')
            handle_double_symbols(processed, &i, &j, '>');
        else if (input[i] == '|' || input[i] == '&' || input[i] == ';' || input[i] == '<' || input[i] == '>')
            handle_single_symbol(input, processed, &i, &j);
        else if (input[i] == ' ' || input[i] == '\t' || input[i] == '\n')
            handle_whitespace(processed, &i, &j);
        else
            handle_regular_char(input, processed, &i, &j);
    }
    processed[j] = '\0';
    return processed;
}*/

char    *prepare_input(const char *input)
{
    size_t  len;
    size_t  i;
    size_t  j;
    char    *processed;

    len = ft_strlen(input);
    processed = malloc((len * 3) + 1);
    if (!processed)
        return (NULL);
    i = 0;
    j = 0;
    while (i < len)
    {
        if (input[i] == '|' && input[i + 1] == '|')
        {
            processed[j++] = ' ';
            processed[j++] = '|';
            processed[j++] = '|';
            processed[j++] = ' ';
            i += 2;
        }
        else if (input[i] == '&' && input[i + 1] == '&')
        {
            processed[j++] = ' ';
            processed[j++] = '&';
            processed[j++] = '&';
            processed[j++] = ' ';
            i += 2;
        }
        else if (input[i] == '<' && input[i + 1] == '<')
        {
            processed[j++] = ' ';
            processed[j++] = '<';
            processed[j++] = '<';
            processed[j++] = ' ';
            i += 2;
        }
        else if (input[i] == '>' && input[i + 1] == '>')
        {
            processed[j++] = ' ';
            processed[j++] = '>';
            processed[j++] = '>';
            processed[j++] = ' ';
            i += 2;
        }
        else if (input[i] == '|' || input[i] == '&' || input[i] == ';' || input[i] == '<' || input[i] == '>')
        {
            processed[j++] = ' ';
            processed[j++] = input[i];
            processed[j++] = ' ';
            i++;
        }
        else if (input[i] == ' ' || input[i] == '\t' || input[i] == '\n')
        {
            processed[j++] = ' ';
            i++;
        }
        else
        {
            processed[j++] = input[i];
            i++;
        }
    }
    processed[j] = '\0';
    return (processed);
}
