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

	file = NULL;
	while ((sd = readdir(dir)) != NULL)
	{
		if (sd->d_name[0] != '.' || (sd->d_name[0] == '.' && flags->dotfiles))
			t_file_pushback(&file, sd->d_name, cat);
	}
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
		file = create_list(flags, ls, dir, cat);
//		if (!flags->longform)
			display(ls, file);
		temp = temp->next;
	}
}
