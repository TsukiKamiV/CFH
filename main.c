#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Define token structure
typedef struct s_token {
	char *value;
	int type;
	struct s_token *previous;
	struct s_token *next;
} t_token;

// Token types
enum e_token_type {
	COMMAND,
	BUILTIN,
	ARGUMENT,
	SEPARATOR,
	OPERATOR,
	WHITESPACE,
	STRING
};

// Utility: Free a string array
void free_string_array(char **array) {
	if (!array) return;
	for (int i = 0; array[i]; i++) {
		free(array[i]);
	}
	free(array);
}

// Utility: Duplicate a string with a maximum length
char *ft_strndup(const char *s, size_t n) {
	char *str = malloc(n + 1);
	if (!str) return NULL;
	strncpy(str, s, n);
	str[n] = '\0';
	return str;
}

// Utility: Split a string by a delimiter
char **ft_split(const char *s, char c) {
	int i = 0, j, k = 0;
	char **tab = malloc(sizeof(char *) * (strlen(s) + 1)); // Overallocate for simplicity
	if (!tab) return NULL;
	
	while (s[i]) {
		while (s[i] == c) i++;
		j = i;
		while (s[i] && s[i] != c) i++;
		if (i > j) {
			tab[k++] = ft_strndup(s + j, i - j);
		}
	}
	tab[k] = NULL;
	return tab;
}

// Determine if a token is a built-in command
bool is_builtin(const char *value) {
	return (!strcmp(value, "cd") || !strcmp(value, "echo") || !strcmp(value, "exit") ||
			!strcmp(value, "pwd") || !strcmp(value, "export") || !strcmp(value, "unset") ||
			!strcmp(value, "env"));
}

// Determine if a token is an operator
bool is_operator(const char *value) {
	return (!strcmp(value, "|") || !strcmp(value, ">") || !strcmp(value, ">>") ||
			!strcmp(value, "<") || !strcmp(value, "<<"));
}

// Determine if a token is a separator
bool is_separator(const char *value) {
	return (!strcmp(value, ";") || !strcmp(value, "&&") || !strcmp(value, "||"));
}

/*
bool is_same_str(const char *__s1, const char *__s2) {
	return strcmp(__s1, __s2) == 0;
}
*/

// Determine if a token is an argument
bool is_argument(const char *value) {
	return value[0] != '\0' && value[0] != '-' && !is_operator(value) && !is_separator(value);
}

// Determine token type
int determine_token_type(const char *value, const t_token *previous_token) {
	if (is_separator(value)) return SEPARATOR;
	if (is_operator(value)) return OPERATOR;
	if (is_builtin(value)) return BUILTIN;
	
	// First token or after separator -> Command
	if (!previous_token || previous_token->type == SEPARATOR || (previous_token->type == OPERATOR && (strcmp(previous_token->value, ">") && strcmp(previous_token->value, ">>") && strcmp(previous_token->value, "<") && strcmp(previous_token->value, "<<"))))
		return COMMAND;
	
	// Default -> Argument
	return ARGUMENT;
}

// Create a new token
t_token *create_token(const char *value, int type) {
	t_token *new_token = malloc(sizeof(t_token));
	if (!new_token) return NULL;
	new_token->value = strdup(value);
	new_token->type = type;
	new_token->previous = NULL;
	new_token->next = NULL;
	return new_token;
}

// Add a token to the linked list
void add_token(t_token **head, t_token *new_token) {
	if (!*head) {
		*head = new_token;
	} else {
		t_token *temp = *head;
		while (temp->next) temp = temp->next;
		temp->next = new_token;
		new_token->previous = temp;
	}
}

// Free all tokens
void free_tokens(t_token *tokens) {
	while (tokens) {
		t_token *temp = tokens;
		tokens = tokens->next;
		free(temp->value);
		free(temp);
	}
}

// Tokenize input string
t_token *tokenize(const char *input) {
	char **tab = ft_split(input, ' ');
	if (!tab) return NULL;
	
	t_token *token_list = NULL;
	t_token *previous = NULL;
	
	for (int i = 0; tab[i]; i++) {
		int type = determine_token_type(tab[i], previous);
		t_token *new_token = create_token(tab[i], type);
		if (!new_token) {
			free_string_array(tab);
			free_tokens(token_list);
			return NULL;
		}
		add_token(&token_list, new_token);
		previous = new_token;
	}
	
	free_string_array(tab);
	return token_list;
}

// Print tokens
void print_tokens(t_token *token_list) 
{
	const char *token_types[] =
	{
		"COMMAND", 
		"BUILTIN",
		"ARGUMENT",
		"SEPARATOR",
		"OPERATOR",
		"WHITESPACE",
		"STRING"
	};
	while (token_list) {
		printf("Value: '%s', Type: %s\n",
			   token_list->value,
			   token_types[token_list->type]);
		token_list = token_list->next;
	}
}

// Main function
int main(void)
{
	const char *input = "ls -R | cat -e > output.txt";
	t_token *tokens = tokenize(input);
	
	if (tokens) {
		print_tokens(tokens);
		free_tokens(tokens);
	} else {
		printf("Error: Failed to tokenize input\n");
	}
	return 0;
}
