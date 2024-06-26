/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:13:52 by misaac-c          #+#    #+#             */
/*   Updated: 2024/05/18 20:14:26 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
// -- LIBRARY -- //
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <strings.h>
# include <sys/wait.h>
// -- LIBRARY -- //
// -- FUNCTION -- //
char	**ft_split(char const *s, char c);
int		ft_strlen(const char *str);
char	*ft_strjoin(char *s1, char *s2);
// PATH PARSING //
int		path_finder(char **map);
char	*locate_path(char **split_path, char *cmd);
// TCHECK //
void	error(void);
int		check_fd(char *fd1);
int		check_cmd(char **envp, char **argv, int index);
// -- FUNCTION -- //
#endif