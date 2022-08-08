#include "minishell.h"

void	print_files(t_wldcrd *list)
{
	while (list)
	{
		printf("%s\n", list->file);
		list = list->next;
	}
}

t_wldcrd  *new_lst(char *val)
{
	t_wldcrd  *elem;
	
	elem = (t_wldcrd *) malloc(sizeof(t_wldcrd));
	if (!elem)
	    return (0);
	elem->next = NULL;
	elem->file = val;
	return (elem);
}

t_wldcrd  *wldlast(t_wldcrd *lst)
{
    if (!lst)
        return (0);
    while (lst->next)
        lst = lst->next;
    return (lst);
}

void    wldadd_back(t_wldcrd **lst, t_wldcrd *new)
{
    t_wldcrd  *f;

    if (!(lst && new))
        return ;
    if (*lst)
    {
        f = wldlast(*lst);
        f->next = new;
    }
    else
        *lst = new;
}

int	selected(char *file, char *wld)
{
	char	*star_index;
	char	*substr;
	char	*strnstr;
	int		first_iter;

	star_index = 0;
	first_iter = 1;
	while (*wld)
	{
		star_index = ft_strchr(wld, '*');
		if (star_index == NULL)
			break ;
		if (star_index == wld)
		{
			first_iter = 0;
			++wld;
			continue ;
		}
		substr = ft_substr(wld, 0, star_index - wld);
		if (!substr)
			exit_ms("malloc_rip", 1);
		strnstr = ft_strnstr(file, substr, ft_strlen(file));
		free(substr);
		if (strnstr == NULL || (first_iter && strnstr != file))
			return (0);
		file = strnstr + (star_index - wld);
		wld = star_index + 1;
		first_iter = 0;
	}
	if (!*wld)
		return (1);
	if (!file)
		return (0);
	if (ft_strnstr(file, wld, ft_strlen(file)) + ft_strlen(wld)
			== file + ft_strlen(file))
		return (1);
	return (0);
}


t_wldcrd	*selection(t_wldcrd *list, char *str)
{
	t_wldcrd	*bl;
	t_wldcrd	*tmp;

	//while (list && !selected(list->file, str))
	//	list = list->next;
	bl = list;
	tmp = bl;
	while (list)
	{
		if (!selected(list->file, str))
		{
			if (bl == list)
			{
				tmp = list->next;
				bl = list->next;
				free(list);
				list = tmp;
				continue ;
			}
			tmp->next = list->next;
			free(list);
			list = tmp->next;
			continue ;
		}
		tmp = list;
		list = list->next;
	}
	return (bl);
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

char	*join_files(t_wldcrd *list)
{
	char		*finish;
	t_wldcrd	*copy;

	finish = NULL;
	copy = list;
	while (list)
	{
		strapp(&finish, list->file, 1);
		list = list->next;	
	}
	free_list(copy);
	return (finish);
}

char	*select_and_join(t_wldcrd *list, char *str)
{
	t_wldcrd	*clear_list;

	clear_list = selection(list, str);
	if (clear_list)
		return (join_files(list));
	//free_list(list);
	return (FILES_NOT_FOUND);
}


char	*wldcrd(char *str)
{
	t_wldcrd		*list;
	//DIR				*dirp;
	//struct dirent	*dp;

	list = NULL;
	//dirp = opendir(".");
	//if (dirp == NULL)
	//	exit_ms("opendir error!", 1);
	int i=0;
	while (1)
	{
		//dp = readdir(dirp);
		//if (dp == NULL)
		//	break ;
		//if (ft_strncmp(".", dp->d_name, 1) == 0)
		//	continue ;
		if (i++ == 13)
			break ;
		wldadd_back(&list, new_lst("lRll"));//dp->d_name));
	}
	if (!list)
		return (NULL);
	//print_files(list);
	return (select_and_join(list, str));
}

int main()
{
	char	*str;

	str = wldcrd("R*");
	ft_putendl_fd(str, 1);
	free(str);
}

