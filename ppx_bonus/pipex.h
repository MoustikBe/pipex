#ifndef PIPEX_H
# define PIPEX_H
// -- LIBRARY -- //
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <strings.h>
# include <sys/wait.h>
typedef struct pipex
{
    int fd[2];
    int fd_temp;
    int nb_cmd;
    int index;
}   t_pipex;

// -- LIBRARY -- //
// -- FUNCTION -- //
char	**ft_split(char const *s, char c);
int		ft_strlen(const char *str);
char	*ft_strjoin(char *s1, char *s2);
// PATH PARSING //
int		path_finder(char **map);
char	*locate_path(char **split_path, char *cmd);
// TCHECK //
void    error(void);
int		check_fd(char *fd1);
int     check_cmd(char **envp, char **argv, int index);
// PROCESS //
void createProcessus(pid_t pid, t_pipex *ppx, char **argv, char **envp);
void step_1(pid_t pid, t_pipex *ppx, char **argv, char **envp);
void last_step(pid_t pid, t_pipex *ppx, char **argv, char **envp, int argc);
// FD PART //
void to_nb_cmd(t_pipex *ppx);
void from_nb_cmd(t_pipex *ppx);
// BASIC PPX //
void    child_process(int fd[2], char **argv, char **envp);
void    parent_process(int fd[2], char **argv, char **envp);
// IMPORTANT //
void	command_execution(char **envp, char **argv, int index, char *str);
// -- FUNCTION -- //
#endif