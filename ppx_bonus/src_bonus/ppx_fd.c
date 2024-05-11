#include "../pipex.h"

void to_nb_cmd(t_pipex *ppx)
{
    close(ppx->fd[1]);
    ppx->fd_temp = ppx->fd[0];
    pipe(ppx->fd);
}

void from_nb_cmd(t_pipex *ppx)
{
    close(ppx->fd_temp);
    close(ppx->fd[1]);
    ppx->fd_temp = ppx->fd[0];
}