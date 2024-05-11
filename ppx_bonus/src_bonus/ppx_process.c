#include "../pipex.h"

void createProcessus(pid_t pid, t_pipex *ppx, char **argv, char **envp)
{
    if(pid == 0)
    {
        close(ppx->fd[0]);
        dup2(ppx->fd_temp, STDIN_FILENO);
        dup2(ppx->fd[1], STDOUT_FILENO);
        close(ppx->fd_temp);
        close(ppx->fd[1]);
        command_execution(envp, argv, ppx->index);
    }
    if(ppx->nb_cmd > 1)
    {
        close(ppx->fd_temp);
        close(ppx->fd[1]);
        ppx->fd_temp = ppx->fd[0];
        pipe(ppx->fd);
    }
    ppx->nb_cmd--;
    ppx->index++;
}

void step_1(pid_t pid, t_pipex *ppx, char **argv, char **envp)
{
    if(pid == 0)
    {
        int fd_in;

        fd_in = open(argv[1], O_RDONLY);
        dup2(ppx->fd[1], STDOUT_FILENO);
        close(ppx->fd[1]);
        dup2(fd_in, STDIN_FILENO);
        dup2(ppx->fd[0], fd_in);
        close(ppx->fd[0]);
        command_execution(envp, argv, 2);
    }
}

void last_step(pid_t pid, t_pipex *ppx, char **argv, char **envp, int argc)
{
    if(pid == 0)
    {
        int fileout;
        fileout = open(argv[argc - 1], O_WRONLY);
        if (fileout == -1)
            fileout = open(argv[argc - 1], O_WRONLY | O_CREAT, 0777);
        dup2(ppx->fd_temp, STDIN_FILENO);
        close(ppx->fd_temp);
        dup2(fileout, STDOUT_FILENO);
        close(fileout);
        command_execution(envp, argv, argc-2);
    }
}
