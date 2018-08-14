/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 10:15:29 by itiievsk          #+#    #+#             */
/*   Updated: 2018/08/06 10:15:31 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "./libft/libft.h"
# include <sys/types.h>
# include <dirent.h>
# include <errno.h>
# include <sys/stat.h>
# include <time.h>
# include <stdio.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# define FLAGS "1ARSUacdfglprtu"

typedef struct		s_file
{
	char			*name;
	char			*path;
	char			*full;
	char			*user;
	char			*group;
	char			type;
	char			chmod[11];
	char			*target;
	time_t			ftime;
	time_t			nsec;
	struct stat		stat;
	struct s_file	*next;
	struct s_file	*prev;
}					t_file;

typedef struct		s_flags
{
	int				longform;
	int				dotfiles;
	int				revsort;
	int				recursive;
	int				sizesort;
	int				timesort;
	int				listdirs;
	int				noparent;
	int				slashdir;
	int				noowner;
	int				nosort;
	char			time_type;
}					t_flags;

typedef struct		s_ls
{
	int				start;
	struct s_file	*objs;
	struct s_file	*err;
	struct s_file	*files;
	char			*path;
}					t_ls;

typedef struct		s_pstat
{
	int				maxusr;
	int				maxgrp;
	int				maxlnk;
	int				maxsize;
	int				total;
}					t_pstat;

void				check_args(int argc, char **argv, t_flags *flags, t_ls *ls);
void				init_struct(t_flags *flags, t_ls *ls);
void				wrong_arg(t_flags *flags, t_ls *ls, char ch);
void				read_objs(t_flags *flags, t_ls *ls);
t_file				*create_list(t_flags *flags, t_ls *ls, DIR *dir, char *cat);
int					t_file_pushback(t_file **begin, char *name, char *cat,
					t_flags *flags);
t_file				*t_file_new(char *name, char *cat, t_flags *flags);
void				sort_list(t_file *file, t_flags *flags);
void				swap_t_file(t_file *one, t_file *two);
void				ft_str_swap(char **a, char **b);
void				ft_stat_swap(struct stat *a, struct stat *b);
void				ft_time_swap(time_t *a, time_t *b);
void				print_list(t_ls *ls, t_file *file, t_flags *flags);
void				display(t_ls *ls, t_file *file, t_flags *flags);
void				display_long(t_ls *ls, t_file *file, t_flags *flags);
int					count_list_length(t_file *file);
void				print_errors(t_ls *ls);
void				print_cat_error(char *cat, char *error);
void				alpha_sort(t_file *file);
void				rev_sort(t_file *file, int i, int j);
void				recursion(t_ls *ls, t_flags *flags);
void				init_pstat(t_pstat *pstat);
void				define_chmod(t_file *file);
char				define_type(t_file *file);
void				get_owner(t_pstat *pstat, t_file *file, t_flags *flags);
void				init_t_file(t_file *file);
void				get_d_list(char *arg, t_flags *flags, t_ls *ls);
void				define_time(t_flags *flags, t_file *file);
void				size_sort(t_file *file);
void				insensitive_sort(t_file *file);
#endif
