
#include "minishell.h"
#include <termios.h>

void disable_echo(void)
{
	struct termios term;
	
	tcgetattr(STDIN_FILENO, &term);      // Get current terminal settings
	term.c_lflag &= ~(ECHO);            // Disable echo
	tcsetattr(STDIN_FILENO, TCSANOW, &term); // Apply changes immediately
}

void enable_echo(void)
{
	struct termios term;
	
	tcgetattr(STDIN_FILENO, &term);      // Get current terminal settings
	term.c_lflag |= ECHO;               // Enable echo
	tcsetattr(STDIN_FILENO, TCSANOW, &term); // Apply changes immediately
}

void	sig_handling(int signal_code)
{
	if (signal_code == SIGINT)
	{
		printf("Signal SIGINT (CTRL + C) detected. Exiting...\n");
		exit (0);
	}
	else if (signal_code == SIGQUIT)
	{
		printf("Signal SIGQUIT (CTRL + D) detected. Exiting...\n");
		exit (0);
	}
	else
		printf("Unknown signal\n");
}

struct sigaction	signal_launching(void)
{
	struct sigaction	sig_config;
	sigset_t	signal_set;
	
	sig_config.sa_flags = 0;
	sig_config.sa_handler = sig_handling;
	
	sigemptyset(&signal_set);
	sigaddset(&signal_set, SIGINT);
	sigaddset(&signal_set, SIGQUIT);
	sig_config.sa_mask = signal_set;
	return (sig_config);
};

int main(int argc, const char * argv[]) 
{
	t_shell_data *data = malloc(sizeof(t_shell_data));
	if (!data)
	{
		perror("Memory allocation failed");
		return (1);
	}
	//char	*user;
	//char	*prompt;
	//char	*line;
	struct sigaction	sig_config;
	
	disable_echo();
	sig_config = signal_launching();
	
	while (1)
	{
		data->username = getenv("USER");
		data->prompt = ft_strjoin(data->username, ">");
		data->line = readline(data->prompt);
		
		if (sigaction(SIGINT, &sig_config, NULL) == -1 || sigaction(SIGQUIT, &sig_config, NULL) == -1)
		{
			printf("Error when calling sigaction");
			return (1);
		}
		if (data->line)
			parse_line(&data);
		/*
		if (*line)
		{
			add_history(line);
		}*/		
		free (data->line);
	}
	//rl_clear_history();
	//enable_echo();
	return (0);
}
