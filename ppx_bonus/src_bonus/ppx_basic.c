#include "../pipex.h"

void    child_process(int fd[2], char **argv, char **envp)
{
    int fd_in;

    fd_in = open(argv[1], O_RDONLY);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);
    dup2(fd_in, STDIN_FILENO);
    dup2(fd[0], fd_in);
    close(fd[0]);
    command_execution(envp, argv, 2, argv[2]);
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