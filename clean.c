/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:10:52 by itiievsk          #+#    #+#             */
/*   Updated: 2018/08/15 12:10:54 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		clean_file(t_file *file)
{
	free(file);
}

void		clean_filelist(t_file *file)
{
	while (file)
	{
		file->name != NULL ? free(file->name) : 0;
		file->path != NULL ? free(file->path) : 0;
		file->full != NULL ? free(file->full) : 0;
		file->user != NULL ? free(file->user) : 0;
		file->group != NULL ? free(file->group) : 0;
		file->target != NULL ? free(file->target) : 0;
		if (file->next)
		{
			file = file->next;
			free(file->prev);
		}
		else
		{
			free(file);
			file = NULL;
		}
	}
}

void		clean_ls(t_ls *ls)
{
	ls->path != NULL ? free(ls->path) : 0;
	clean_filelist(ls->objs);
	clean_filelist(ls->files);
	clean_filelist(ls->err);
	free(ls);
}
