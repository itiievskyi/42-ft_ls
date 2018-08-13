/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 15:01:35 by itiievsk          #+#    #+#             */
/*   Updated: 2018/08/08 15:01:37 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		display(t_ls *ls, t_file *file)
{
	t_file			*temp;

	temp = file;
	while (temp && ls)
	{
//		ft_printf("%d\t", (file1->stat).st_mode);
//		ft_printf("%s\t", file1->full);
		ft_printf("%s\n", temp->name);
//		ft_printf("%s\t", file1->path);
//		ft_printf("%s", ctime(&(file1->stat).st_mtime));
		temp = temp->next;
	}
}

void		print_list(t_ls *ls, t_file *file, t_flags *flags)
{
	int				length;

	length = count_list_length(ls->objs);
	if (!flags->longform)
		display(ls, file);
	else if (flags->longform == 1)
		display_long(ls, file);
}
