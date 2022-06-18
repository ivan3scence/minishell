#include "minishell.h"

t_env	*ft_update_env_unset(t_env *lenv, t_env *lenv_tmp, size_t size)
{
    int i;
    void *tmp;

    i = 0;
    free_lenv(lenv);
    lenv = (t_env *)malloc(sizeof(t_env) * size);
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

extern t_mshell inf;

void unset_main(void)
{
	int i;

	i = 0;
	while (inf.pipes[0].cmd[i])
		i ++;
    inf.lenv = unset_env_list(inf.lenv, i, inf.pipes->cmd);
    if (!inf.lenv)
        return ;
    return ;
}

//gcc unset.c ../../includes/minishell.h ../../libft/ft_strlen.c ../../libft/ft_strdup.c ../../libft/ft_strncmp.c ../../src/env_list.c ../../libft/ft_strchr.c unset_utils.c