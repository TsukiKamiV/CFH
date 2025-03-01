#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h> // sigaction and sigset_t
# include <stdbool.h>
# include <sys/wait.h> // waitpid, WIFEXITED
# include <sys/stat.h>
#include <sys/ioctl.h> //ioctl, FIONREAD

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define RESET "\033[0m"

# define PARSER_BUFFER_SIZE 1024
# define HEREDOC_BUFFER_SIZE 1024

// Potentiellement pour en ajouter une liste dans
// exec_simple_command (exec_handling/command_exec.c) ou exec_all_commands (exec_handling/command_exec.c pas encore créé)
// typedef struct s_redirection
// {
// 	int		type; // 0: "<", 1: ">", 2: ">>", 3: "<<"
// 	char	*filename; // Nom du fichier concerné
// 	int		fd;	// Descripteur de fichier (après ouverture)
// char		*heredoc_delimiter;
//} t_redirection;

typedef enum	e_quote_state //Pour mieux gérer les mixted quotes dans les tokens
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}	t_quote_state;

// Représentation des tokens
typedef struct s_token
{
	char	*value; // (ls, |, >, -l, /home/)
	int		type; // (COMMAND, OPERATOR, ARGUMENT)
	enum	e_quote_state	quote_state;
	struct	s_token	*previous; // Pas forcément nécessaire ?
	struct	s_token	*next;
}				t_token;

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
	PIPE,
	REDIR,
	WHITESPACE,
	DEFAULT
};

/*
	- Codes de retour standards :stan
		0 : Succès de l'exécution.
		1 : Erreur générale (utilisé pour des erreurs génériques).
		2 : Mauvaise utilisation de la commande (erreur de syntaxe).

	- Codes de retour liés aux fichiers et permissions :
		126 : Commande trouvée mais non exécutable (problème de permission).
		127 : Commande introuvable (exécutable non trouvé dans $PATH).
		128 : Erreur liée à l'utilisation incorrecte des codes de retour (exemple : exit 256 revient à exit 0 car seuls les 8 bits de poids faible sont pris en compte (à creuser)).

	- Codes de retour liés aux signaux :
		Lorsque le processus est terminé par un signal, Bash retourne 128 + numéro du signal :

		130 (128 + SIGINT) : Terminé par un Ctrl + C (SIGINT).
		137 (128 + SIGKILL) : Terminé par un kill -9 (SIGKILL).
		143 (128 + SIGTERM) : Terminé par kill ou kill -15 (SIGTERM).
		Codes de retour liés à wait et exec :
		255 : Erreur de sortie (valeur non autorisée par exit, car seules les valeurs entre 0 et 255 sont valides).
*/


// Debut d'une structure pour stocker nos donnees et gagner de la place
typedef struct	s_shell_data
{
	char	**env;
	char	**exported_vars;
	char	*username;
	char	*hostname;
	char	*prompt;
	char	*line;
	char	**splitted_prev_command;
	int		exit_status;
	char	*shell_name;
	struct sigaction	sig_config;
	t_command_table	*command_table;
	t_token	*tokens;
	char	pid_str[20];//used to retreive the current PID by stat expansion $$
	bool is_interactive; // Ne pas appeler readline si non interactif !
	// rl history struct ?
}	t_shell_data;

typedef struct	s_tokenizer
{
	const char		*line;
	const char		*start;
	t_quote_state	q_state;
	char			buffer[PARSER_BUFFER_SIZE];
	int				buf_i;
	t_token			*prev;
	t_shell_data	*data;
}				t_tokenizer;

// builtins/*.c
int	env_builtin(t_shell_data *shell_data);
int	pwd_builtin(t_shell_data *shell_data);
char	**modify_string_in_array(char **array, char *new_string, int index);
int	unset_builtin(t_shell_data *shell_data);
int	echo_builtin(t_shell_data *data);
int	export_builtin(t_shell_data *data);
//builtins/export_utils.c
char **modify_string_in_array(char **array, char *new_string, int index);
char	*ft_strndup(const char *src, size_t n);
void sort_char_array(char **array);
char *extract_key(const char *env_entry);
int get_env_index(char **env, const char *key);
//builtins/export_utils_2.c
int is_var_in_list(char **list, const char *key);
char **remove_var_from_list(char **list, const char *key);
void count_env_and_exported_vars(t_shell_data *data, int *env_size, int *export_size);
void fill_sorted_exports_env(char **sorted_exports, t_shell_data *data, int env_size);
void fill_sorted_exports_exported(char **sorted_exports, t_shell_data *data, \
								  int env_size, int export_size);
//builtins/export_utils_3.c
void print_sorted_exports(char **sorted_exports, int fd_out);
int		is_valid_identifier(const char *str);
//builtins/exit.c
int	exit_builtin(t_shell_data *shell_data);
//builtins/cd.c
int	cd_builtin(t_shell_data *data);
//builtins/cd_utils.c
char	*ft_strjoin_3(const char *s1, const char *s2, const char *s3);
int	update_env_entry(char ***env, const char *var, const char *new_entry, size_t var_len);
void	append_env_entry(char ***env, const char *new_entry, int i);
void	set_env_value(char ***env, const char *var, const char *value);
//builtins/cd.c
int	cd_builtin(t_shell_data *data);
int	cd_change_dir(t_shell_data *data, char *dir);
char	*get_cd_dir(t_shell_data *data);

// data_handling/data_struct_utils.c
t_shell_data	*init_shell_data(char **env);
void			free_shell_data(t_shell_data *shell_data);
//expander for the command table (for later use 09012025)
//void 	expand_tokens(t_command_table *cmd_table);// a faire
char			*get_env_value(const char *var, char **envp);

