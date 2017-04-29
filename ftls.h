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
#include <unistd.h>
#include <sys/xattr.h>

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
	char *full_link;
	t_list *invalid;//
	t_list *file;//
	t_list *directory;//
	int flag;//
	int count_arg;

	long long block_size;
	long max_link;
	long long max_bytes_nbr;
	int max_on;//max owner name
	int max_gn;//max group name 
	long max_major;
	long max_minor;

	int is_file;
	int is_dir;// print total blocksize = 0 while only one file contained, .  and .. and one file
	int dir_sign;
}				t_linfo;

//ls_parse_arg.c
t_linfo	*parse_argument(char **av, t_linfo *info);
int	get_arg(t_linfo *info, char *av);
char *get_full_link(char *av, char* link);
char *get_link_file(char *link_name);
char	**parse_flag(char **av, int *flag);
void  get_flag(char *av, int *flag);

//ls_print_all.c 

void	print_directory(t_linfo *info);
void	print_file(t_list *file, t_linfo *info);
void	get_file_max_space(t_linfo *info, t_list *file);
void	print_unvalid(t_list *invalid, t_linfo *info);


void merge_sort(t_list **headref, int (*compare_fuc)(t_list *, t_list *, t_linfo *), t_linfo *info);
// void front_back_split(t_list *source, t_list **frontref, t_list **backref)

// int	compare_fuc_dir(t_list *a, t_list *b, t_linfo *info);
// int	compare_fuc_r_dir(t_list *a, t_list *b, t_linfo *info);
// int	compare_fuc_t(t_list *a, t_list *b, t_linfo *info);
// int	compare_fuc_rt(t_list *a, t_list *b, t_linfo *info);
// int	compare_fuc_ru_file(t_list *a, t_list *b, t_linfo *info);
// int	compare_fuc_u_file(t_list *a, t_list *b, t_linfo *info);
int	compare_fuc_rt_dir(t_list *a, t_list *b, t_linfo *info);
int	compare_fuc_t_dir(t_list *a, t_list *b, t_linfo *info);
int	compare_fuc_r_dir(t_list *a, t_list *b, t_linfo *info);
int	compare_fuc_dir(t_list *a, t_list *b, t_linfo *info);

int	compare_fuc_rt_file(t_list *a, t_list *b, t_linfo *info);
int	compare_fuc_t_file(t_list *a, t_list *b, t_linfo *info);
int	compare_fuc_r_file(t_list *a, t_list *b, t_linfo *info);
int	compare_fuc_file(t_list *a, t_list *b, t_linfo *info);

int	list_directory(char *path, int len, t_linfo *info, int sign);
void	get_lst(struct dirent *dir, t_list **all_lst, t_list **dir_lst, t_linfo *info);
char	*get_path(char *path, char *name);
void	lst_print_all_rec(t_list *lst, t_linfo *info);
char	*add_path(char *dname, char *path);

void	print_l(struct stat sb, struct dirent *dir, t_linfo *info);
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
char *get_link_path(char *lname, char *lpath);
void	print_helper(struct dirent *dir, struct stat sb, char *path, t_linfo *info);

void	print_link(char *av, t_linfo *info);

#endif




