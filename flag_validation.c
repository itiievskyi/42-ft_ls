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
		(arg[i] == 'l' || arg[i] == 'g' || arg[i] == 'o') ?
		flags->longform = 1 : 0;
		(arg[i] == 'a' || arg[i] == 'f') ? flags->dotfiles = 1 : 0;
		arg[i] == 'r' ? flags->revsort = 1 : 0;
		arg[i] == 'R' ? flags->recursive = 1 : 0;
		arg[i] == 'S' ? flags->sizesort = 1 : 0;
		arg[i] == 't' ? flags->timesort = 1 : 0;
		arg[i] == 'd' ? flags->listdirs = 1 : 0;
		arg[i] == 'c' ? flags->time_type = 'c' : 0;
		arg[i] == 'U' ? flags->time_type = 'U' : 0;
		arg[i] == 'u' ? flags->time_type = 'u' : 0;
		arg[i] == '1' ? flags->longform = 0 : 0;
		arg[i] == 'g' ? flags->noowner = 1 : 0;
		arg[i] == 'o' ? flags->nogroup = 1 : 0;
		arg[i] == 'f' ? flags->nosort = 1 : 0;
		arg[i] == 'T' ? flags->fulltime = 1 : 0;
		arg[i] == 'F' ? flags->filetypes = 1 : 0;
		arg[i] == 'p' ? flags->filetypes = 2 : 0;
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
		sort_list(&ls->files, flags);
		print_list(ls, ls->files, flags);
		if (ls->objs)
			write(1, "\n", 1);
	}
}

static void	get_list(char *arg, t_flags *flags, t_ls *ls, char *buf)
{
	struct stat	stat;
	DIR			*dir;
	char		*error;

	error = NULL;
	arg ? readlink(arg, buf, 1024) : 0;
	dir = opendir(arg);
	dir == NULL ? error = ft_strdup(strerror(errno)) : 0;
	if (ft_strlen(buf) > 0 && flags->longform == 1)
		t_file_pushback(&(ls->files), arg, ls->path, flags);
	else if (ft_strlen(buf) > 0 && dir == NULL &&
	ft_strequ(error, "No such file or directory") &&
	!lstat(arg, &stat))
		t_file_pushback(&(ls->files), arg, ls->path, flags);
	else if (arg && dir == NULL &&
	ft_strequ(error, "Not a directory"))
		t_file_pushback(&(ls->files), arg, ls->path, flags);
	else if (arg && dir == NULL &&
	ft_strequ(error, "No such file or directory"))
		t_file_pushback(&(ls->err), arg, error, flags);
	else if (arg)
		t_file_pushback(&(ls->objs), arg, ls->path, flags);
	error == NULL ? 0 : free(error);
	dir == NULL ? 0 : closedir(dir);
}

void		check_args(int argc, char **argv, t_flags *flags, t_ls *ls)
{
	int		arg;
	char	*buf;

	arg = 0;
	ls->path = ft_strdup("");
	while (++arg < argc)
	{
		if (argv[arg] && !ls->objs && !ls->err && !ft_strequ(argv[arg], "--")
		&& !ls->files && argv[arg][0] == '-' && !ft_strequ(argv[arg], "-"))
			parse_flags(flags, ls, argv[arg], 0);
		else if (argv[arg])
		{
			buf = (char*)malloc(sizeof(char) * 1024);
			buf[0] = '\0';
			if (!ls->objs && !ls->err && !ls->files &&
			ft_strequ(argv[arg], "--"))
				arg++;
			if (flags->listdirs == 1)
				get_d_list(argv[arg], flags, ls, buf);
			else
				get_list(argv[arg], flags, ls, buf);
			free(buf);
		}
	}
	finish_parsing(ls, flags);
}
