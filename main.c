/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 16:08:44 by lwang             #+#    #+#             */
/*   Updated: 2017/04/18 00:03:43 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftls.h"

void  get_flag(char *av, int *flag)
{
   while (*++av)
   {
		if (*av == 'a')
			*flag |= FLAG_A;
		else if (*av == 'r')
			*flag |= FLAG_R;
		else if (*av == 'R')
			*flag |= FLAG_CAP_R;
		else if (*av == 't')
			*flag |= FLAG_T;
		else if (*av == 'l')
			*flag |= FLAG_L;
		else if (*av == '1')
			*flag |= FLAG_ONE;
		else if (*av == 'f')
			*flag |= FLAG_F;
		else if (*av == 'n')
			*flag |= FLAG_N;
		else if (*av == 'u')
			*flag |= FLAG_U;
		else
		{
			ft_printf("ls: illegal option -- %c\n", *av);
			ft_printf("usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]\n");
			// ft_printf("ft_ls: illegal option -- %c\n", *av);
			// ft_printf("usage: ft_ls [-arRtl1fnu] [file ...]\n");
			exit(1);
		}
	}
}

char	**parse_flag(char **av, int *flag)
{
	while (*++av)
	{
		if (av[0][0] == '-')
			get_flag(*av, flag);
		else
			break ;
	}
	return (av);
}

char *get_link_file(char *link_name)
{
	ssize_t len;
	int tmp;
	char *s;

	len = 0;
	tmp = 0;
	s = (char*)malloc(sizeof(char) * 226);
	tmp = readlink(link_name, s, 225);
	if (tmp != -1)
		len = tmp;
	s[len] = '\0';
	return (s);
}

// void	print_link(char *av, t_linfo *info)
// {
// 	struct stat sb;
// 	char *link;

// 	link = get_link_file(av);
// 	// if (lstat(link, &sb) == -1)
// 	// 	ft_lstadd(&info->invalid, ft_lstnew(av, (int)ft_strlen(av) + 1));
// 	if ((sb.st_mode & S_IFMT) == S_IFDIR)
// 	{
// 		if (!(sb.st_mode & S_IRUSR) && !(sb.st_mode & S_IWUSR) && !(sb.st_mode & S_IXUSR)\
//  	&& !(sb.st_mode & S_IRGRP) && !(sb.st_mode & S_IWGRP) && !(sb.st_mode & S_IXGRP) && !(sb.st_mode & S_IROTH) && !(sb.st_mode & S_IWOTH) && !(sb.st_mode & S_IXOTH))
// 		{
// 			ft_fprintf(2, "ls: %s: Permission denied\n", av);//ft_ls
// 			exit(1);
// 		}
// 		ft_lstadd(&info->directory, ft_lstnew(av, (int)ft_strlen(av) + 1));
// 	}
// 	else// if ((sb.st_mode & S_IFMT) == S_IFREG)
// 	{
// 		ft_lstadd(&info->file, ft_lstnew(av, (int)ft_strlen(av) + 1));
// 	}

// }

int	get_arg(t_linfo *info, char *av)
{
	// DIR *dirp;
	struct stat sb;
	struct stat sb1;
	char *link;

	if (av)
	{
		if (ft_strcmp(av, "") == 0)
		{
			ft_fprintf(2, "ls: fts_open: No such file or directory\n");
			exit(1);
		}

		if (lstat(av, &sb) == -1)
		{
			// ft_printf("it's invalid\n");
			ft_lstadd(&info->invalid, ft_lstnew(av, (int)ft_strlen(av) + 1));
		}
		// if ((sb.st_mode & S_IFMT) == S_IFLNK)
		// {
		// 	print_link(av, info);
		// 	// av = ft_strdup(get_link_file(av));
		// 	// lstat(av, &sb);
		// }
		else if ((sb.st_mode & S_IFMT) == S_IFDIR)
		{
			// ft_printf("it's dir\n");
			if (!(sb.st_mode & S_IRUSR) && !(sb.st_mode & S_IWUSR) && !(sb.st_mode & S_IXUSR)\
	 	&& !(sb.st_mode & S_IRGRP) && !(sb.st_mode & S_IWGRP) && !(sb.st_mode & S_IXGRP) && !(sb.st_mode & S_IROTH) && !(sb.st_mode & S_IWOTH) && !(sb.st_mode & S_IXOTH))
			{
				ft_fprintf(2, "ls: %s: Permission denied\n", av);//ft_ls
				exit(1);
			}
			ft_lstadd(&info->directory, ft_lstnew(av, (int)ft_strlen(av) + 1));
		}
		else //if ((sb.st_mode & S_IFMT) == S_IFREG)
		{
			if ((sb.st_mode & S_IFMT) == S_IFLNK)
			{
				link = get_link_file(av);
				if (lstat(link, &sb1) == -1)
				{
					ft_lstadd(&info->invalid, ft_lstnew(link, (int)ft_strlen(link) + 1));
				}
				if ((sb1.st_mode & S_IFMT) == S_IFDIR)
					ft_lstadd(&info->directory, ft_lstnew(link, (int)ft_strlen(link) + 1));
				else if ((sb.st_mode & S_IFMT) == S_IFREG)
					ft_lstadd(&info->file, ft_lstnew(link, (int)ft_strlen(link) + 1));
			}
			// ft_lstadd(&info->file, ft_lstnew(av, (int)ft_strlen(av) + 1));
		}

		// else
		// {
		// 	ft_printf("something else");
		// 	exit(1);
		// }

		// dirp = opendir(av);
		// if (dirp != NULL)
		// {
		// 	ft_lstadd(&info->directory, ft_lstnew(av, (int)ft_strlen(av) + 1));
		// }
		// else if (lstat(av, &sb) == -1)
		// 	ft_lstadd(&info->invalid, ft_lstnew(av, (int)ft_strlen(av) + 1));
		// else
		// 	ft_lstadd(&info->file, ft_lstnew(av, (int)ft_strlen(av) + 1));
	}
	return (0);
}

t_linfo	*parse_argument(char **av, t_linfo *info)
{
	av = parse_flag(av, &info->flag);
	if (*av == NULL)
	{
		
		ft_lstadd(&info->directory, ft_lstnew(".", 2));
	}
	while (*av != NULL)
	{
		info->count_arg++;
		get_arg(info, *av++);
	}
	return (info);
}

void	ft_lstfree(t_list *lst)
{
	while (lst)
	{
		free(lst);
		lst = lst->next;
	}
}

void	print_unvalid(t_list *invalid, t_linfo *info)
{
	t_list *cur;

	cur = invalid;
	merge_sort(&cur, compare_fuc_file, info);
	while (cur)
	{
		ft_fprintf(2, "ls: %s: No such file or directory\n", (char*)cur->content);
		cur = cur->next;
	}
	ft_lstfree(invalid);
}

void	get_file_max_space(t_linfo *info, t_list *file)
{
	t_list *cur;
	struct stat sb;

	cur = file;
	while (cur)
	{
		if (lstat((char*)cur->content, &sb) == -1)
		{
			perror("stat3");
			exit(1);
		}
		get_max_space(info, sb);
		cur = cur->next;
	}
}

void	print_file(t_list *file, t_linfo *info)
{
	t_list *cur;
	struct stat sb;
	struct dirent *dir;

	cur = file;
	dir = NULL;
	get_file_max_space(info, file);
	if (info->flag & FLAG_R && info->flag & FLAG_T)
	{
		merge_sort(&cur, compare_fuc_file, info);
		merge_sort(&cur, compare_fuc_rt_file, info);
	}
	else if (info->flag & FLAG_R)
		merge_sort(&cur, compare_fuc_r_file, info);
	else if (info->flag & FLAG_T)
		merge_sort(&cur, compare_fuc_t_file, info);
	else
		merge_sort(&cur, compare_fuc_file, info);
	while(cur != NULL)
	{
		if (info->flag & FLAG_L)
		{
			info->is_file = 1;
			if (lstat((char*)cur->content, &sb) == -1)
			{
				perror("stat2");
				exit(1);
			}
			info->file_path = ft_strdup((char*)cur->content);
			print_l(sb, dir, info);//0
		}
		else
			ft_printf("%s\n", (char*)cur->content);
		cur = cur->next;
	}
	ft_lstfree(file);
}

void	print_directory(t_linfo *info)
{
	t_list *cur;

	cur = info->directory;

	merge_sort(&cur, compare_fuc_file, info);
	while (cur)
	{
		info->dir_sign++;
		list_directory(cur->content, (int)ft_strlen((char*)cur->content), info, 0);
		cur = cur->next;
	}
	ft_lstfree(info->directory);
}

int main(int ac, char **av)
{
	(void)ac;
	t_linfo *info;
	info = (t_linfo*)malloc(sizeof(t_linfo) * 1);
	ft_bzero(info, sizeof(t_linfo));

	info = parse_argument(av, info);

	print_unvalid(info->invalid,info);
	print_file(info->file, info);
	print_directory(info);
	free(info);
	return (0);
}
