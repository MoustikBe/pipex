#ifndef PIPEX_H
# define PIPEX_H
// -- STRUCT -- //
typedef struct pipex
{
	char *file1;
	char *file2;
	char *cmd1;
	char *flag;
	char *cmd2;
}	t_pipex;
// -- STRUCT -- // 
// -- LIBRARY -- //
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <strings.h>
# include <sys/wait.h>

// -- LIBRARY -- //
// -- FUNCTION -- //
char	**ft_split(char const *s, char c);
// -- FUNCTION -- //
#endif