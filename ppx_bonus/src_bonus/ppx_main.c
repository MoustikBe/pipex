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

void createProcessus(pid_t pid, t_pipex *ppx)
{
	if(pid == 0)
	{
		close(ppx->fd[0]);
		dup2(ppx->fd_temp, STDIN_FILENO);
		dup2(ppx->fd[1], STDOUT_FILENO);
		close(ppx->fd_temp);
		close(ppx->fd[1]);
		char *argu[] = {"grep", "ef", NULL};
		execve("/bin/grep", argu, NULL);
	}
	close(ppx->fd_temp);
	close(ppx->fd[1]);
	ppx->fd_temp = ppx->fd[0];
	pipe(ppx->fd);
}


int main(void)
{	
	t_pipex *ppx;
	pid_t pid;

	ppx = malloc(sizeof(t_pipex)); 
	pipe(ppx->fd);
	pid = fork();
	// PREMIERE FOIS // 
	if(pid == 0)
	{
		close(ppx->fd[0]);
		dup2(ppx->fd[1], STDOUT_FILENO);
		close(ppx->fd[1]);
		char *argu[] = {"cat", "test.txt", NULL};
		execve("/bin/cat", argu, NULL);
	}
	// SAUVEGARDE DES DONNES // 
	close(ppx->fd[1]);
	ppx->fd_temp = ppx->fd[0];
	pipe(ppx->fd);
	pid = fork();
	// DEUXIEME FOIS // 
	// PARTIE A EXECUTER ENTRE CHAQUE INTER-PROCESS //
	createProcessus(pid, ppx);
	// SAUVEGARDE DES DONNEES // 
	// DOIT ETRE EXECUTER A CHAQUE FOIS ENTRE CHAQUE INTER-PROCESS, LE MÊME MORCEAU DE CODE //  
	/*close(ppx->fd_temp);
	close(ppx->fd[1]);
	ppx->fd_temp = ppx->fd[0];
	pipe(ppx->fd);*/
	pid = fork();
	// TROISIEME FOIS // 
	if(pid == 0)
	{
		close(ppx->fd[0]);
		dup2(ppx->fd_temp, STDIN_FILENO);
		dup2(ppx->fd[1], STDOUT_FILENO);
		close(ppx->fd_temp);
		close(ppx->fd[1]);
		char *argu[] = {"grep", "i", NULL};
		execve("/bin/grep", argu, NULL);
	}
	// PARTIE A EXECUTER ENTRE CHAQUE INTER-PROCESS //
	// SAUVEGARDE DES DONNEES // 
	close(ppx->fd_temp);
	close(ppx->fd[1]);
	ppx->fd_temp = ppx->fd[0];
	pid = fork();
	// QUATRIEME FOIS // 
	if(pid == 0)
	{
		dup2(ppx->fd_temp, STDIN_FILENO);
		close(ppx->fd_temp);
		char *argu[] = {"wc", "-l", NULL};
		execve("/bin/wc", argu, NULL);
	}
    close(ppx->fd_temp);
/*
    waitpid(pid_a, NULL, 0);
    waitpid(pid_b, NULL, 0);
    waitpid(pid_c, NULL, 0);
    waitpid(pid_d, NULL, 0);
*/



	return(0);
}




