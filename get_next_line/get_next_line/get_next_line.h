//
//  get_next_line.h
//  get_next_line
//
//  Created by XU Luyao on 2024/6/17.
//  Copyright © 2024年 XU Luyao. All rights reserved.
//

#ifndef get_next_line_h
# define get_next_line_h

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>

char    *get_next_line(int fd);
size_t  ft_strlen(const char *s);
size_t  ft_strlcat(char *dest, const char *src, size_t size);
void    *ft_calloc(size_t nmemb, size_t size);
char    *add_to_line(char *dest, const char *src);
char    *find_residue(char *buffer);
char    *ft_strdup(const char *s);
char    *ft_strchr(const char *s, int c);
char    *ft_strjoin(const char *s1, const char *s2);
size_t  ft_strlcpy(char *dest, const char *src, size_t size);

#endif
