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

int			clean_filelist(t_file *file)
{
	t_file		*temp;

	while ((temp = file))
	{
		file = file->next;
		temp->name != NULL ? free(temp->name) : 0;
		temp->path != NULL ? free(temp->path) : 0;
		temp->full != NULL ? free(temp->full) : 0;
		temp->user != NULL ? free(temp->user) : 0;
		temp->group != NULL ? free(temp->group) : 0;
		temp->target != NULL ? free(temp->target) : 0;
		free(temp);
	}
	return (1);
}

void		clean_ls(t_ls *ls)
{
	ls->path != NULL ? free(ls->path) : 0;
	clean_filelist(ls->objs);
	clean_filelist(ls->files);
	clean_filelist(ls->err);
	free(ls);
}
