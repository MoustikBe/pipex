#include "../pipex.h"

void	command_execution(char **envp, char **argv, int index, char *str)
{
    char **split_path;
    char **arguments;
    char *path;
    int id_path;

    id_path = path_finder(envp);
    split_path = ft_split(envp[id_path], ':');
    path = locate_path(split_path, argv[index]);
    arguments = ft_split(str, ' ');
    execve(path, arguments, NULL);
}

void    chield_pross(int fd[2], char **argv, char **envp)
{
    char *line;

    line = ft_strjoin(argv[2], argv[1]);
    close(fd[0]);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);
    command_execution(envp, argv, 2, line);
}

void    parent_process(int fd[2], char **argv, char **envp)
{
    int fileout;

    wait(0);
    close(fd[1]);
    fileout = open(argv[4], O_WRONLY);
    if (fileout == -1)
        fileout = open(argv[4], O_WRONLY | O_CREAT, 0777);
    dup2(fd[0], STDIN_FILENO);
    dup2(fileout, STDOUT_FILENO);
    close(fileout);
    close(fd[0]);
    command_execution(envp, argv, 3, argv[3]);
}

int main(int argc, char **argv, char **envp)
{
	pid_t pid;
	int	fd[2];

	if(argc != 5)
		error();
	if(check_fd(argv[1]))
        error();
    if(check_cmd(envp, argv, 2))
        error();
    pipe(fd);
	pid = fork();
	if(pid == 0)
        chield_pross(fd, argv, envp);
	else
        parent_process(fd, argv, envp);
}
