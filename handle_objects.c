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

void		create_list(t_flags *flags, t_ls *ls, DIR *dir)
{
	struct dirent	*sd;
	t_file			*file;

	file = NULL;
	while ((sd = readdir(dir)) != NULL)
	{
		if (sd->d_name[0] != '.' || (sd->d_name[0] == '.' && flags->dotfiles))
			t_file_pushback(&file, sd->d_name);
	}
	if (flags && ls) {}

	while (file) {
		ft_printf("%d\t", (file->stat).st_mode);
		ft_printf("%s\t", ctime(&(file->stat).st_mtime));
		ft_printf("%s\n", file->name);
		file = file->next;
	}
}

void		read_objs(t_flags *flags, t_ls *ls)
{
	DIR				*dir;
	int				i;

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
		else if (!flags->longform)
			create_list(flags, ls, dir);
	}
}
