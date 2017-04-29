/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_parse_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 18:45:48 by lwang             #+#    #+#             */
/*   Updated: 2017/04/28 18:45:53 by lwang            ###   ########.fr       */
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

char *get_full_link(char *av, char* link)
{
	char *dst;

	dst = ft_strjoin(av, " -> ");
	dst = ft_strjoin(dst, link);

	return (dst);
}

int	get_arg(t_linfo *info, char *av)
{
	struct stat sb;
	struct stat sb1;
	char *link;// link is the part after ->

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
		else if ((sb.st_mode & S_IFMT) == S_IFLNK)
		{
				link = get_link_file(av);// av is the part before -> 
				info->full_link = get_full_link(av, link);
				// ft_printf("full link file is %s -> %s\n", av, link);
				if (lstat(link, &sb1) == -1)
				{
					ft_lstadd(&info->file, ft_lstnew(av, (int)ft_strlen(av) + 1));
				}
				if ((sb1.st_mode & S_IFMT) == S_IFDIR)
				{
					if (info->flag & FLAG_L)
					{
						ft_lstadd(&info->file, ft_lstnew(av, (int)ft_strlen(av) + 1));
					}
					else
						ft_lstadd(&info->directory, ft_lstnew(link, (int)ft_strlen(link) + 1));
				}
				else if ((sb1.st_mode & S_IFMT) == S_IFREG)
				{
					ft_lstadd(&info->file, ft_lstnew(av, (int)ft_strlen(av) + 1));
				}
				else
					return (0);
		}
		else
		{
			ft_lstadd(&info->file, ft_lstnew(av, (int)ft_strlen(av) + 1));
		}
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
