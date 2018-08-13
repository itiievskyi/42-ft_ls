/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_long.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 11:11:18 by itiievsk          #+#    #+#             */
/*   Updated: 2018/08/13 11:11:20 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		parse_list(t_pstat *pstat, t_file *file)
{
	t_file			*temp;
	int				lnk_len;
	int				size_len;

	temp = file;
	while (temp)
	{
		pstat->total += (temp->stat).st_blocks;
		lnk_len = ft_intlen(temp->stat.st_nlink);
		size_len = ft_intlen(temp->stat.st_size);
		lnk_len > pstat->maxlnk ? pstat->maxlnk = lnk_len : 0;
		size_len > pstat->maxsize ? pstat->maxsize = size_len : 0;
		temp->type = define_type(temp);
		define_chmod(temp);
		get_owner(pstat, temp);
		temp = temp->next;
	}
}

void		print_time(t_file *temp)
{
	if ((time(NULL) - temp->stat.st_mtime < 15780000 &&
	temp->stat.st_mtime - time(NULL) < 15780000))
		ft_printf("%.12s", ctime(&temp->stat.st_mtime) + 4);
	else if ((ctime(&temp->stat.st_mtime) + 20)[0] != ' ')
		ft_printf("%.7s %.4s", ctime(&temp->stat.st_mtime) + 4,
		ctime(&temp->stat.st_mtime) + 20);
	else
		ft_printf("%.7s 10000", ctime(&temp->stat.st_mtime) + 4);
}

void		display_long(t_ls *ls, t_file *file)
{
	t_file			*temp;
	t_pstat			*pstat;

	temp = file;
	pstat = (t_pstat*)malloc(sizeof(t_pstat));
	init_pstat(pstat);
	parse_list(pstat, file);
	(file != ls->files && file) ? ft_printf("total %d\n", pstat->total) : 0;
	while (temp && ls)
	{
		ft_printf("%c%s %*d %-*s  %-*s  %*d ",
		temp->type, temp->chmod, pstat->maxlnk, temp->stat.st_nlink,
		pstat->maxusr, temp->user, pstat->maxgrp, temp->group,
		pstat->maxsize, temp->stat.st_size);
		print_time(temp);
		ft_printf(" %s", temp->name);
		if (temp->type == 'l' && temp->target)
			ft_printf(" -> %s", temp->target);
		write(1, "\n", 1);
		temp = temp->next;
	}
}
