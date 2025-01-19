#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct s_token 
{
    char            *value;
    int             type;
    struct s_token  *previous;
    struct s_token  *next;
} t_token;

typedef struct s_command_table 
{
    char            **parsed_command;
    int             fd_in;
    int             fd_out;
    bool            check_pipe;
    bool            check_redir;
    struct s_command_table *next;
} t_command_table;

typedef struct s_shell_data 
{
    char            *line;
    t_token         *tokens;
    t_command_table *command_table;
} t_shell_data;

enum e_token_type 
{
    COMMAND,
    ARGUMENT,
    OPERATOR,
    WHITESPACE,
    REDIRECTION
};

// Constants for redirection
enum e_fd 
{
    STDIN = 0,
    STDOUT = 1,
    STDERR = 2
};

t_token *create_token(const char *value, int type) 
{
    t_token *new_token = malloc(sizeof(t_token));
    if (!new_token) return NULL;
    new_token->value = strdup(value);
    new_token->type = type;
    new_token->previous = NULL;
    new_token->next = NULL;
    return new_token;
}

t_command_table *create_command_table(void) 
{
    t_command_table *new_command = malloc(sizeof(t_command_table));
    if (!new_command) return NULL;
    new_command->parsed_command = NULL;
    new_command->fd_in = STDIN;
    new_command->fd_out = STDOUT;
    new_command->check_pipe = false;
    new_command->check_redir = false;
    new_command->next = NULL;
    return new_command;
}

int determine_token_type(const char *value, const t_token *previous) 
{
    if (strcmp(value, "|") == 0)
        return OPERATOR;
    if (strcmp(value, ">") == 0 || strcmp(value, ">>") == 0 || strcmp(value, "<") == 0 || strcmp(value, "<<") == 0)
        return REDIRECTION;
    if (!previous || previous->type == OPERATOR)
        return COMMAND;
    return ARGUMENT;
}

void add_token(t_token **head, t_token *new_token) 
{
    if (!*head) 
	{
        *head = new_token;
        return;
    }
    t_token *temp = *head;
    while (temp->next)
        temp = temp->next;
    temp->next = new_token;
    new_token->previous = temp;
}

void tokenize(t_shell_data *data) 
{
    char *token;
    char *input = strdup(data->line);
    t_token *previous = NULL;

    token = strtok(input, " ");
    while (token) 
	{
        int type = determine_token_type(token, previous);
        t_token *new_token = create_token(token, type);
        if (!new_token) 
		{
            free(input);
            return;
        }
        add_token(&data->tokens, new_token);
        previous = new_token;
        token = strtok(NULL, " ");
    }
    free(input);
}

t_token *parse_tokens_into_command_table(t_command_table *cmd, t_token *current) 
{
    int i = 0;

    cmd->parsed_command = malloc(sizeof(char *) * 256);
    if (!cmd->parsed_command) return NULL;

    while (current) 
	{
        if (current->type == OPERATOR && strcmp(current->value, "|") == 0) 
		{
            cmd->check_pipe = true;
            return current->next;
        } 
		else if (current->type == REDIRECTION) 
		{
            cmd->check_redir = true;
            current = current->next; // Skip redirection target
        } else 
		{
            cmd->parsed_command[i++] = strdup(current->value);
        }
        current = current->next;
    }

    cmd->parsed_command[i] = NULL;
    return NULL;
}

void populate_command_table(t_shell_data *data) 
{
    t_token *current = data->tokens;
    t_command_table *last_cmd = NULL;

    while (current) 
	{
        t_command_table *new_cmd = create_command_table();
        if (!new_cmd) return;

        current = parse_tokens_into_command_table(new_cmd, current);

        if (!data->command_table)
            data->command_table = new_cmd;
        else
            last_cmd->next = new_cmd;

        last_cmd = new_cmd;
    }
}

void print_command_table(t_command_table *cmd_table) 
{
    int cmd_num = 1;
    while (cmd_table) {
        printf("Command %d:\n", cmd_num++);
        for (int i = 0; cmd_table->parsed_command[i]; i++) 
		{
            printf("  Arg[%d]: %s\n", i, cmd_table->parsed_command[i]);
        }
        printf("  Pipe: %s\n", cmd_table->check_pipe ? "Yes" : "No");
        printf("  Redirection: %s\n", cmd_table->check_redir ? "Yes" : "No");
        cmd_table = cmd_table->next;
    }
}

int main(void) 
{
    t_shell_data data;
    data.line = NULL;
    data.tokens = NULL;
    data.command_table = NULL;

    printf("Enter a command line: ");
    size_t len = 0;
    getline(&data.line, &len, stdin);

    // Remove trailing newline
    data.line[strcspn(data.line, "\n")] = '\0';

    tokenize(&data);                  // Step 1: Tokenize input
    populate_command_table(&data);    // Step 2: Parse tokens into command tables

    print_command_table(data.command_table); // Step 3: Print command tables
    return 0;
}
