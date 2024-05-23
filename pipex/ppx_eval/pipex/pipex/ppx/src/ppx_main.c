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

void	child_process(int fd[2], char **argv, char **envp)
{
	int	fd_in;

	fd_in = open(argv[1], O_RDONLY);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	dup2(fd_in, STDIN_FILENO);
	dup2(fd[0], fd_in);
	close(fd[0]);
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

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (envp == NULL || envp[0] == NULL || path_finder(envp) == 0)
		error();
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
		child_process(fd, argv, envp);
	else
		parent_process(fd, argv, envp);
}
