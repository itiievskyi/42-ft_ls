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
//		system("leaks ft_ls");
	}
	read_objs(flags, ls);
	clean_ls(ls);
	free(flags);
//	system("leaks ft_ls > leaks.out");
	return (0);
}
