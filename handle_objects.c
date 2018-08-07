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

void		read_objs(int argc, char **argv, t_flags *flags, t_ls *ls)
{
	DIR				*dir;
	struct dirent	*sd;
	int				i;

	i = -1;
	if (argv && argc && flags) {}
	if (flags->revsort == 0)
		ft_sort_strtab(ls->objs, "asc");
	else if (flags->revsort == 1)
		ft_sort_strtab(ls->objs, "desc");
	while (ls->objs[++i])
	{
		dir = opendir(ls->objs[i]);
		if (dir == NULL)
			ft_printf("%s\n", strerror(errno));
		else
		{
			while ((sd = readdir(dir)) != NULL)
			{
				ft_printf("%s\n", sd->d_name);
			}
		}
	}
}
