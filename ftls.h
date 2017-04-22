/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 19:31:26 by lwang             #+#    #+#             */
/*   Updated: 2017/04/06 19:31:31 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTLS_H
# define FTLS_H

# include <dirent.h>
# include <stdio.h>
# include "./libft/libft.h"
# include <sys/types.h>
# include <sys/dir.h>
# include <sys/stat.h>

# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <time.h>

#define FLAG_A 1
#define FLAG_R 2
#define FLAG_CAP_R 4
#define FLAG_T 8
#define FLAG_L 16
#define FLAG_ONE 32
#define FLAG_F 64
#define FLAG_N 128
#define FLAG_U 256

typedef struct	s_linfo
{
	char *path;
	char *file_path;
	t_list *invalid;//
	t_list *file;//
	t_list *directory;//
	int flag;//
	int count;//
	long long block_size;
	long max_link;
	long long max_bytes_nbr;
	int is_file;
}				t_linfo;

void merge_sort(t_list **headref, int (*compare_fuc)(t_list *, t_list *, t_linfo *), t_linfo *info);
// void front_back_split(t_list *source, t_list **frontref, t_list **backref)
int	compare_fuc_file(t_list *a, t_list *b, t_linfo *info);
int	compare_fuc_dir(t_list *a, t_list *b, t_linfo *info);
int	compare_fuc_r_dir(t_list *a, t_list *b, t_linfo *info);
int	compare_fuc_t(t_list *a, t_list *b, t_linfo *info);
int	compare_fuc_rt(t_list *a, t_list *b, t_linfo *info);

// t_list *sorted_merge_dir(t_list *a, t_list *b);
// t_list *sorted_merge_r_dir(t_list *a, t_list *b);
// t_list *sorted_merge_a_dir(t_list *a, t_list *b);
// t_list *sorted_merge_file(t_list *a, t_list *b);
// t_list *sorted_merge_t(t_list *a, t_list *b, t_linfo *info);
// void merge_sort_time(t_list **headref, t_list *(*f)(t_list *, t_list *, t_linfo *), t_linfo *info);
// t_list *sorted_merge_rt(t_list *a, t_list *b, t_linfo *info);

// void front_back_split(t_list *source, t_list **frontref, t_list **backref);
// void merge_sort(t_list **headref, t_list *(*f)(t_list *, t_list *));

int	list_directory(char *path, int len, t_linfo *info, int sign);
void	get_lst(struct dirent *dir, t_list **all_lst, t_list **dir_lst, t_linfo *info);
char	*get_path(char *path, char *name);
void	lst_print_all_color(t_list *lst, char *path, t_linfo *info);
char	*add_path(char *dname, char *path);

void	print_l(struct stat sb, struct dirent *dir, int sign, t_linfo *info);
t_linfo *pre_display_l(t_linfo *info, struct stat sb);
void modi_time(char *s, struct stat sb);
char  *cut_second(char *s);
char	get_type(struct stat sb);
int	max_len(long long nbr);

void	ft_lstfree(t_list *lst);
void	get_max_space(t_linfo *info, struct stat sb);
void	get_file_max_space(t_linfo *info, t_list *file);
void	change_sort_way(t_list **lst, t_linfo *info);

void	lst_print_all(t_list *lst);////

#endif




