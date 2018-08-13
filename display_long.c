/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_long.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 11:11:18 by itiievsk          #+#    #+#             */
/*   Updated: 2018/08/13 11:11:20 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		define_chmod(t_file *file)
{
	mode_t val;
	val=(file->stat.st_mode & ~S_IFMT);

	file->chmod[0] = ((val & S_IRUSR) ? 'r' : '-');
	file->chmod[1] = ((val & S_IWUSR) ? 'w' : '-');
	file->chmod[2] = ((val & S_IXUSR) ? 'x' : '-');
	file->chmod[3] = ((val & S_IRGRP) ? 'r' : '-');
	file->chmod[4] = ((val & S_IWGRP) ? 'w' : '-');
	file->chmod[5] = ((val & S_IXGRP) ? 'x' : '-');
	file->chmod[6] = ((val & S_IROTH) ? 'r' : '-');
	file->chmod[7] = ((val & S_IWOTH) ? 'w' : '-');
	file->chmod[8] = ((val & S_IXOTH) ? 'x' : '-');
}

char		define_type(t_file *file)
{
	if (S_ISDIR(file->stat.st_mode))
		return ('d');
	if (S_ISCHR(file->stat.st_mode))
		return ('c');
	if (S_ISBLK(file->stat.st_mode))
		return ('b');
	if (S_ISLNK(file->stat.st_mode))
		return ('l');
	if (S_ISSOCK(file->stat.st_mode))
		return ('s');
	if (S_ISFIFO(file->stat.st_mode))
		return ('p');
	return ('-');
}

void		parse_list(t_pstat *pstat, t_file *file)
{
	t_file			*temp;

	temp = file;
	while (temp)
	{
		pstat->total += (temp->stat).st_blocks;
		temp->type = define_type(temp);
		define_chmod(temp);
		temp = temp->next;
	}
}

void		display_long(t_ls *ls, t_file *file)
{
	t_file			*temp;
	t_pstat			*pstat;

	temp = file;
	pstat = (t_pstat*)malloc(sizeof(t_pstat));
	init_pstat(pstat);
	parse_list(pstat, file);
	ft_printf("total %d\n", pstat->total);
	while (temp && ls)
	{
		ft_printf("%c%s %s\n", temp->type, temp->chmod, temp->name);
		temp = temp->next;
	}
}
