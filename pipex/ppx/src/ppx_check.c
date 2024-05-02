#include "../pipex.h"

void    error(void)
{
    write(1, "ERROR\n", 6);
    exit(1);
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