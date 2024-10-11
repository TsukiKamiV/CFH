#ifndef PIPEX_H
#define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../libft/libft.h"

void	ft_error(void);
void	ft_execute(char *argv, char **envp);

#endif /* pipex_h */
