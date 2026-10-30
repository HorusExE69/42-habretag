#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

int		line_length(char *stash);
int		rest_length(char *stash);
char	*ft_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);

#endif