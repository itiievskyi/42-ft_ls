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

t_file		*handle_sd(t_flags *flags, t_ls *ls, t_file *file, t_file *dirs)
{
	t_file			*temp;

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
		sort_list(&file, flags);
	return (file);
}

t_file		*create_list(t_flags *flags, t_ls *ls, DIR *dir, char *cat)
{
	struct dirent	*sd;
	t_file			*file;
	t_file			*dirs;
	DIR				*test;

	file = NULL;
	dirs = NULL;
	while ((sd = readdir(dir)) != NULL)
	{
		if (sd->d_name[0] != '.' || (sd->d_name[0] == '.' && flags->dotfiles) ||
		(sd->d_name[0] == '.' && flags->noparent && !ft_strequ(sd->d_name, ".")
		&& !ft_strequ(sd->d_name, "..")))
		{
			if ((test = opendir(sd->d_name)) == NULL &&
			ft_strequ(strerror(errno), "Not a directory"))
				t_file_pushback(&file, sd->d_name, cat, flags);
			else
				t_file_pushback(&dirs, sd->d_name, cat, flags);
			if (test)
				closedir(test);
		}
	}
	file = handle_sd(flags, ls, file, dirs);
	return (file);
}

void		create_new_list(t_ls *ls, t_file *file, char *path, t_flags *flags)
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
			t_file_pushback(&(ls->files), temp->full, path, flags);
		else if ((S_ISDIR(stat_temp.st_mode)) && !ft_strequ(".", temp->name)
		&& !ft_strequ("..", temp->name))
		{
			t_file_pushback(&(ls->objs), temp->full, path, flags);
		}
		if (dir)
			closedir(dir);
		temp = temp->next;
	}
}

static void	process_dir(t_file *temp, t_ls *ls, t_flags *flags, DIR *dir)
{
	char		*cat;
	t_ls		*new;
	t_file		*file;

	cat = ft_strjoin(temp->path, temp->name);
	if (((count_list_length(ls->objs) > 1 || ls->err || ls->files) &&
	!flags->recursive) || (flags->recursive && !(ls->start == 1 &&
	count_list_length(ls->objs) < 2 && !ls->err && !ls->files)))
		ft_printf("%s:\n", cat);
	(!(dir = opendir(temp->full))) ? print_cat_error(cat, strerror(errno)) : 0;
	if (dir)
	{
		file = create_list(flags, ls, dir, cat);
		print_list(ls, file, flags);
		if (flags->recursive == 1)
		{
			new = (t_ls*)malloc(sizeof(t_ls));
			init_t_ls(new);
			create_new_list(new, file, ls->path, flags);
			(new->objs && write(1, "\n", 1)) ? read_objs(flags, new) : 0;
			new != NULL ? clean_ls(new) : 0;
		}
		(clean_filelist(file) && dir == NULL) ? 0 : closedir(dir);
	}
	free(cat);
}

void		read_objs(t_flags *flags, t_ls *ls)
{
	DIR				*dir;
	t_file			*temp;

	dir = NULL;
	temp = NULL;
	sort_list(&ls->objs, flags);
	temp = ls->objs;
	while (temp)
	{
		process_dir(temp, ls, flags, dir);
		if (temp->next)
			write(1, "\n", 1);
		temp = temp->next;
	}
}
