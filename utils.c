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
	flags->listdirs = 0;
	flags->noparent = 0;
	flags->time_type = '\0';
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

void		init_t_file(t_file *file)
{
	file->user = NULL;
	file->group = NULL;
	file->type = '\0';
	ft_bzero(file->chmod, sizeof(file->chmod));
	file->target = NULL;
	file->ftime = 0;
	file->nsec = 0;
}
