#include "minishell.h"

bool	validate_quotes(const char *input)
{
	bool	single_quote;
	bool	double_quote;
	
	single_quote = false;
	double_quote = false;
	while (*input)
	{
		if (*input == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (*input == '\"' && !single_quote)
			double_quote = !double_quote;
		input++;
	}
	return !(single_quote || double_quote);
}
