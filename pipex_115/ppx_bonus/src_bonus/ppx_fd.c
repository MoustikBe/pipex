/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:35:43 by misaac-c          #+#    #+#             */
/*   Updated: 2024/05/18 20:36:04 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	to_nb_cmd(t_pipex *ppx)
{
	close(ppx->fd[1]);
	ppx->fd_temp = ppx->fd[0];
	pipe(ppx->fd);
}

void	from_nb_cmd(t_pipex *ppx)
{
	close(ppx->fd_temp);
	close(ppx->fd[1]);
	ppx->fd_temp = ppx->fd[0];
}
