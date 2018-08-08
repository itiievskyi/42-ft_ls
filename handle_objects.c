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
/*	ft_printf("##################### BEFORE_SORTING ########################\n");

	t_file			*file2;
	file2 = file;
	while (file2) {
		ft_printf("%d\t", (file2->stat).st_mode);
		ft_printf("%s\t", file2->name);
		ft_printf("%s", ctime(&(file2->stat).st_mtime));
		file2 = file2->next;
	}
	ft_printf("##################### AFTER_SORTING ########################\n");
*/
	if (ls->files > 0)
		sort_list(file, flags);

	t_file			*file1;
	file1 = file;
	while (file1) {
		ft_printf("%d\t", (file1->stat).st_mode);
		ft_printf("%s\t", file1->name);
		ft_printf("%s", ctime(&(file1->stat).st_mtime));
		file1 = file1->next;
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
