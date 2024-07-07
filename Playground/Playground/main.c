#include "get_next_line.h"

#include <stdio.h>
#include "common.h"

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
        free (line);
        if (line == NULL)
        {
            close (fd);
            exit (0);
        }
        i++;
    }
    return (0);
}

/*
//把get_next_line函数拆分成三大块：
 1、  当ret里没有\n，从file中读取新的内容；buff[bytes_read] = '\0' => 手动把读取到的内容保护为字符串；将ret和buffer贴起来
 2、  找出（或写入）new_line，并返回；
 3、  更新remainder
*/

/*没写完的，可能用不上
char *read_and_join(int fd, char *temp_ret)//名字不易读，待定
{
    char    *ret;
    char    *buffer;
    ssize_t bytes_read;
    
    buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
    if (!buffer)
        return (NULL);
    bytes_read = 1;
    while ((!ft_strchr(buffer, '\n')) && bytes_read != 0)
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read <= 0)
        {
            free (buffer);
            return (NULL);
        }
        
    }
    if (fd < 0)
}*/


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
        //printf("  开始大循环\n");
        if (!remainder || remainder[0] == '\0')
        {
            buffer = (char *)ft_calloc((BUFFER_SIZE + 1), sizeof(char));//malloc_1
            if (!buffer)
            {
                free (buffer);
                return (NULL);
            }
            bytes_read = read(fd, buffer, BUFFER_SIZE);
            if (bytes_read  < 0)
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
            //printf("<-- %s\n", buffer);
            current = ft_strdup(buffer); //malloc_2 (not freed)
            if (!current)
                free (current);
            free (buffer);//free_1
            //buffer = NULL;//useless??
        }
        else
        {
            current = remainder; //此时两个PTR指向同一个内存地址， 还有用，所以不能free任何一个*
            remainder = NULL;
        }
        while (current && current[0] != '\0')
        {
            //printf("    开始小循环\n");
            new_line_ptr = ft_strchr(current, '\n');//new_line_ptr与current指向的是同一内存区域
            if (new_line_ptr)//如果current中还有\n
            {
                *new_line_ptr = '\0';
                /* //hou
                 if (!new_line_ptr)
                 remainder = ft_strdup(new_line_ptr + 1); //将remainder更新为裁剪之后的字符串
                 */
                //tu
                
                if (BUFFER_SIZE != 1 || current[0] == '\n') {
                    remainder = ft_strdup(new_line_ptr + 1); //malloc_3 (not freed) => 地址总是与malloc_1地址一样？并且size为malloc_1 (size - 1)
                    if (remainder && remainder[0] == '\0') {
                        free (remainder);
                        remainder = NULL;
                    }
                    
                }
                ret = add(ret, current);
                ret = addbr(ret);
                
                return (ret);
            }
            else//remainder中没有还需要剪裁的内容
            {
                ret = add(ret, current);
            }
            current = NULL;
        }
    }
    return (NULL);
}


//A可以为NULL， B必不为NULL, 返回值必不为空
char *add(char *a, char *b)
{
    //size_t  len;
    char *temp;
    
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

char *addbr(char *a)
{
    //size_t  len;
    char *temp;
    
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
