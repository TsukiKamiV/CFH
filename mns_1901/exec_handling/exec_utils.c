#include "../minishell.h"


/**
	@brief Retourne un tableau de strings contenant a chaque index un des path contenant des commandes
	@return NULL si PATH ou l'environnement ne sont pas trouves, le tableau si tout se passe comme prevu
*/
char	**extract_and_split_env_path(char **env)
{
	int		i;
	char	*path_env_path;
	char	**splitted_env_path;

	i = 0;
	if (!env || !*env)
		return (NULL);
	splitted_env_path = NULL;
	path_env_path = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path_env_path = env[i] + 5;
			break ;
		}
		i++;
		if (!env[i])
			return (NULL);
	}
	splitted_env_path = ft_split(path_env_path, ':');
	if (!splitted_env_path)
		return (NULL);
	return (splitted_env_path);
}
/**
	@brief Tente d'acceder a chaque chemin present dans PATH et verifie si la commande entree est presente et executable
	@return le chemin complet de la commande si elle est presente et executable, NULL sinon
	@warning Ne gere pas les chemins absolus !!!
*/
char	*cmd_is_accessible(char *cmd, char **path)
{
	char	*full_path;
	char	*tmp;
	int		i;

	if (!cmd)
		return (NULL);
	i = 0;
	while (path && path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}


