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

t_wldcrd	*wldcrd(char *str)
{
	t_wldcrd		*list;
	DIR				*dirp;
	struct dirent	*dp;
//	char			*new_file;
	(void)str;

	list = NULL;
	dirp = opendir(".");
	if (dirp == NULL)
		exit_ms("opendir error!", 1);
	while (1)
	{
		dp = readdir(dirp);
		if (dp == NULL)
			break ;
		if (ft_strncmp(".", dp->d_name, 1) == 0)
			continue ;
		wldadd_back(&list, new_lst(dp->d_name));
	}
	print_files(list);
	return (list);
}

int main()
{
	wldcrd("looooooooooool");
}


	

	//dirp = opendir(".");
	//if (dirp == NULL)
	//        return (ERROR);
	//len = strlen(name);
	//while ((dp = readdir(dirp)) != NULL) {
	//        if (dp->d_namlen == len && strcmp(dp->d_name, name) == 0) {
	//                (void)closedir(dirp);
	//                return (FOUND);
	//        }
	//}
	//(void)closedir(dirp);
	//return (NOT_FOUND);
