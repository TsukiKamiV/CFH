#include "get_next_line.h"

#include <stdio.h>

int main(int argc, const char * argv[])
{
    int fd;
    int i;
    char *line;
    
    //delete this line before submit
    printf("BufferSize is: %d\n", BUFFER_SIZE);
    
    i = 1;
    fd = open("/Users/Luyao/CFH/get_next_line/get_next_line/test.txt", O_RDONLY);
    while (fd)
    {
        printf("get_next_line即将运行第%d次\n", i);
        line = get_next_line(fd);
        printf("结果是：%s\n\n", line);
        if (line == NULL)
        {
            close (fd);
            exit (0);
        }
        i++;
    }
    return (0);
}

char    *get_next_line(int fd)
{
    static char *remainder;
    char    *new_line_ptr;
    char    *buffer;
    char    *ret;
    char    *current;
    //char    *hou_set_me_free;
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
                /* //hou
                if (!new_line_ptr)
                    remainder = ft_strdup(new_line_ptr + 1); //将remainder更新为裁剪之后的字符串
                 */
                //tu
                remainder = ft_strdup(new_line_ptr + 1); //将remainder更新为裁剪之后的字符串
                
                //hou_set_me_free = ret;
                ret = add_to_line(ret, current);
                //free(hou_set_me_free);
                //free(current);
                
                //hou_set_me_free = ret;
                ret = add_to_line(ret, "\n");
                //free(hou_set_me_free);
                
                return (ret);
            }
            else//remainder中没有还需要剪裁的内容
            {
                //hou_set_me_free = ret;
                ret = add_to_line(ret, current);
                //if (hou_set_me_free)
                //    free (hou_set_me_free);
                //free(current);
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
