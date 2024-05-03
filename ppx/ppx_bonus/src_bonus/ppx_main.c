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
/*
void create_child(char **argv, char **envp, int index, int fd[2])
{
	pid_t pid;

	pid = fork();
	if(pid == 0)
	{
		sleep(5);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		command_execution(envp, argv, index, argv[index]);
	}
	else
	{
		close(fd[0]);
		wait(0);
	}
} 
*/

void    child_pross(int fd[2], char **argv, char **envp)
{
    char *argu_line;

    close(fd[0]);
    dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
    argu_line = ft_strjoin(argv[2], argv[1]);
	command_execution(envp, argv, 2, argu_line);
}

void    parent_process(int fd[2], char **argv, char **envp, int argc)
{
    int fileout;

	wait(0);
    close(fd[1]);
    fileout = open(argv[argc - 1], O_WRONLY);
    if (fileout == -1)
        fileout = open(argv[argc - 1], O_WRONLY | O_CREAT, 0777);
    dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
    dup2(fileout, STDOUT_FILENO);
	close(fileout);
	command_execution(envp, argv, argc - 2, argv[argc - 2]);
}

int main(int argc, char **argv, char **envp)
{
	int i;

	i = argc; 
	
	pid_t pid;
	int	fd[2];
	//int index;

	//if(argc != 5)
	//	error();
	if(check_fd(argv[1]))
        error();
	pipe(fd);
	pid = fork();
	if(pid == 0)
    {
		child_pross(fd, argv, envp);
	}	
	else
	{
		int fd2[2];
		pipe(fd2);
		pid = fork();
		if(pid == 0)
		{
			close(fd2[0]);
			
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);

			dup2(fd2[1], STDOUT_FILENO);
			close(fd2[1]);
			command_execution(envp, argv, 3, argv[3]);
		}
		
		else
			wait(0);
		parent_process(fd2, argv, envp, argc);
	}
}
