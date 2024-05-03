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