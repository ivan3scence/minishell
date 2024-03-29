/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_managment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:58:59 by sdonny            #+#    #+#             */
/*   Updated: 2022/06/11 15:36:27 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

extern t_mshell	g_inf;

void	*free_fd(int **fd)
{
	int	i;

	i = -1;
	if (fd)
	{
		while (++i <= (g_inf.mask >> 16))
		{
			if (fd[i])
				free(fd[i]);
		}
		free(fd);
		fd = NULL;
	}
	return (NULL);
}

void	exitmalloc(int **fd)
{
	perror("malloc rip");
	fd = free_fd(fd);
	ft_putendl_fd("pipex gone mad", 2);
	exit(43);
}

void	exitpipex(int **fd, char *desc)
{
	perror(desc);
	fd = free_fd(fd);
	free(g_inf.pids);
	g_inf.pids = NULL;
	free_pipes(g_inf.pipes);
	exit(127);
}

void	free_list(t_wldcrd *list)
{
	t_wldcrd	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp);
	}
}
