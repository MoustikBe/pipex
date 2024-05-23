# ifndef TEST_H
# define TEST_H
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <strings.h>
# include <sys/wait.h>

char	*get_next_line(int fd);

#endif