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


int main(int argc, char **argv)
{
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
	printf("tout est carré\n");
	return(0);
}