//data_handling/redir_and_heredoc.c
//void			handle_heredoc(const char *delim);
int 			handle_redirection(t_command_table *cmd, t_token *current);

// data_handling/cmd_table_manips.c
//t_command_table	*init_command_table(char **parsed_command);
t_command_table	*init_command_table(void);
void			create_command_table(t_shell_data *data);
t_token 		*init_token_list(t_token *start, t_token *end);
void			add_token(t_token **head, t_token *new_token); // DOUBLON_OK
void 			free_token_list(t_token *head);
void 			free_command_table(t_command_table **head);
//int 			cmd_table_to_shell_data(t_shell_data *shell_data, char **parsed_command);
void			fill_command_table(t_shell_data *data);//called by parse_line to communicate the tokens and command tables
//t_token			*parse_tokens_into_command_table(t_command_table *cmd, t_token *current, t_shell_data *data);
//t_token	*tokens_into_cmd_annex(t_command_table *cmd, t_token *current, int *i, t_shell_data *data);

//data_handling/data_struct_expander.c
char	*remove_surrounding_quotes(char *str);
void	expand_variables(char **str, t_shell_data *data);
void	expand_cmd_token(t_token *tokens, t_shell_data *data);

//data_handling/expander_utils.c
char	*handle_exit_status(char *res, t_shell_data *data);
char	*append_str(char *res, const char *str);
char	*append_substr(char *res, const char *src, size_t begin, size_t len);
char	*handle_env_var(char *res, const char *var_name, t_shell_data *data);
char	*perform_expansion(const char *str, t_shell_data *data);

//data_handling/perform_expansion_annexe.c
char	*extract_var_name(const char *str, size_t *start);
char	*expand_variable(char *res, const char *str, size_t *i, t_shell_data *data);
void	get_shell_pid(t_shell_data *data);

// general_utils/string_array_manips.c
void	free_string_array(char **array);
int		string_array_len(char **array);
char	**copy_string_array(char **array);
char	**add_string_to_array(char **array, char *new_string);
char	**remove_string_from_array(char **array, int index);

// mainloop_handling/minishell_mainloop.c
int	minishell_mainloop(t_shell_data *shell_data);

// signal_handling/signal_utils.c
void	sig_handling(int signal);
struct sigaction	signal_launching(void);
void	restore_signals_in_parent(struct sigaction *old_sigint, struct sigaction *old_sigquit);
void	ignore_signals_in_parent(struct sigaction *old_sigint, struct sigaction *old_sigquit);
void	heredoc_sig_handler(int sig);

// exec_handling/builtins_exec.c
int	execute_simple_builtin_command(t_shell_data *shell_data);

//exec_handling/system_exec.c
int	execute_system_command(t_command_table *cmd, t_shell_data *shell_data);

// exec_handling/piped_command_handling.c
int	execute_piped_commands(t_command_table *cmd, t_shell_data *shell_data);

// exec_handling/simple_command_handling.c
char	*verify_simple_command(t_command_table *cmd, t_shell_data *shell_data);
int	execute_simple_child(t_command_table *cmd, t_shell_data *shell_data, char *correct_cmd_path);

// exec_handling/command_exec.c
int	exec_simple_command(t_command_table *cmd, t_shell_data *shell_data);


// //exec_handling/builtins_exec.c
// int	execute_builtin_command(t_shell_data *shell_data);

//exec_handling/exec_utils.c
char	**extract_and_split_env_path(char **env);
char	*cmd_is_accessible(char *cmd, char **path);
int		check_env_var(char *var, char **env);

//token_handling/parse_utiles.c
void	parse_operator(t_tokenizer *t);
void	toggle_quote_state(t_quote_state *q_state, char c);
bool	handle_quote_or_operator(t_tokenizer *t);

//token_handling/token_utiles.c
t_token	*create_token(const char *value, int type, t_quote_state q_state);
void	add_token(t_token **head, t_token *new_token);
int		ft_strcmp(const char *s1, const char *s2);
int		determine_token_type(const char *value, const t_token *previous_token);
void	finalize_token(t_tokenizer *t);

//token_handling/tokenize_input.c
//char	**parse_commands(const char *input);
//char	*prepare_input(const char *input);
void	parse_line(t_shell_data *data);
void	print_tab(char **tab); // A supprimer

//token_handling/parse_bools_1.c
bool check_double_pipe(char **parsed_command); // Vérifie si double pipe (ls || cat)
bool is_empty_cmd(char **parsed_command); // Vérifie si la commande est vide (ls | | ls ou cat "")
bool cmd_got_pipe(char **parsed_command); // Vérifie si la commande a un pipe (ls | cat)
//bool cmd_got_redir(char **parsed_command); // >
//bool check_double_redir(char **parsed_command); // >>

//token_handling/parse_bools_2.c
//bool 	check_open_quote(char **parsed_command); // Vérifie si les quotes sont bien fermées (ls "cat ou ls cat')
//bool	is_surrounded_by_quotes(const char *str, char quote); //Vérifie si string commence et se termine par quotes
int 	is_whitespace(char c);
bool	validate_quotes(const char *input);
bool	is_line_empty_or_whitespace(const char *line);

//token_handling/token_determin_bools.c
bool	is_builtin(const char *value);
bool	is_separator(const char *value);
bool	is_operator(const char *value);
//bool 	is_argument(const char *value);
bool	is_pipe(const char *value);
bool	is_redirection(const char *value);

//general_utils/error_exit.c
void	error_exit(t_shell_data *data, const char *msg, int status);
void	set_error(t_shell_data *data, const char *msg, int status);
#endif
