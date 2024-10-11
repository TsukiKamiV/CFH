//#include "get_next_line.h"
# include "libft.h"

char	*get_next_line(int fd)
{
	static char	*remainder;
    /*char        *new_line_ptr;*/
	char		*ret;
	char		*current;

	ret = NULL;
    
	while (fd >= 0)
	{
        current = gimme_current(fd, &remainder, &ret);
        remainder = NULL;
        if (current == NULL) {
            return ret;
        }
        current = process_current(&current, &ret, &remainder);
        if (current)
            return (current);
	}
	return (NULL);
}

char    *gimme_current(int fd, char **remainder, char **ret_to_free)
{
    char        *buffer;
    ssize_t     bytes_read;
    
    if (!*remainder || *remainder[0] == '\0')
    {
        /*如果calloc可以换成malloc,安全地， 就又省了一个function配额*/
        buffer = (char *)ft_calloc((BUFFER_SIZE + 1), sizeof(char));
        if (!buffer)
            return (NULL);
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read <= 0)
        {
            if (bytes_read < 0 && ret_to_free)
            {
                free(*ret_to_free);
                *ret_to_free = NULL;
            }
            free (buffer);
            return (NULL);
        }
        *remainder = ft_strdup(buffer);
        free (buffer);
    }
    return (*remainder);
}

char    *process_current(char **current, char **ret, char **remainder_to_fill)
{
    char        *new_line_ptr;
    
    new_line_ptr = ft_strchr(*current, '\n');
    if (new_line_ptr)
    {
        *new_line_ptr = '\0';
        if (BUFFER_SIZE != 1 || *current[0] == '\n')
        {
            *remainder_to_fill = ft_strdup(new_line_ptr + 1);
            if (*remainder_to_fill && *remainder_to_fill[0] == '\0')
            {
                free (*remainder_to_fill);
                *remainder_to_fill = NULL;
            }
        }
        *ret = add(*ret, *current);
        *ret = add_break(*ret);
        return (*ret);
    }
    else
        *ret = add(*ret, *current);
    return (NULL);
}

char	*add(char *a, char *b)
{
	char	*temp;

	if (!a)
	{
		temp = ft_strdup(b);
	}
	else
	{
		temp = ft_strjoin(a, b);
		free(a);
	}
	free(b);
	return (temp);
}

char	*add_break(char *a)
{
	char	*temp;

	if (!a)
	{
		temp = "\n";
	}
	else
	{
		temp = ft_strjoin(a, "\n");
		free(a);
	}
	return (temp);
}

/*char *get_next_line(int fd)
 {
 ssize_t bytes_read;
 char *buffer;
 char *ret = NULL;
 //static char *remainder;
 size_t i;
 
 buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
 if (!buffer)
 return (NULL);
 while (fd)
 {
 bytes_read = read(fd, buffer, BUFFER_SIZE);
 if (bytes_read <= 0)
 return (NULL);
 i = 0;
 while (buffer[i] && i < bytes_read)
 {
 if (buffer[i] == '\n')
 {
 ret = add_to_line(ret, "\n");
 return (ret);
 //break;
 }
 else
 i++;
 }
 ret = add_to_line(ret, buffer);
 }
 return (ret);
 }*/
