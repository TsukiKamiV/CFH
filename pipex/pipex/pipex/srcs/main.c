#include "../includes/pipex.h"

void	p_child(char **argv, char **envp, int *fd);
void	p_parent(char **argv, char **envp, int *fd);

int	main(int argc, char * argv[], char **envp)
{
	int		pipefd[2];
	pid_t	pid;
	
	if (argc == 5)
	{
		if (pipe(pipefd) == -1)
			ft_error();
		pid = fork();
		if (pid == -1)
			ft_error();
		if (pid == 0)
			p_child(argv, envp, pipefd);
		waitpid(pid, NULL, 0);
		p_parent(argv, envp, pipefd);
	}
	else
	{
		ft_putstr_fd("\033[31mError: Bad arguments\n\e[0m", 2);
		ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
	}
	return 0;
}


void	p_child(char **argv, char **envp, int *fd)
{
	int	fd_child;
	
	fd_child = open(argv[1], O_RDONLY);
	if (fd_child == -1)
		ft_error();
	dup2(fd[1], STDOUT_FILENO);
	dup2(fd_child, STDIN_FILENO);
	close(fd[0]);
	ft_execute(argv[2], envp);
}

void	p_parent(char **argv, char **envp, int *fd)
{
	int	fd_parent;
	
	fd_parent = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_parent == -1)
		ft_error();
	dup2(fd[0], STDIN_FILENO);
	dup2(fd_parent, STDOUT_FILENO);
	close(fd[1]);
	ft_execute(argv[3], envp);
}
