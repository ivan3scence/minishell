#include "minishell.h"

extern t_mshell inf;

void    del_unset(t_env *prev)
{
    t_env *lenv;

    lenv = prev->next;
    prev->next = lenv->next;
    free(lenv->key);
    free(lenv->val);
    free(lenv);
}

void    unset_env_list(t_env *lenv, char **del)
{
    int i;
    void *tmp;

    i = 0;
    while (del[i])
    {
        if (!ft_strncmp(inf.lenv->key, del[i], ft_strlen(inf.lenv->key)))
        {
            tmp = inf.lenv->next;
            free(inf.lenv->key);
            free(inf.lenv->val);
            free(inf.lenv);
            inf.lenv = tmp;
        }
        ++i;
    }
    tmp = NULL;
    while (lenv)
    {
        i = 0;
        while (del[i])
        {
            if (!ft_strncmp(lenv->key, del[i], ft_strlen(lenv->key)))
            {
                lenv = lenv->next;
                del_unset(tmp);
            }
            i ++;
        }
        tmp = lenv;
        if (lenv)
            lenv = lenv->next;
    }
}

void error_print_unset(char *str, int i)
{
    if (str[i] == 45)
    {
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
	}
	else
        return ;
}

int	check_pipes_cmd_unset(char *str)
{
	int i;

	i = -1;
	if (str[0] >= '0' && str[0] <= '9')
		return (1);
    while (str[++ i])
    {
        if (str[i] == 59)
            return (127);
    }
    i = 0;
	while (str[i])
	{
        if (str[0] == 45)
            return (2);
		if ((check_key(str[i])) == 1)
		{
			error_print_unset(str, i);  //потом изменить!
			return (1);
		}
		i ++;
	}
	return (-1);
}

int unset_main(int index)
{
	int i;
    int flag;

    flag = 0;
	i = 0;
	while (inf.pipes[index].cmd[i])
    {
        flag = check_pipes_cmd_unset(inf.pipes[index].cmd[i]);
        if (flag == 1)
			return (0);
        if (flag == 2)
            return (2);
        if (flag == 127)
            return (127);
        i ++;
    }
	if (i == 1)
        return (0);
    unset_env_list(inf.lenv, inf.pipes[index].cmd);
    if (!inf.lenv)
        return (0);
    return (0);
}
