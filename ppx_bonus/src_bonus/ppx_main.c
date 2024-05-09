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

//void createProcessus()
//{
//
//}


int main(void)
{
	int fd[2];
	int fd_temp = STDIN_FILENO;
	pid_t pid;

	
	pipe(fd);
	pid = fork();
	// PREMIERE FOIS // 
	if(pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		char *argu[] = {"cat", "test.txt", NULL};
		execve("/bin/cat", argu, NULL);
	}
	// SAUVEGARDE DES DONNES // 
	close(fd[1]);
	fd_temp = fd[0];
	pipe(fd);
	pid = fork();
	// DEUXIEME FOIS // 
	// PARTIE A EXECUTER ENTRE CHAQUE INTER-PROCESS //
	if(pid == 0)
	{
		close(fd[0]);
		dup2(fd_temp, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd_temp);
		close(fd[1]);
		char *argu[] = {"grep", "ef", NULL};
		execve("/bin/grep", argu, NULL);
	}
	// SAUVEGARDE DES DONNEES // 
	// DOIT ETRE EXECUTER A CHAQUE FOIS ENTRE CHAQUE INTER-PROCESS, LE MÊME MORCEAU DE CODE //  
	close(fd_temp);
	close(fd[1]);
	fd_temp = fd[0];
	pipe(fd);
	pid = fork();
	// TROISIEME FOIS // 
	if(pid == 0)
	{
		close(fd[0]);
		dup2(fd_temp, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd_temp);
		close(fd[1]);
		char *argu[] = {"grep", "i", NULL};
		execve("/bin/grep", argu, NULL);
	}
	// PARTIE A EXECUTER ENTRE CHAQUE INTER-PROCESS //
	// SAUVEGARDE DES DONNEES // 
	close(fd_temp);
	close(fd[1]);
	fd_temp = fd[0];
	pid = fork();
	// QUATRIEME FOIS // 
	if(pid == 0)
	{
		dup2(fd_temp, STDIN_FILENO);
		close(fd_temp);
		char *argu[] = {"wc", "-l", NULL};
		execve("/bin/wc", argu, NULL);
	}
    close(fd_temp);
/*
    waitpid(pid_a, NULL, 0);
    waitpid(pid_b, NULL, 0);
    waitpid(pid_c, NULL, 0);
    waitpid(pid_d, NULL, 0);
*/



	return(0);
}




