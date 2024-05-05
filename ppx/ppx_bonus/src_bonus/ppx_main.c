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

void createProcessus(int nb_cmd, int i, int fd[2], int fd2[2], 
char **argv, int index, char **envp)
{
	pid_t pid;

    pid = fork();
    if(pid == 0)
	{
		close(fd[1]);
		close(fd2[0]);
		dup2(fd[0], STDIN_FILENO);
		
		close(fd[0]);
		dup2(fd2[1], STDOUT_FILENO);
		close(fd2[1]);
		
		command_execution(envp, argv, index, argv[index]);
	}
	else
	{
		// Je call la recurciviter si jamais on a pas finis niveau commande
		if(i <  nb_cmd - 1)
		{
			i++;
			index++;
			printf("%d\n", i);
			createProcessus(nb_cmd, i, fd, fd2, argv, index, envp);
		}
	}
}

int main(int argc, char **argv, char **envp)
{
	int index = 3;
	int fd[2];
	int fd2[2];
	pid_t pid;
	int nb_cmd = argc - 5;

	pipe(fd);
	pipe(fd2);
	pid = fork();
	if(pid == 0)
	{
		// La premiere commande
		close(fd2[0]);
		close(fd2[1]);
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		char *argu[] = {"cat", "file/test.txt", NULL};
		execve("/bin/cat", argu, NULL);
	}
	else
	{
		pid =fork();
		if(pid == 0)
		{
			// Toutes les commandes intermediaires
			createProcessus(nb_cmd, 0, fd, fd2, argv, index, envp);
		}
		else
		{
			// parent_pross, derniere commande
			close(fd[1]);
			close(fd[0]);

			close(fd2[1]);
			dup2(fd2[0], STDIN_FILENO);
			close(fd2[0]);
			char *argu[] = {"cat", NULL};
			execve("/bin/cat", argu, NULL);
		}
	}

	return(0);
}




