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
//	system("leaks ft_ls > leaks.out");
	int a = -1;
	while (ls->objs[++a])
		ft_printf("objs[%d] = %s\n", a, ls->objs[a]);
	return (0);
}
