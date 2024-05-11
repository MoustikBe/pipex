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
    if(path == NULL)
        error() ;
    arguments = ft_split(str, ' ');
    execve(path, arguments, NULL);
}



void ppx_bonus(int argc, char **argv, char **envp)
{
    t_pipex *ppx;
    pid_t pid;

    if(argc < 5)
        error();
    if(check_fd(argv[1]))
        error();
    ppx = malloc(sizeof(t_pipex));
    ppx->nb_cmd = argc - 5;
    ppx->index = 3;
    pipe(ppx->fd);
    pid = fork();
    step_1(pid, ppx, argv, envp);
    to_nb_cmd(ppx);
    while(ppx->nb_cmd)
    {
        pid = fork();
        createProcessus(pid, ppx, argv, envp);
    }
    from_nb_cmd(ppx);
    pid = fork();
    last_step(pid, ppx, argv, envp, argc);
    close(ppx->fd_temp);
/*
    peut-être je vais devoir faire cette partie la
    DONC TOUCHE PAS POUR LE MOMENT
    waitpid(pid_a, NULL, 0);
    waitpid(pid_b, NULL, 0);
    waitpid(pid_c, NULL, 0);
    waitpid(pid_d, NULL, 0);
*/
}



void pipex(char **argv, char **envp)
{
    pid_t pid;
    int	fd[2];

    if(check_fd(argv[1]))
        error();
    if(check_cmd(envp, argv, 2))
        error();
    pipe(fd);
    pid = fork();
    if(pid == 0)
        child_process(fd, argv, envp);
    else
        parent_process(fd, argv, envp);
}

int main(int argc, char **argv, char **envp)
{
    if(argc < 5)
        error();
    else if(argc > 5)
        ppx_bonus(argc, argv, envp);
    else if(argc == 5)
    {
        pipex(argv, envp);
    }
        return(0);
}
