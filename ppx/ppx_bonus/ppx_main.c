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
/*
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
*/

int path_finder(char **map)
{
	int i; 
	int j;

	i = 0;
	while(map[i])
	{
		j = 0;
		if(map[i][j])
		{
			if(map[i][j] == 'P' && map[i][j + 1] == 'A' && map[i][j + 2] == 'T' && map[i][j + 3] == 'H')
				return(i);
			else
				j++;
		}
		i++;
	}
    return(0);
}


char	*suite_join(char *s1, char *s2,
						char *new_char, int len1)
{
	int	count;

	count = 0;
	if (s1 && s2)
	{
		while (s1[count] != '\0')
		{
			new_char[count] = s1[count];
			count++;
		}
        new_char[len1++] = ' ';
		count = 0;
		while (s2[count] != '\0')
		{
			new_char[len1] = s2[count];
			count++;
			len1++;
		}
		new_char[len1] = '\0';
		return (new_char);
	}
	return (new_char);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		len1;
	int		len2;
	char	*new_char;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new_char = malloc((len1 + len2 + 1) * sizeof(char));
	if (new_char == NULL)
		return (NULL);
	suite_join(s1, s2, new_char, len1);
	return (new_char);
}

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

int size_flag(char *str, int j)
{
	int i;

	i = 0;
	while(str[j])
	{
		i++;
		j++;
	}
	return(i);
}

char *make_path(char *split_path, char *cmd)
{
	int i;
	int j;
	char *path;

	i = 0; 
	path = malloc(ft_strlen(split_path) + ft_strlen(cmd + 1) + 1 * sizeof(char));
	if(!path)
		return(NULL);
	while(split_path[i])
	{
		path[i] = split_path[i];
		i++;
	}
	path[i] = '/';
	i++;
	j = 0; 
	while(cmd[j] && cmd[j] != ' ')
	{
		path[i] = cmd[j];
		i++;
		j++;
	}
	path[i] = '\0';
	return(path);
}
char *locate_path(char **split_path, char *cmd)
{
	int i; 
	int flag_acss; 
	char *path; 

	i = 0;
	while(split_path[i])
	{
		path = make_path(split_path[i], cmd);
		//printf("path -> %s\n", path);
		flag_acss = access(path, O_RDONLY);
		if(flag_acss == 0)
			return(path);
		else
		{
			//free(path);
			i++;
		}
	}
	return(NULL);
}

int main(int argc, char **argv, char **envp)
{
    char **split_path;
    char *path;
    int id_path;
	pid_t pid;
	int	index;
	int	fd[2];

	//if(argc != 5)
	//	return(printf("Problemes de nb d'arguments\n"));
    if(check_fd(argv[1], argv[argc - 1]))
		return(printf("Problemes de fd\n"));
	printf("%d\n", argc);
    /*
    pipe(fd);
	pid = fork();
	if(pid == 0)
	{
		id_path = path_finder(envp);
		split_path = ft_split(envp[id_path], ':');
		path = locate_path(split_path, argv[2]);
		if(path == NULL)
			return(printf("ERREUR, pas de chemin trouver\n"));
        close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
        char *argu_line;
        argu_line = ft_strjoin(argv[2], argv[1]);
        char **arguments = ft_split(argu_line, ' ');
		execve(path, arguments, NULL);
	}
	else
	{
		wait(0);
		close(fd[1]);
        int fileout;
        fileout = open(argv[4], O_WRONLY);
        if (fileout == -1)
            return (1);
        dup2(fd[0], STDIN_FILENO);
        dup2(fileout, STDOUT_FILENO);
		id_path = path_finder(envp);
		split_path = ft_split(envp[id_path], ':');
		path = locate_path(split_path, argv[3]);
		if(path == NULL)
			return(printf("ERREUR, pas de chemin trouver\n"));
        char **arguments_wc = ft_split(argv[3], ' ');
        execve(path, arguments_wc, NULL);
		//system("leaks a.out");
	}
	 */
}
/*
	int BUFFER_SIZE = 5;
	char *buffer;
	char *full_line = malloc(sizeof(char));
	int nb = 1;
	while(nb > 0)
	{
		buffer = malloc(sizeof(char) * BUFFER_SIZE);
		nb = read(fd[0], buffer, 5);	
		buffer[nb] = '\0';
		full_line = ft_strjoin(full_line, buffer);
		free(buffer);
	}
	//printf("%s\n", full_line);
*/