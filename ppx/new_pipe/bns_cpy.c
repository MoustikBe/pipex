#include "bns_ppx.h"


int	str_len(char *str)
{
	int count = 0;
	while(str[count++]);
	return(count - 1);
}


int main(int argc, char **argv, char **envp)
{
    pid_t	pid;
	pid_t	pid2; 
    int fd1[2], fd2[2];

    pipe(fd1);
    pipe(fd2);

	pid = fork();
	if(pid == 0)
	{
		// process enfant
		close(fd2[0]);
		close(fd2[1]);
		close(fd1[0]);
		dup2(fd1[1], STDOUT_FILENO);
		close(fd1[1]);
		char *argu[] = {"cat", "test.txt", NULL};
		execve("/bin/cat", argu, NULL);
	}
	else
	{
		pid2 = fork();
		if(pid2 == 0)
		{
			close(fd1[1]);
			dup2(fd1[0], STDIN_FILENO);
			close(fd1[0]);

			close(fd1[0]);
			dup2(fd2[1], STDOUT_FILENO);
			close(fd2[1]);

			// ICI ON PEUT METTRE EXEC CMD 
			char *argu[] = {"grep", "aw", NULL};
			execve("/bin/grep", argu, NULL);
		}
		else
		{
			// process parent 
			close(fd1[1]);
			close(fd1[0]);

			close(fd2[1]);
			dup2(fd2[0], STDIN_FILENO);
			close(fd2[0]);

			char *argu[] = {"wc", "-l", NULL};
			execve("/bin/wc", argu, NULL);
			// NE PAS OUBLIER QUE SI LE PROGRAMME EXECUTE LA FONCTION execve 
			// ON SORT DU PROG ACTUEL 
			// C'EST IMPORTANT DE FAIRE CETTE COMMANDE EN DERNIER 
			printf("\nFin de programme\n");
		}

	}
}