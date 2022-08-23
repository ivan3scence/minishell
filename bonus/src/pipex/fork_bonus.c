/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:59:08 by sdonny            #+#    #+#             */
/*   Updated: 2022/06/11 15:20:12 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

extern t_mshell	g_inf;

static pid_t	*createpids(int **fd)
{
	pid_t	*pid;
	int		i;

	i = -1;
	pid = (pid_t *)malloc(sizeof(pid_t) * (g_inf.mask >> 16));
	if (!pid)
		exitmalloc(fd);
	while (++i < (g_inf.mask >> 16))
		pid[i] = 0;
	g_inf.pids = pid;
	return (pid);
}

int	str_len(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		;
	return (i);
}

static void	update_env(void)
{
	t_env	*lenv;
	char	**new;

	if (((g_inf.mask >> 3) & 1) == 0)
		return ;
	g_inf.env = free_env(g_inf.env);
	lenv = g_inf.lenv;
	new = (char **)malloc(sizeof(char *) * list_len(lenv));
	if (!new)
		exit_ms("malloc rip!", EXIT_ERROR);
	g_inf.env = new;
	while (lenv)
	{
		*new = ft_strjoin(lenv->key, lenv->val);
		if (!*new)
			exit_ms("malloc rip!", EXIT_ERROR);
		++new;
		lenv = lenv->next;
	}
	*new = NULL;
}

int	child(int **fd, t_pipes *pipes, int index)
{
	char	**cmd;
	int		exit_status;

	child_fd(index, fd);
	exit_status = check_func(pipes, 0, index);
	if (exit_status != 256)
		exit(0);
	update_env();
	cmd = cmdparse(pipes->cmd, g_inf.env, fd);
	if (!cmd[0])
		exitpipex(fd, PERROR": bin not found");
	if (execve(cmd[0], cmd, g_inf.env) == -1)
		exitpipex(fd, cmd[0]);
	killchild(cmd, fd);
	return (1);
}

pid_t	*forks(int **fd)
{
	int		m;
	pid_t	*pid;
	t_pipes	*pipes;

	m = -1;
	pipes = g_inf.pipes;
	pid = createpids(fd);
	while (pipes)
	{
		pid[++m] = fork();
		if (pid[m] < 0)
			exitpipex(fd, "fork");
		else if (!pid[m] && !ft_strncmp(pipes->cmd[0], "exit", 5))
		{
			ft_putstr_fd("\b\b\b\b\b\b\b\b\b\b\b\b", 1);
			exit(0);
		}
		else if (!pid[m])
			child(fd, pipes, m);
		check_func(pipes, 1, m);
		pipes = pipes->next;
	}
	return (pid);
}
