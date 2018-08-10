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

t_file		*create_list(t_flags *flags, t_ls *ls, DIR *dir, char *cat)
{
	struct dirent	*sd;
	t_file			*file;
	t_file			*dirs;
	t_file			*temp;

	file = NULL;
	while ((sd = readdir(dir)) != NULL)
	{
		if (sd->d_name[0] != '.' || (sd->d_name[0] == '.' && flags->dotfiles))
		{
			if ((opendir(sd->d_name)) == NULL &&
			ft_strequ(strerror(errno), "Not a directory"))
				t_file_pushback(&file, sd->d_name, cat);
			else
				t_file_pushback(&dirs, sd->d_name, cat);
		}
	}
//	rev_sort(file, -1, 0);
//	rev_sort(dirs, -1, 0);
	temp = file;
	if (file)
	{
		while (temp->next)
			temp = temp->next;
		temp->next = dirs;
	}
	else
		file = dirs;
	if (count_list_length(file) > 1 && ls)
		sort_list(file, flags);
	return (file);
}

void		read_objs(t_flags *flags, t_ls *ls)
{
	DIR				*dir;
	t_file			*temp;
	t_file			*file;
	char			*cat;

	temp = ls->objs;
	sort_list(ls->objs, flags);
	while (temp)
	{
		dir = opendir(temp->name);
		if (dir == NULL)
			ft_printf("%s\n", strerror(errno));
		cat = ft_strjoin(temp->path, temp->name);
		if (dir && cat && (count_list_length(ls->objs) > 1 || ls->err))
			ft_printf("%s:\n", cat);
		file = create_list(flags, ls, dir, cat);
		print_list(ls, file, flags);
		if (temp->next)
			write(1, "\n", 1);
		temp = temp->next;
	}
}
