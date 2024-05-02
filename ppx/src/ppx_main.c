#include "../pipex.h"
 

void    chield_pross(int fd[2], char **argv, char **envp)
{
    char **split_path;
    char **arguments;
    char *argu_line;
    char *path;
    int id_path;

    id_path = path_finder(envp);
    split_path = ft_split(envp[id_path], ':');
    path = locate_path(split_path, argv[2]);
    if(path == NULL)
        error() ;
    close(fd[0]);
    dup2(fd[1], STDOUT_FILENO);
    argu_line = ft_strjoin(argv[2], argv[1]);
    arguments = ft_split(argu_line, ' ');
    execve(path, arguments, NULL);
}

void    parent_process(int fd[2], char **argv, char **envp)
{
    char **split_path;
    char **arguments_wc;
    char *path;
    int id_path;
    int fileout;

    wait(0);
    close(fd[1]);
    fileout = open(argv[4], O_WRONLY);
    if (fileout == -1)
        fileout = open(argv[4], O_WRONLY | O_CREAT, 0777);
    dup2(fd[0], STDIN_FILENO);
    dup2(fileout, STDOUT_FILENO);
    id_path = path_finder(envp);
    split_path = ft_split(envp[id_path], ':');
    path = locate_path(split_path, argv[3]);
    if(path == NULL)
        error() ;
    arguments_wc = ft_split(argv[3], ' ');
    execve(path, arguments_wc, NULL);
}

int main(int argc, char **argv, char **envp)
{
	pid_t pid;
	int	fd[2];

	if(argc != 5)
		error();
	if(check_fd(argv[1]))
        error();
	pipe(fd);
	pid = fork();
	if(pid == 0)
        chield_pross(fd, argv, envp);
	else
        parent_process(fd, argv, envp);
}
