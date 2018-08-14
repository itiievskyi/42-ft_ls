/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 11:23:34 by itiievsk          #+#    #+#             */
/*   Updated: 2018/08/06 11:23:36 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	parse_flags(t_flags *flags, t_ls *ls, char *arg, int i)
{
	while (arg[++i] != '\0')
	{
		if (!ft_strchr(FLAGS, arg[i]))
			wrong_arg(flags, ls, arg[i]);
		arg[i] == 'A' ? flags->noparent = 1 : 0;
		arg[i] == 'l' ? flags->longform = 1 : 0;
		arg[i] == 'a' ? flags->dotfiles = 1 : 0;
		arg[i] == 'r' ? flags->revsort = 1 : 0;
		arg[i] == 'R' ? flags->recursive = 1 : 0;
		arg[i] == 't' ? flags->timesort = 1 : 0;
		arg[i] == 'd' ? flags->listdirs = 1 : 0;
		arg[i] == 'c' ? flags->time_type = 'c' : 0;
		arg[i] == 'U' ? flags->time_type = 'U' : 0;
		arg[i] == 'u' ? flags->time_type = 'u' : 0;
	}
}

static void	finish_parsing(t_ls *ls, t_flags *flags)
{
	print_errors(ls);
	if (!ls->objs && !ls->err && !ls->files && flags->listdirs == 0)
		t_file_pushback(&(ls->objs), ".", "", flags);
	if (!ls->files && flags->listdirs == 1)
	{
		flags->dotfiles = 1;
		t_file_pushback(&(ls->files), ".", "", flags);
	}
	if (ls->files)
	{
		sort_list(ls->files, flags);
		print_list(ls, ls->files, flags);
		if (ls->objs)
			write(1, "\n", 1);
	}
}

static void	get_list(char *arg, t_flags *flags, t_ls *ls)
{
	char 		*buf;
	struct stat	stat;

	buf = (char*)malloc(sizeof(char) * 1024);
	buf[0] = '\0';
	if (arg)
		readlink(arg, buf, 1024);
	if (ft_strlen(buf) > 0 && flags->longform == 1)
		t_file_pushback(&(ls->files), arg, ls->path, flags);
	else if (ft_strlen(buf) > 0 && (opendir(arg)) == NULL &&
	ft_strequ(strerror(errno), "No such file or directory") &&
	!lstat(arg, &stat))
		t_file_pushback(&(ls->files), arg, ls->path, flags);
	else if (arg && (opendir(arg)) == NULL &&
	ft_strequ(strerror(errno), "Not a directory"))
		t_file_pushback(&(ls->files), arg, ls->path, flags);
	else if (arg && (opendir(arg)) == NULL &&
	ft_strequ(strerror(errno), "No such file or directory"))
		t_file_pushback(&(ls->err), arg, strerror(errno), flags);
	else if (arg)
		t_file_pushback(&(ls->objs), arg, ls->path, flags);
	free(buf);
}

void		check_args(int argc, char **argv, t_flags *flags, t_ls *ls)
{
	int		arg;

	arg = 0;
	ls->path = ft_strdup("");
	while (++arg < argc)
	{
		if (argv[arg] && !ls->objs && !ls->err && !ft_strequ(argv[arg], "--")
		&& !ls->files && argv[arg][0] == '-' && !ft_strequ(argv[arg], "-"))
			parse_flags(flags, ls, argv[arg], 0);
		else if (argv[arg])
		{
			if (!ls->objs && !ls->err && !ls->files &&
			ft_strequ(argv[arg], "--"))
				arg++;
			if (flags->listdirs == 1)
				get_d_list(argv[arg], flags, ls);
			else
				get_list(argv[arg], flags, ls);
		}
	}
	finish_parsing(ls, flags);
}
