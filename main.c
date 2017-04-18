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
         ft_printf("ft_ls: illegal option -- %c\n", *av);
         ft_printf("usage: ft_ls [-arRtl1fnu] [file ...]\n");
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

int	get_arg(t_linfo *info, char *av)
{
	DIR *dirp;
	struct stat sb;

	if (av)
	{
		dirp = opendir(av);
		if (dirp != NULL)
			ft_lstadd(&info->directory, ft_lstnew(av, (int)ft_strlen(av) + 1));
		else if (stat(av, &sb) == -1)
			ft_lstadd(&info->invalid, ft_lstnew(av, (int)ft_strlen(av) + 1));
		else
			ft_lstadd(&info->file, ft_lstnew(av, (int)ft_strlen(av) + 1));
	}
	return (0);
}

t_linfo	*parse_argument(char **av, t_linfo *info)
{
	av = parse_flag(av, &info->flag);
	if (*av == NULL)
		ft_lstadd(&info->directory, ft_lstnew(".", 2));
	while (*av != NULL)
	{
		info->count++;
		get_arg(info, *av++);
	}
	return (info);
}

void	print_unvalid(t_list *invalid)
{
	t_list *cur;

	cur = invalid;
	merge_sort(&cur, sorted_merge_file);
	while (cur)
	{
		ft_fprintf(2, "ls: %s: No such file or directory\n", (char*)cur->content);
		cur = cur->next;
	}
	// ft_lstfree(path);
}

void	print_file(t_list *file, t_linfo *info)//int flag
{
	t_list *cur;

	cur = file;
	if (info->flag & FLAG_R)
		merge_sort(&cur, sorted_merge_file);
	else
		merge_sort(&cur, sorted_merge_file);
	// if (flag & FLAG_T)
	// 	merge_sort(&cur, sort_by_t)
	// if (flag & FLAG_U)
	// 	merge_sort(&cur, sort_by_u)
	
	while(cur != NULL)
	{
		ft_printf("%s\n", (char*)cur->content);
		cur = cur->next;
	}
	// ft_lstfree(file);
}

void	print_directory(t_linfo *info)
{
	t_list *cur;

	cur = info->directory;
	while (cur)
	{
		list_directory(cur->content, (int)ft_strlen((char*)cur->content), info);
		cur = cur->next;
	}
	// ft_lstfree(directory);
}

int main(int ac, char **av)
{
	(void)ac;
	t_linfo *info;
	info = (t_linfo*)malloc(sizeof(t_linfo) * 1);
	ft_bzero(info, sizeof(t_linfo));

	info = parse_argument(av, info);
	print_unvalid(info->invalid);
	print_file(info->file, info);//, int flag for r
	print_directory(info);
	// free(info);
	return (0);
}
