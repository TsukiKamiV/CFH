#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h> // sigaction and sigset_t
# include <stdbool.h>


// Représentation des tokens
typedef struct s_token
{
	char		*value; // (ls, |, >, -l, /home/)
	int		type; // (COMMAND, OPERATOR, ARGUMENT)
	struct s_token	*previous; // Pas forcément nécessaire ?
	struct s_token	*next;
}		t_token;

// Représentation de la table de commandes, elle représente une commande à exécuter
// ex : si l'utilisateur tape "ls -lRa /home/ | cat", on aura une table de commandes avec 2 éléments (ls -lRa /home/ et cat)
typedef struct s_command_table
{
	char	**parsed_command; // to be free, [ls, -lRa, /home/]
	t_token	*token_list;
	int		fd_in; // Par défaut 0 (stdin), à modifier si redirection
	int		fd_out; // Par défaut 1 (stdout), à modifier aussi
	bool	check_pipe; // Par défaut false, vérifie si la commande est suivie d'un pipe
	bool	check_redir; // Idem pour la redirection
	struct s_command_table	*next; // NULL si fin de la liste ou si une seule commande
}	t_command_table;



// Lucas ?
/* HANDLING */
// t_command_table *init_command_table(char **parsed_command);
// t_token *init_token_list(char **parsed_command);
// void add_token(t_token **head, t_token *new_token); // (pointeur vers un pointeur pour modifier l'adresse de l'indice 0 de la liste)
// void add_command_table(t_command_table **head, t_command_table *new_command);
// void free_command_table(t_command_table *head);
// void free_all_command_table(t_command_table **head);
// void free_token_list(t_token *head); // A appeler dans free_command_table ? // Pointeur vers le premier élément de la liste
// void free_all_token_list(t_token **head); // Pointeur vers le premier élément de la liste
// => Reste à créer une table/ pipe dans la commande. + voir ensuite le parser.
enum e_fd
{
	STDIN = 0,
	STDOUT = 1,
	STDERR = 2
};

enum e_token_type
{
	COMMAND,
	BUILTIN,
	ARGUMENT,
	SEPARATOR,
	OPERATOR,
	//STRING,?
	WHITESPACE,
	DEFAULT
};

// Debut d'une structure pour stocker nos donnees et gagner de la place
typedef struct	s_shell_data
{
	char	**env;
	char	*username;
	char	*hostname;
	char	*prompt;
	char	*line;
	char	**splitted_prev_command;
	int		exit_status;
	struct sigaction	sig_config;
	t_command_table	*command_table;
	t_token	*tokens;
	// rl history struct ?
}	t_shell_data;

// builtins/*.c
int	env_builtin(t_shell_data *shell_data);
int	pwd_builtin(void);
char	**modify_string_in_array(char **array, char *new_string, int index);
int	unset_builtin(t_shell_data *shell_data);

// data_handling/data_struct_utils.c
t_shell_data	*init_shell_data(char **env);
void	free_shell_data(t_shell_data *shell_data);
//expander for the command table (for later use 09012025)
void expand_tokens(t_command_table *cmd_table);// a faire
void handle_redirection(t_command_table *cmd, t_token *current);

// data_handling/cmd_table_manips.c
//l'ancien init_command_table ici
//t_command_table	*init_command_table(char **parsed_command);
t_command_table	*init_command_table(void);
void			create_command_table(t_shell_data *data);
t_token 		*init_token_list(t_token *start, t_token *end);
void			add_token(t_token **head, t_token *new_token); // DOUBLON_OK
void 			free_token_list(t_token *head);
void 			free_command_table(t_command_table **head);
int 			cmd_table_to_shell_data(t_shell_data *shell_data, char **parsed_command);
void			fill_command_table(t_shell_data *data);//called by parse_line to communicate the tokens and command tables

// general_utils/string_array_manips.c
void	free_string_array(char **array);
int		string_array_len(char **array);
char	**copy_string_array(char **array);
char	**add_string_to_array(char **array, char *new_string);
char	**remove_string_from_array(char **array, int index);

// mainloop_handling/minishell_mainloop.c
void	minishell_mainloop(t_shell_data *shell_data);

// signal_handling/signal_utils.c
void				sig_handling(int signal);
struct sigaction	signal_launching(void);

// exec_handling/builtins_exec.c
int	execute_builtin_command(t_shell_data *shell_data);
int	verify_simple_command(t_command_table *cmd, t_shell_data *shell_data);
int	exec_simple_command(t_command_table *cmd, t_shell_data *shell_data);

//exec_handling/builtins_exec.c
int	execute_builtin_command(t_shell_data *shell_data);

//exec_handling/exec_utils.c
char	**extract_and_split_env_path(char **env);
char	*cmd_is_accessible(char *cmd, char **path);

//token_handling/tokenize_input.c
void	set_bools_for_tokens(t_token *token);//set the booleans into the token structure, to be fusioned with double redir
char	**parse_commands(const char *input);
char	*prepare_input(const char *input);
void	parse_line(t_shell_data *data);
void	print_tab(char **tab); // A supprimer
int		ft_strcmp(const char *s1, const char *s2);
void free_tokens(t_token *tokens);

//token_handling/
bool check_double_pipe(char **parsed_command); // Vérifie si double pipe (ls || cat)
bool is_empty_cmd(char **parsed_command); // Vérifie si la commande est vide (ls | | ls ou cat "")
bool cmd_got_pipe(char **parsed_command); // Vérifie si la commande a un pipe (ls | cat)
bool cmd_got_redir(char **parsed_command); // >
bool check_double_redir(char **parsed_command); // >>
bool check_open_quote(char **parsed_command); // Vérifie si les quotes sont bien fermées (ls "cat ou ls cat')

//general_utils/error_exit.c
void	error_exit(t_shell_data *data, const char *msg, int status);
#endif
