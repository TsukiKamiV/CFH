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
*/
char	*cmd_is_accessible(char *cmd, char **path)
{
	char	*full_path;
	char	*tmp;
	int		i;

	if (!cmd)
		return (NULL);
	i = 0;
	if (cmd[0] == '/' || cmd[0] == '.') // Chemin absolu ou relatif (./ depuis usr ou bin)
	{
		// Si la commande est exactement "." ou "..", on la considère invalide (message géré dans l'exec)
		if (ft_strcmp(cmd, ".") == 0 || ft_strcmp(cmd, "..") == 0)
			return (NULL);
		if (access(cmd, F_OK | X_OK) == 0)
			return (printf("Commande valide: %s\n", cmd), ft_strdup(cmd)); ///// !!!!
		return (NULL);
	}
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

// Vérifier si une variable est dispo dans l'env du shell (utile pour vérifier si le PATH est dispo)
// 1 si oui, 0 sinon
//ATTENTION: s'il existe déjà une VAR qui s'appelle VAR_EXISTANT et je cherche VAR dans l'env, la fonction va retourner 1.
int	check_env_var(char *var, char **env)
{
	int	i;
	size_t	var_len;

	if (!var || !env)
		return (0);

	var_len = ft_strlen(var);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(var, env[i], var_len) == 0 && env[i][var_len] == '=')
			return (1);
		i++;
	}
	return (0);
}
