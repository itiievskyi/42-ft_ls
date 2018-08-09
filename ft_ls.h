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
# define FLAGS "Ralrt"

typedef struct		s_file
{
	char			*name;
	char			*path;
	char			*full;
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
	int				timesort;
}					t_flags;

typedef struct		s_ls
{
	int				files;
	int				flags;
	int				*argc;
	struct s_file	*objs;
	struct s_file	*err;
}					t_ls;

void				check_args(int argc, char **argv, t_flags *flags, t_ls *ls);
void				init_struct(t_flags *flags, t_ls *ls, int size);
void				wrong_arg(t_flags *flags, t_ls *ls, char ch);
void				read_objs(t_flags *flags, t_ls *ls);
t_file				*create_list(t_flags *flags, t_ls *ls, DIR *dir, char *cat);
int					t_file_pushback(t_file **begin, char *name, char *cat);
t_file				*t_file_new(char *name, char *cat);
void				sort_list(t_file *file, t_flags *flags);
void				ft_str_swap(char **a, char **b);
void				ft_stat_swap(struct stat *a, struct stat *b);
void				display(t_ls *ls, t_file *file);
int					count_list_length(t_file *file);
#endif
