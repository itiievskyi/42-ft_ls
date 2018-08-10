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
	ls->flags++;
	while (arg[++i] != '\0')
	{
		if (!ft_strchr(FLAGS, arg[i]))
			wrong_arg(flags, ls, arg[i]);
		else if (arg[i] == 'l')
			flags->longform = 1;
		else if (arg[i] == 'a')
			flags->dotfiles = 1;
		else if (arg[i] == 'r')
			flags->revsort = 1;
		else if (arg[i] == 'R')
			flags->recursive = 1;
		else if (arg[i] == 't')
			flags->timesort = 1;
	}
}

static void	finish_parsing(t_ls *ls, t_flags *flags)
{
	print_errors(ls);
	if (ls->files)
	{
		sort_list(ls->files, flags);
		print_list(ls, ls->files, flags);
		if (ls->objs)
			write(1, "\n", 1);
	}
	if (!ls->objs && !ls->err && !ls->files)
		t_file_pushback(&(ls->objs), ".", "");
}

void		check_args(int argc, char **argv, t_flags *flags, t_ls *ls)
{
	int		arg;

	arg = 0;
	while (++arg < argc)
	{
		if (argv[arg] && !ls->objs && !ls->err && !ls->files &&
		argv[arg][0] == '-' && !ft_strequ(argv[arg], "--"))
			parse_flags(flags, ls, argv[arg], 0);
		else if (argv[arg])
		{
			if (!ls->objs && !ls->err && ft_strequ(argv[arg], "--"))
				arg++;
			if (argv[arg] && (opendir(argv[arg])) == NULL &&
			ft_strequ(strerror(errno), "Not a directory"))
				t_file_pushback(&(ls->files), argv[arg], "");
			else if (argv[arg] && (opendir(argv[arg])) == NULL)
				t_file_pushback(&(ls->err), argv[arg], strerror(errno));
			else if (argv[arg])
				t_file_pushback(&(ls->objs), argv[arg], "");
		}
	}
	finish_parsing(ls, flags);
}
