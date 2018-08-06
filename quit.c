/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 14:01:56 by itiievsk          #+#    #+#             */
/*   Updated: 2018/08/06 14:01:58 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		wrong_arg(t_flags *flags, t_ls *ls, char ch)
{
	ft_printf("ft_ls: illegal option -- %c\n", ch);
	ft_printf("usage: ./ft_ls [-%s] [file ...]\n", FLAGS);
	free(flags);
	free(ls);
//	system("leaks ft_ls > leaks.out");
	exit(-1);
}
