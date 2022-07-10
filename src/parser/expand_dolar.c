#include "minishell.h"

// int	sizeofline(char *)
// {
// 	int	count;


// }

t_list	*newlst(char *val, int start, int end, char *str)
{
	t_list	*elem;

	elem = (t_list *) malloc(sizeof(t_list));
	if (!elem)
		return (0);
	elem->next = NULL;
	if (str)
	{
		elem->val = str;
		return (elem);
	}
	elem->val = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!elem->val)
		exit_ms("malloc rip", 1);
	ft_strlcpy(elem->val, &val[start], end - start + 1);
	return (elem);
}

int	isdollar(char *line, int i)
{
	if (ft_isdigit(line[i] && i && line[i - 1] == '$'))
		return (1);
	if (line[i] == '?' && i && line[i - 1] == '$')
		return (1);
	if (ft_isalpha(line[i]) || line[i] == '_'
		|| (line[i] == '$' && i && line[i - 1] == '$'))
		return (1);
	return (0);
}

char *replace_dollar(char *line, int start, int end)
{
	char	*str;
	int		i;

	str = NULL;
	i = -2;
	if (start == end)
	{
		str = ft_strdup("$");
		if (!str)
			exit_ms("malloc_rip", 1);
		return (str);
	}
	if (line[start] == '$')
	{
		while (++i < (end - start + 2) / 2)
			strapp(&str, "228", 1);
		if ((end - start + 2) % 2)
			strapp(&str, "$", 1);
		return (str);
	}
	str = (char *)malloc(sizeof(char) * (end - start + 2));
	if (!str)
		exit_ms("malloc rip", 1);
	ft_strlcpy(str, &line[start], end - start + 2);
	printf("%s;%d;%d\n", str, start, end);
	return (find_env(str));
}

char	*joinlist(t_list **bl)
{
	char	*str;
	t_list	*elem;
	t_list	*tmp;

	str = NULL;
	elem = *bl;
	while (elem)
	{
		tmp = elem;
		strapp(&str, elem->val, 2);
		elem = elem->next;
		free(tmp);
	}
	free(bl);
	return (str);
}

char	*expand_dol(char *line)
{
	t_list	**bl;
	int		i;
	int		start;

	i = -1;
	start = 0;
	bl = (t_list **)malloc(sizeof(t_list *));
	if (!bl)
		exit_ms("malloc rip", 1);
	*bl = NULL;
	while (line[++i])
	{
		// printf("%d\n", i);
		if (line[i] == '\'')
		{
			while (line[++i] && line[i] != '\'')
				;
			if (!line[i])
				exit_ms("not closed quote", 1);
		}
		else if (line[i] == '$')
		{
			ft_lstadd_back(bl, newlst(line, start, i, NULL));
			start = 1 + i;
			while(line[++i] && isdollar(line, i))
				;
			ft_lstadd_back(bl, newlst(line, 0, 0, replace_dollar(line, start, i - 1)));
			start = i--;
			// if (!line[i])
			// 	break ;
		}
	}
	if (start != i)
	{
		// ft_putendl_fd("ll", 1);
		ft_lstadd_back(bl, newlst(line, start, i, NULL));
	}
	if (!*bl)
	{
		free(bl);
		return (line);
	}
	free(line);
	return (joinlist(bl));
}