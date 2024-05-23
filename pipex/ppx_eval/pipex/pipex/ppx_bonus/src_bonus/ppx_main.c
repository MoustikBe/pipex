/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:36:16 by misaac-c          #+#    #+#             */
/*   Updated: 2024/05/18 20:47:03 by misaac-c         ###   ########.fr       */
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
	if (path == NULL)
		error();
	arguments = ft_split(argv[index], ' ');
	execve(path, arguments, NULL);
}

void	sub_process(t_pipex *ppx, pid_t pid, char **argv, char **envp)
{
	while (ppx->nb_cmd)
	{
		pid = fork();
		if (pid == -1)
			error();
		createprocessus(pid, ppx, argv, envp);
	}
}

void	ppx_bonus(int argc, char **argv, char **envp)
{
	t_pipex	*ppx;
	pid_t	pid;

	if (argc < 5)
		error();
	if (check_fd(argv[1]))
		error();
	ppx = malloc(sizeof(t_pipex));
	ppx->argc = argc;
	ppx->nb_cmd = argc - 5;
	ppx->index = 3;
	pipe(ppx->fd);
	pid = fork();
	if (pid == -1)
		error();
	step_1(pid, ppx, argv, envp);
	to_nb_cmd(ppx);
	sub_process(ppx, pid, argv, envp);
	from_nb_cmd(ppx);
	pid = fork();
	if (pid == -1)
		error();
	last_step(pid, ppx, argv, envp);
	close(ppx->fd_temp);
}

void	pipex(char **argv, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (check_fd(argv[1]))
		error();
	if (check_cmd(envp, argv, 2))
		error();
	pipe(fd);
	pid = fork();
	if (pid == 0)
		child_process(fd, argv, envp);
	else
		parent_process(fd, argv, envp);
}

int	main(int argc, char **argv, char **envp)
{
	if (envp == NULL || envp[0] == NULL || path_finder(envp) == 0)
		error();
	if (argc < 5)
		error();
	else if (argc > 5)
		ppx_bonus(argc, argv, envp);
	else if (argc == 5)
		pipex(argv, envp);
	return (0);
}
