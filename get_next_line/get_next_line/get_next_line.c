#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*new_line_ptr;
	char		*buffer;
	char		*ret;
	char		*current;
	ssize_t		bytes_read;

	ret = NULL;
	while (fd >= 0)
	{
		if (!remainder || remainder[0] == '\0')
		{
			buffer = (char *)ft_calloc((BUFFER_SIZE + 1), sizeof(char));
			if (!buffer)
			{
				free (buffer);
				return (NULL);
			}
			bytes_read = read(fd, buffer, BUFFER_SIZE);
			if (bytes_read < 0)
			{
				free (ret);
				free (buffer);
				return (NULL);
			}
			if (bytes_read == 0)
			{
				free (buffer);
				return (ret);
			}
			current = ft_strdup(buffer);
			if (!current)
				free (current);
			free (buffer);
		}
		else
		{
			current = remainder;
			remainder = NULL;
		}
		while (current && current[0] != '\0')
		{
			new_line_ptr = ft_strchr(current, '\n');
			if (new_line_ptr)
			{
				*new_line_ptr = '\0';
				if (BUFFER_SIZE != 1 || current[0] == '\n')
				{
					remainder = ft_strdup(new_line_ptr + 1);
					if (remainder && remainder[0] == '\0')
					{
						free (remainder);
						remainder = NULL;
					}
				}
				ret = add(ret, current);
				ret = add_break(ret);
				return (ret);
			}
			else
			{
				ret = add(ret, current);
			}
			current = NULL;
		}
	}
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
