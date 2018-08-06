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

static void double_def()
{

}

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

void		check_args(int argc, char **argv, t_flags *flags, t_ls *ls)
{
	int		arg;

	arg = 0;
	while (++arg < argc)
	{
		if (!ls->files && argv[arg][0] == '-' && !ft_strequ(argv[arg], "--")
		&& argv[arg][0] != '\0')
			parse_flags(flags, ls, argv[arg], 0);
		else if (ft_strequ(argv[arg], "--"))
			double_def();
	}
}