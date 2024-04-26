#include "pipex.h"



// file1 cmd1 cmd2 file2 

// file1 = le fichier 
// dans lequel on va chercher le contenus, il peut contenir n'importe quoi 

// cmd1 = il s'agit de la premiere commande 
// elle va interagire sur le contenus du fichier1 et le sotcker quelques part

// cmd2 =  Il s'agit de la seconde commande 
// elle va interagir sur le contenus stocker apres l'intervention de cmd1 
// et stocker le resultat sur fichier2 

// file2 = stocke le resultat du contenus apres le passage de cmd1 puis de cmd2 

// On va devoir séparer le programme dans le but que les commandes ne s'appliquent 
// pas au deux en même temps, c'est pour cela que l'on utilise fork, pipe, etc... 


int	ft_strlen(char *str)
{
	int count;

	count = 0;
	while(str[count])
		count++;
	return(count);
}

char 	*memory_mngt(char **argv, int nb)
{
	char *str;
	int i = 0; 
	str = malloc(sizeof (char) * ft_strlen(argv[nb]));
	if(!str)
		// IL FAUT FREE -> free(ppx);
		return(NULL);
	while(argv[nb][i])
	{
		str[i] = argv[nb][i];
		i++;
	}
	return(str);
}


//int main(int argc, char **argv)
//{
	/*
	int fd; 
	int fd2; 
	t_pipex	*ppx;

	ppx = malloc(sizeof(t_pipex));
	if(ppx == NULL)
		return(1);
	ppx->file1 = memory_mngt(argv, 1);
	ppx->file2 = memory_mngt(argv, 2);
	ppx->cmd1 = memory_mngt(argv, 3);
	ppx->cmd2 = memory_mngt(argv, 4);
	printf("file1 -> %s\n", ppx->file1);
	printf("file2 -> %s\n", ppx->file2);
	printf("cmd1 -> %s\n", ppx->cmd1);
	printf("cmd2 -> %s\n", ppx->cmd2);
	
	fd = open(ppx->file1, O_RDONLY);
	fd2 = open(ppx->file2, O_RDONLY);
	printf("%d\n", fd);
	printf("%d\n", fd2);
	if(fd < 0 || fd2 < 0)
	{
		printf("Mauvais fichier\n");
		return(1);
	}
	*/

	/* create the pipe */

/*   char buffer[BUFSIZ+1];
 
	t_pipex	*ppx;

	ppx = malloc(sizeof(t_pipex));
	if(ppx == NULL)
		return(1);
	ppx->file1 = memory_mngt(argv, 1);
	ppx->file2 = memory_mngt(argv, 4);
	ppx->cmd1 = memory_mngt(argv, 2);
	ppx->cmd2 = memory_mngt(argv, 3);
	pipe(fd);
	fd[0] = open(ppx->file1, O_RDONLY);
	fd[1] = open(ppx->file2, O_WRONLY);
	printf("fd -> %d\n", fd[0]); 
	printf("fd -> %d\n", fd[1]);
	 write into the pipe 
//	write(fd[1], "Hello World\n", strlen("Hello World\n"));
	 read the pipe and print the read value 
	//read(fd[0], buffer, BUFSIZ);
	//printf("%s", buffer);*/
/*
	int fd[2];
	pid_t pid;
	int *status;
	char *newargv[] = { NULL, "hello", "world", NULL };
	
	int nb = 42;

	if(pipe(&fd[2]) == -1)
		return(0);
	pid = fork();
	if(pid == -1)
		return(printf("problemes pour fork\n"));
	if(pid == 0)
	{	
		close(fd[1]);
		printf("Fils : Initialisation du pogramme enfant\n");
		printf("Fils : La valeur que j'ai est -> %d\n", nb);
		printf("Fils : Fin du programme\n");
		exit(0);
	}
	else
	{	
		close(fd[0]);
		printf("Père : Initialisation du pere\n");
		printf("Père : La valeur que j'ai est -> %d\n", nb);
		wait(NULL);
		printf("Pére : mais la vrais valeur est -> %d\n", nb*2);
		//execve(argv[1], argv + 1, NULL);
	}
	return(0);
}
*/
/*
void	writestr(int fd, const char *str)
{
	write(fd, str, strlen(str));
}

//	Main
int	main(void)
{
	int	pipefd[2];  // Stocke les fd du pipe :
			    //  - pipefd[0] : lecture seule
			    //  - pipefd[1] : écriture seule
	pid_t	pid;	// Stocke le retour de fork
	char	buf;	// Stocke la lecture de read

//	Crée un pipe. En cas d'échec on arrête tout
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
//	Crée un processus fils
	pid = fork();
	if (pid == -1) // Echec, on arrête tout
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0) // Processus fils
	{
	//	Ferme le bout d'écriture inutilisé
		close(pipefd[1]);
		writestr(STDOUT_FILENO, "Fils : Quel est le secret dans ce pipe ?\n");
		writestr(STDOUT_FILENO, "Fils : \"");
	//	Lit les caractères dans le pipe un à un
		int fd = open("test.txt", O_WRONLY);
		while (read(pipefd[0], &buf, 1) > 0)
		{
			// Écrit le caractère lu dans la sortie standard
			write(fd, &buf, 1);
		}
		writestr(STDOUT_FILENO, "\"\n");
		writestr(STDOUT_FILENO, "Fils : Ohlala ! Je vais voir mon pere.\n");
	//	Ferme le bout de lecture
		close(pipefd[0]);
		exit(EXIT_SUCCESS);
	}
	else	// Processus père
	{
	//	Ferme le bout de lecture inutilisé
		close(pipefd[0]);
		writestr(STDOUT_FILENO, "Pere : J'ecris un secret dans le pipe...\n");
	//	Écrit dans le bout d'écriture du pipe
		writestr(pipefd[1], "Eiwa draré!");
	//	Ferme le bout d'ecriture (lecteur verra EOF)
		close(pipefd[1]);
	//	Attend la terminaison du fils
		wait(NULL);
		writestr(STDOUT_FILENO, "Pere : Salut mon fils !\n");
		exit(EXIT_SUCCESS);
	}
*/
int check_fd(char *fd1, char *fd2)
{
	int fd; 

	fd = open(fd1, O_RDONLY);
	if(fd >= 0)
	{	
		fd = open(fd2, O_RDONLY);
		if(fd >= 0)
			return(0);
		else
			return(1);	
	}
	else
		return(1);
	
}
int main(int argc, char **argv, char **envp)
{
	pid_t pid;
	int	index;
	int	fd[2];

	//if(argc != 5)
	//	return(printf("Problemes de nb d'arguments\n"));
	//if(check_fd(argv[1], argv[4]))
	//	return(printf("Problemes de fd\n"));
	printf("Tous les test sont correctes\n");
	pipe(&fd[2]);
	pid = fork();
	if(pid == 0)
	{
		int BUFFER_SIZE = 10;
		char *buffer = malloc(BUFFER_SIZE + 1 * sizeof(char));
		dup2(fd[0], STDOUT_FILENO);
		close(fd[1]);
		read(fd[0], buffer, BUFFER_SIZE);
		printf("BUFFER -> %s\n", buffer);
		printf("process child\n");
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], STDIN_FILENO);
		char *path = "/bin/cat";
		char *arguments[] = {argv[2], argv[3], NULL};
		printf("process parent\n");
		execve(path, arguments, NULL);
		wait(NULL);
		return(0);
	}
}


