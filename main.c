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

	if ((flags = (t_flags*)malloc(sizeof(t_flags))) &&
		(ls = (t_ls*)malloc(sizeof(t_ls))))
	{
		init_struct(flags, ls);
		check_args(argc, argv, flags, ls);
	}
	return (0);
}
