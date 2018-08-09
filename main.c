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
		init_struct(flags, ls, argc);
		check_args(argc, argv, flags, ls);
	}
	read_objs(flags, ls);
//	ft_sort_strtab(ls->objs, "asc");
//	ft_sort_strtab(ls->objs, "desc");
//	int a = -1;
//	while (ls->objs[++a])
//		ft_printf("objs[%d] = %s\n", a, ls->objs[a]);
//	system("leaks ft_ls > leaks.out");
	return (0);
}
