/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 14:23:25 by itiievsk          #+#    #+#             */
/*   Updated: 2018/08/06 14:23:27 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		init_struct(t_flags *flags, t_ls *ls, int size)
{
	flags->longform = 0;
	flags->dotfiles = 0;
	flags->revsort = 0;
	flags->recursive = 0;
	flags->timesort = 0;
	ls->files = 0;
	ls->flags = 0;
	ls->argc = (int*)malloc(sizeof(int) * size);
}