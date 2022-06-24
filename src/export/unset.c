#include "minishell.h"

extern t_mshell inf;

t_env	*ft_update_env_unset(t_env *lenv, t_env *lenv_tmp, size_t size)
{
    int i;
    void *tmp;

    i = 0;
    free_lenv(lenv);
    lenv = (t_env *)malloc(sizeof(t_env) * size);
    if (!lenv)
        exit_ms("error malloc", -1);
    tmp = lenv_tmp;
    while (lenv_tmp)
    {
        lenv[i].key = ft_strdup(lenv_tmp->key);
        lenv[i].val = ft_strdup(lenv_tmp->val);
        if (i > 0)
            lenv[i - 1].next = &lenv[i];
        lenv_tmp = lenv_tmp->next;
        i ++;
    }
    if (i > 0)
		lenv[i - 1].next = NULL;
    lenv_tmp = tmp;
    free_lenv(lenv_tmp);
    return (lenv);
}

t_env	*unset_env_list(t_env *lenv, int num, char **del)
{
    t_env *lenv_tmp;
    int i;
    void *tmp;
    void *tmp_two;

    i = 0;
    if (num == 1)
        return (NULL);
    tmp = lenv;
    while (lenv)
    {
        i ++;
        lenv = lenv->next;
    }
    lenv = tmp;
    lenv_tmp = (t_env *)malloc(sizeof(t_env) * i - (num - 1) + 1);
    if (!lenv_tmp)
        exit_ms("error malloc", -1);
    lenv_tmp = delete_env_unset(lenv, lenv_tmp, num, del);
    i = 0;
    tmp_two = lenv_tmp;
    while (lenv_tmp)
    {
        i ++;
        lenv_tmp = lenv_tmp->next;
    }
    lenv_tmp = tmp_two;
    return (ft_update_env_unset(lenv, lenv_tmp, i));
}

void error_print_unset(char *str, int i)
{
    if (str[i] == 45)
    {
        // ft_putstr_fd("minishell: unset: -",)
        // ft_putstr_fd("unset: использование: unset [-f] [-v] [-n] [имя ...]", 2);
        // ft_putchar_fd('\n', 2);
        // sig_hand(2);
        // exit (2);
        return ;
    }
	if (str[i] == 33 || str[i] == 59)
	{
		ft_putstr_fd("minishell: ", 2);
		while (str[i])
		{
			write(2, &str[i], 1);
			i ++;
		}
		ft_putstr_fd(": event not found\n", 2);
        // exit(127);
	}
	else
	{
        return ;
	}
}

int	check_pipes_cmd_unset(char *str)
{
	int i;

	i = 0;
	if (str[i] >= '0' && str[i] <= '9')
		return (1);
	while (str[i])
	{
		if ((check_key(str[i])) == 1)
		{
			error_print_unset(str, i);  //потом изменить!
			return (1);
		}
		i ++;
	}
	return (-1);
}

void unset_main(void)
{
	int i;

	i = 0;
	while (inf.pipes[0].cmd[i])
    {
        if (check_pipes_cmd_unset(inf.pipes[0].cmd[i]) == 1)
			return ;
        i ++;
    }
	if (i == 1)
        return ;
    inf.lenv = unset_env_list(inf.lenv, i, inf.pipes->cmd);
    if (!inf.lenv)
        return ;
    return ;
}

//gcc unset.c ../../includes/minishell.h ../../libft/ft_strlen.c ../../libft/ft_strdup.c ../../libft/ft_strncmp.c ../../src/env_list.c ../../libft/ft_strchr.c unset_utils.c