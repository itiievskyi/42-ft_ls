/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 10:16:25 by itiievsk          #+#    #+#             */
/*   Updated: 2018/08/06 10:16:27 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	wrong_arg(t_flags *flags, t_ls *ls, char ch)
{
	ft_putstr_fd("ft_ls: illegal option -- ", 2);
	ft_putchar_fd(ch, 2);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd("usage: ./ft_ls [-", 2);
	ft_putstr_fd(FLAGS, 2);
	ft_putstr_fd("] [file ...]\n", 2);
	free(flags);
	free(ls);
	exit(1);
}

int		main(int argc, char **argv)
{
	t_flags	*flags;
	t_ls	*ls;

	ls = NULL;
	if ((flags = (t_flags*)malloc(sizeof(t_flags))) &&
		(ls = (t_ls*)malloc(sizeof(t_ls))))
	{
		init_struct(flags, ls);
		ls->start = 1;
		check_args(argc, argv, flags, ls);
	}
	read_objs(flags, ls);
	clean_ls(ls);
	free(flags);
	return (0);
}
