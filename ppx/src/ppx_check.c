#include "../pipex.h"

void    error(void)
{
    write(1, "ERROR\n", 6);
    exit(1);
}

int check_fd(char *fd1)
{
	int fd; 

	fd = open(fd1, O_RDONLY);
	if(fd >= 0)
        return(0);
	else
		return(1);
}

int	check_cmd(char **envp, char **argv, int index)
{
	char **split_path;
    char *path;
    int id_path;

	while(index != 4)
	{
    	id_path = path_finder(envp);
    	split_path = ft_split(envp[id_path], ':');
    	path = locate_path(split_path, argv[index]);
    	if(path == NULL)
        {	
			return(1);
		}
		index++;
	}
	return(0);
}