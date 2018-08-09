/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 18:10:42 by itiievsk          #+#    #+#             */
/*   Updated: 2018/08/07 18:10:44 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file		*create_list(t_flags *flags, t_ls *ls, DIR *dir)
{
	struct dirent	*sd;
	t_file			*file;

	file = NULL;
	while ((sd = readdir(dir)) != NULL)
	{
		if (sd->d_name[0] != '.' || (sd->d_name[0] == '.' && flags->dotfiles))
			t_file_pushback(&file, sd->d_name);
	}
	if (ls->files > 0)
		sort_list(file, flags);
	return (file);
}

void		read_objs(t_flags *flags, t_ls *ls)
{
	DIR				*dir;
	int				i;
	t_file			*file;

	i = -1;
	if (flags->revsort == 0)
		ft_sort_strtab(ls->objs, "asc");
	else if (flags->revsort == 1)
		ft_sort_strtab(ls->objs, "desc");
	while (ls->objs[++i])
	{
		dir = opendir(ls->objs[i]);
		if (dir == NULL)
			ft_printf("%s\n", strerror(errno));
		file = create_list(flags, ls, dir);
		if (!flags->longform)
			display(ls, file);
	}
}
