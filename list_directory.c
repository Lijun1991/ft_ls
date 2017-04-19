/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_directory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 13:47:17 by lwang             #+#    #+#             */
/*   Updated: 2017/04/16 13:47:19 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftls.h"

char	*add_path(char *dname, char *path)
{
	char *dst;

	dst = path;
	if (ft_strcmp(path, ".") == 0)
		dst = dname;
	else
	{
		dst = ft_strjoin(dst, "/");
		dst = ft_strjoin(dst, dname);
	}
	return (dst);
}

// void	lst_print_all(t_list *lst)
// {
// 	t_list *cur;
// 	struct dirent *dir;

// 	cur = lst;
// 	while(cur != NULL)
// 	{
// 		dir = cur->content;
// 		if (dir->d_name[0] != '.')
// 		{
// 			ft_printf("%s\n", dir->d_name);
// 		}
// 		cur = cur->next;
// 	}
// }


void	print_l(struct stat sb, struct dirent *dir)
{
	int bin;
	char *str;

	bin = (int)(sb.st_mode);
	str = ft_itoa(bin);
	if (str[0] == '1')
		ft_putchar('-');
	else if (str[0] == '4')
		ft_putchar('d');
	str++;
	while (*++str)
	{
		if (*str == '0')
			ft_putstr("---");
		else if (*str == '1')
			ft_putstr("--x")
		else if (*str == '6')
			ft_putstr("rwx");
		else if (*str == '5')
			ft_putchar("r-x");
		else if (*str == '3')
			ft_putchar("-wx");
	}
	ft_printf("%d   ", bin);
	ft_printf(GREE"%s\n"CLN, dir->d_name);
}

void	print_l_file(struct stat sb, struct dirent *dir)
{
	ft_printf("%lo   ", sb.st_mode);
	ft_printf("%s\n", dir->d_name);
}

void	lst_print_all_color(t_list *lst, char *path, t_linfo *info)
{
	t_list *cur;
	struct stat sb;
	struct dirent *dir;
	char *sub_dir;

	cur = lst;

	while(cur != NULL)
	{
		dir = cur->content;
		sub_dir = add_path(dir->d_name, path);
		if (stat(sub_dir, &sb) == -1)
		{
			perror("stat2");
			return ;
		}
		if ((info->flag & FLAG_L) && dir->d_name[0] != '.' && ((sb.st_mode & S_IFMT) == S_IFDIR))
			print_l(sb, dir);
		else if (dir->d_name[0] != '.' && ((sb.st_mode & S_IFMT) == S_IFDIR))
			ft_printf(GREE"%s\n"CLN, dir->d_name);
		else if ((info->flag & FLAG_L) && dir->d_name[0] != '.')
			print_l_file(sb, dir);
		else if (dir->d_name[0] != '.')
			ft_printf("%s\n", dir->d_name);
		else if ((info->flag & FLAG_L) && dir->d_name[0] == '.' && (info->flag & FLAG_A))
			print_l_file(sb, dir);
		else if (dir->d_name[0] == '.' && (info->flag & FLAG_A))
			ft_printf("%s\n", dir->d_name);
		cur = cur->next;
	}
}

char	*get_path(char *path, char *name)
{
	char *dst;

	dst = ft_strjoin(path, "/");
	dst = ft_strjoin(dst, name);

	return (dst);
}

void	get_lst(struct dirent *dir, t_list **all_lst, t_list **dir_lst, char *path)
{
	struct stat sb;
	char *sub_dir;

	sub_dir = add_path(dir->d_name, path);
	if (stat(sub_dir, &sb) == -1)
	{
		perror("stat1");
		return ;
	}
	ft_lstadd(all_lst, ft_lstnew(dir, dir->d_reclen));
	if (dir->d_name[0] != '.' && ((sb.st_mode & S_IFMT) == S_IFDIR))
	{
		ft_lstadd(dir_lst, ft_lstnew(dir, dir->d_reclen));
	}
}

int	list_directory(char *path, int len, t_linfo *info)
{
	DIR *dirp;
	struct dirent *dir;
	char *newpath;
	t_list *all_lst;
	t_list	*dir_lst;
	char *tmp;

	tmp = path;
	all_lst = NULL;
	dir_lst = NULL;

	tmp = ft_strsub(tmp, len + 1, ft_strlen(tmp) - len - 1);

	if (info->invalid || info->file || info->count >= 3)
		ft_printf("\n%s:\n", path);
	if (ft_strcmp(tmp, "") != 0)
		ft_printf("\n./%s:\n", tmp);

	dirp = opendir(path);
	if (dirp == NULL)
	{
		perror("dir no exit");
		return (2);
	}
	while ((dir = readdir(dirp)))
		get_lst(dir, &all_lst, &dir_lst, path);

	if (info->flag & FLAG_R)
		merge_sort(&all_lst, sorted_merge_r_dir);
	else
		merge_sort(&all_lst, sorted_merge);
	lst_print_all_color(all_lst, path, info);

	if (info->flag & FLAG_R)
		merge_sort(&dir_lst, sorted_merge_r_dir);
	else
		merge_sort(&dir_lst, sorted_merge);

	while (dir_lst != NULL && (info->flag & FLAG_CAP_R))
	{
		dir = dir_lst->content;
		newpath = get_path(path, dir->d_name);
		list_directory(newpath, len, info);
		dir_lst = dir_lst->next;
	}
    if (!closedir(dirp))
    	return (-1);
    return (0);
}



