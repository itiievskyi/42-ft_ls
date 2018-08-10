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
	ft_putstr_fd("ft_ls: illegal option -- ", 2);
	ft_putchar_fd(ch, 2);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd("usage: ./ft_ls [-", 2);
	ft_putstr_fd(FLAGS, 2);
	ft_putstr_fd("] [file ...]\n", 2);
	free(flags);
	free(ls);
//	system("leaks ft_ls > leaks.out");
	exit(-1);
}
