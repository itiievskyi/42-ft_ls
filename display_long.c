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

static void	parse_list(t_pstat *pstat, t_file *file, t_flags *flags)
{
	t_file			*temp;
	int				lnk_len;
	int				size_len;

	temp = file;
	while (temp)
	{
		pstat->total += (temp->stat).st_blocks;
		temp->type = define_type(temp, pstat);
		define_chmod(temp);
		get_owner(pstat, temp, flags);
		lnk_len = ft_intlen(temp->stat.st_nlink);
		size_len = ft_intlen(temp->stat.st_size);
		lnk_len > pstat->maxlnk ? pstat->maxlnk = lnk_len : 0;
		size_len > pstat->maxsize ? pstat->maxsize = size_len : 0;
		temp = temp->next;
	}
	if (pstat->special && pstat->maxsize < 8)
		pstat->maxsize = 8;
}

static void	print_time(t_file *temp, t_flags *flags)
{
	if (flags->fulltime == 1)
		ft_printf("%.20s", ctime(&temp->ftime) + 4);
	else
	{
		if ((time(NULL) - temp->ftime < 15780000 &&
		temp->ftime - time(NULL) < 15780000))
			ft_printf("%.12s", ctime(&temp->ftime) + 4);
		else if ((ctime(&temp->ftime) + 20)[0] != ' ')
			ft_printf("%.7s %.4s", ctime(&temp->ftime) + 4,
			ctime(&temp->ftime) + 20);
		else
			ft_printf("%.7s 10000", ctime(&temp->ftime) + 4);
	}
}

static void	print_size(t_file *temp, t_pstat *pstat)
{
	if (!pstat->special)
		ft_printf("%*d ", pstat->maxsize, temp->stat.st_size);
	else
	{
		if (temp->type == 'c' || temp->type == 'b')
		{
			if (ft_intlen(major(temp->stat.st_rdev)) < 4)
				ft_printf("% 3d,", major(temp->stat.st_rdev));
			else
				ft_printf(" %#010x,", major(temp->stat.st_rdev));
			if (ft_intlen(minor(temp->stat.st_rdev)) < 4)
				ft_printf("% 4d ", minor(temp->stat.st_rdev));
			else
				ft_printf(" %#010x ", minor(temp->stat.st_rdev));
		}
		else
			ft_printf("%*d ", pstat->maxsize, temp->stat.st_size);
	}
}

void		display_long(t_ls *ls, t_file *file, t_flags *flags)
{
	t_file			*temp;
	t_pstat			*pstat;

	temp = file;
	pstat = (t_pstat*)malloc(sizeof(t_pstat));
	init_pstat(pstat);
	parse_list(pstat, file, flags);
	(file != ls->files && file) ? ft_printf("total %d\n", pstat->total) : 0;
	while (temp && ls)
	{
		ft_printf("%c%s %*d %-*s%-*s",
		temp->type, temp->chmod, pstat->maxlnk, temp->stat.st_nlink,
		pstat->maxusr, temp->user, pstat->maxgrp, temp->group);
		print_size(temp, pstat);
		print_time(temp, flags);
		ft_printf(" %s", temp->name);
		pf_flags_display(temp, flags);
		if (temp->type == 'l' && temp->target)
			ft_printf(" -> %s", temp->target);
		write(1, "\n", 1);
		temp = temp->next;
	}
}
