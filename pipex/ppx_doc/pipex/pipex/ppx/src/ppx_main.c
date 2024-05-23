/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:18:14 by misaac-c          #+#    #+#             */
/*   Updated: 2024/05/18 20:21:48 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	command_execution(char **envp, char **argv, int index)
{
	char	**split_path;
	char	**arguments;
	char	*path;
	int		id_path;

	id_path = path_finder(envp);
	split_path = ft_split(envp[id_path], ':');
	path = locate_path(split_path, argv[index]);
	arguments = ft_split(argv[index], ' ');
	execve(path, arguments, NULL);
}

void	child_process(int fd[2], char **argv, char **envp, char *title_file)
{
	int	fd_in;
	int fd_second = open("temp_file.txt", O_RDONLY); 

	fd_in = open(title_file, O_RDONLY);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	dup2(fd_in, STDIN_FILENO);
	dup2(fd[0], fd_in);
	close(fd[0]);
	if(fd_second)
	{	
		if (unlink("temp_file.txt") == 0) 
        	printf("Le fichier a été supprimé avec succès.\n");
		close(fd_second);
	}
	command_execution(envp, argv, 2);
}

void	parent_process(int fd[2], char **argv, char **envp)
{
	int	fileout;

	wait(0);
	close(fd[1]);
	fileout = open(argv[4], O_WRONLY);
	if (fileout == -1)
		fileout = open(argv[4], O_WRONLY | O_CREAT, 0777);
	dup2(fd[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	close(fileout);
	close(fd[0]);
	command_execution(envp, argv, 3);
}

void to_temp(char *line)
{
    int fileout;
    int i = 0;

    fileout = open("temp_file.txt", O_WRONLY | O_CREAT | O_APPEND, 0777);
    if (fileout == -1)
    {
        perror("open");
        return;
    }
    while (line[i])
    {
        write(fileout, &line[i], 1);
        i++;
    }
    close(fileout);
}
int comparaison(char *s1, char *s2, int flag)
{
    int i = 0;
    
    while(s1[i] == s2[i])
		i++;
	if(flag == 1 && i == ft_strlen(s2) + 1)
		return(1); 
    else if(flag == 0 && i == ft_strlen(s2) && s1[i - 1] == s2[i - 1])
		return(1);
    else 
        return(0);
}

int here_doc()
{
	char *line;
    char *cmp = "here_doc";

    while(1)
    {
        line = get_next_line(0);
        // CHECKER LES LIGNES //
        if(comparaison(line, cmp, 0) == 1)
            return(1);
		to_temp(line);
        free(line);
    }
	return(0);
}

void hered_process(char **argv, char **envp)
{
	pid_t	pid;
	int		fd[2];
	
	if (check_cmd(envp, argv, 2))
		error();
	pipe(fd);
	pid = fork();
	if (pid == -1)
		error();
	else if (pid == 0)
		child_process(fd, argv, envp, "temp_file.txt");
	else
		parent_process(fd, argv, envp);
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (comparaison(argv[1], "here_doc", 1))
	{
		if(here_doc())
			hered_process(argv, envp);
		exit(1);
	}
	if (argc != 5)
		error();
	if (check_fd(argv[1]))
		error();
	if (check_cmd(envp, argv, 2))
		error();
	pipe(fd);
	pid = fork();
	if (pid == -1)
		error();
	else if (pid == 0)
		child_process(fd, argv, envp, argv[1]);
	else
		parent_process(fd, argv, envp);
}
