#include "get_next_line.h"

char    *get_next_line(int fd)
{
    static char *remainder;
    char    *new_line_ptr;
    char    *buffer;
    char    *ret;
    char    *current;
    //char    *set_me_free;
    ssize_t bytes_read;
    
    ret = NULL;
    while (fd >= 0)
    {
        buffer = (char *)calloc((BUFFER_SIZE + 1), sizeof(char));
        if (!buffer)
            return (NULL);
        if (!remainder || remainder[0] == '\0')
        {
            bytes_read = read(fd, buffer, BUFFER_SIZE);
            if (bytes_read  < 0)
            {
                free (ret);
                free (buffer);//leak
                return (NULL);
            }
            if (bytes_read == 0)
            {
                free (buffer);//leak
                return (ret);
            }
            current = ft_strdup(buffer); //alloc
            free (buffer);
            //buffer = NULL;//useless??
        }
        else
        {
            current = remainder; //此时两个PTR指向同一个内存地址， 还有用，所以不能free任何一个*
            remainder = NULL;
        }
        while (current && current[0] != '\0')
        {
            new_line_ptr = ft_strchr(current, '\n');//new_line_ptr与current指向的是同一内存区域
            if (new_line_ptr)//如果current中还有\n
            {
                *new_line_ptr = '\0';
                remainder = ft_strdup(new_line_ptr + 1);
                ret = add_to_line(ret, current);
                ret = add_to_line(ret, "\n");
                return (ret);
            }
            else//remainder中没有还需要剪裁的内容
            {
                ret = add_to_line(ret, current);
            }
            current = NULL;
        }
    }
    return (NULL);
}

char *add_to_line(char *dest, const char *src)
{
    //size_t  len;
    
    if (!dest)
    {
        dest = ft_strdup(src);
        return (dest);
    }
    else
    {
        //len = ft_strlen(dest) + ft_strlen(src);
        dest = ft_strjoin(dest, src);
        return (dest);
    }
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
