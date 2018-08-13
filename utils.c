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

void		init_struct(t_flags *flags, t_ls *ls)
{
	flags->longform = 0;
	flags->dotfiles = 0;
	flags->revsort = 0;
	flags->recursive = 0;
	flags->timesort = 0;
	ls->folders = NULL;
	ls->objs = NULL;
	ls->files = NULL;
	ls->err = NULL;
	ls->path = NULL;
}

void		init_pstat(t_pstat *pstat)
{
	pstat->maxgrp = 0;
	pstat->maxusr = 0;
	pstat->maxsize = 0;
	pstat->maxlnk = 1;
	pstat->total = 0;
}
