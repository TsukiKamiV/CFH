#include "../minishell.h"

/**
 * @brief	Pwd builtin, affiche le répertoire courant
 * @return 0 dans tous les cas ?
 */
int	pwd_builtin(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (1);
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
