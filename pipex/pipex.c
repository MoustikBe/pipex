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
int main(int argc, char **argv)
{
	pid_t pid;

	if(argc	!= 5)
		return(printf("Problemes de nb d'arguments\n"));
	if(check_fd(argv[1], argv[4]))
		return(printf("Problemes de fd\n"));
	printf("Tous les test sont correctes\n");

	pid = fork();
	if(pid == 0)
	{
		printf("process child\n");
	}
	else
	{
		wait(NULL);
		printf("process parent\n");
	}
}