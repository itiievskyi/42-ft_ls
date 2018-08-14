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
	dirs = NULL;
	while ((sd = readdir(dir)) != NULL)
	{
		if (sd->d_name[0] != '.' || (sd->d_name[0] == '.' && flags->dotfiles) ||
		(sd->d_name[0] == '.' && flags->noparent && !ft_strequ(sd->d_name, ".")
		&& !ft_strequ(sd->d_name, "..")))
		{
			if ((opendir(sd->d_name)) == NULL &&
			ft_strequ(strerror(errno), "Not a directory"))
				t_file_pushback(&file, sd->d_name, cat);
			else
				t_file_pushback(&dirs, sd->d_name, cat);
		}
	}
	temp = file;
	if (file)
	{
		while (temp->next)
			temp = temp->next;
		temp->next = dirs;
	}
	else
		file = dirs;
	if (file && count_list_length(file) > 1 && ls)
		sort_list(file, flags);
	return (file);
}

void		create_new_list(t_ls *ls, t_file *file, char *path)
{
	struct stat		stat_temp;
	t_file			*temp;
	DIR				*dir;

	temp = file;
	ls->path = ft_strdup(path);
	while (temp)
	{
		lstat(temp->full, &stat_temp);
		if ((dir = opendir(temp->full)) == NULL &&
		ft_strequ(strerror(errno), "Not a directory"))
			t_file_pushback(&(ls->files), temp->full, path);
		else if ((S_ISDIR(stat_temp.st_mode)) && !ft_strequ(".", temp->name)
		&& !ft_strequ("..", temp->name))
		{
			t_file_pushback(&(ls->objs), temp->full, path);
		}
		if (dir)
			closedir(dir);
		temp = temp->next;
	}
}

void		read_objs(t_flags *flags, t_ls *ls)
{
	DIR				*dir;
	t_file			*temp;
	t_file			*file;
	char			*cat;
	t_ls			*new;

	new = NULL;
	temp = NULL;
	temp = ls->objs;
	sort_list(ls->objs, flags);
	while (temp)
	{
		cat = ft_strjoin(temp->path, temp->name);
		if (((count_list_length(ls->objs) > 1 || ls->err || ls->files) &&
		!flags->recursive) || (flags->recursive && !(ls->start == 1 &&
		count_list_length(ls->objs) < 2 && !ls->err && !ls->files)))
			ft_printf("%s:\n", cat);
		dir = opendir(temp->full);
		if (dir == NULL)
			print_cat_error(cat, strerror(errno));
		else
		{
			file = create_list(flags, ls, dir, cat);
			print_list(ls, file, flags);
			if (flags->recursive == 1)
			{
				new = (t_ls*)malloc(sizeof(t_ls));
				new->objs = NULL;
				new->files = NULL;
				new->err = NULL;
				create_new_list(new, file, ls->path);
				if (new->objs)
				{
					write(1, "\n", 1);
					read_objs(flags, new);
				}
				if (new)
					free(new);
			}
			closedir(dir);
		}
		if (temp->next)
			write(1, "\n", 1);
		temp = temp->next;
	}
}
