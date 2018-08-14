/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 15:01:35 by itiievsk          #+#    #+#             */
/*   Updated: 2018/08/08 15:01:37 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		pf_flags_display(t_file *temp, t_flags *flags)
{
	mode_t 		val;

	val = (temp->stat.st_mode & ~S_IFMT);
	if ((S_ISDIR(temp->stat.st_mode) && flags->filetypes > 0))
		write(1, "/", 1);
	else if (flags->filetypes == 1 && S_ISREG(temp->stat.st_mode) &&
	((val & S_IXUSR) || (val & S_IXGRP) || (val & S_IXOTH)))
		write(1, "*", 1);
	else if (flags->filetypes == 1 && S_ISLNK(temp->stat.st_mode))
		write(1, "@", 1);
	else if (flags->filetypes == 1 && S_ISSOCK(temp->stat.st_mode))
		write(1, "=", 1);
	else if (flags->filetypes == 1 && S_ISWHT(temp->stat.st_mode))
		ft_printf("%%");
	else if (flags->filetypes == 1 && S_ISFIFO(temp->stat.st_mode))
		write(1, "|", 1);
}

void		display(t_ls *ls, t_file *file, t_flags *flags)
{
	t_file			*temp;

	temp = file;
	while (temp && ls)
	{
		ft_printf("%s", temp->name);
		pf_flags_display(temp, flags);
		write(1, "\n", 1);
		temp = temp->next;
	}
}

void		print_list(t_ls *ls, t_file *file, t_flags *flags)
{
	int				length;

	length = count_list_length(ls->objs);
	if (!flags->longform)
		display(ls, file, flags);
	else if (flags->longform == 1)
		display_long(ls, file, flags);
}
