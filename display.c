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

void		display(t_ls *ls, t_file *file, t_flags *flags)
{
	t_file			*temp;

	temp = file;
	while (temp && ls)
	{
		ft_printf("%s", temp->name);
		if ((S_ISDIR(temp->stat.st_mode) && flags->slashdir == 1))
			write(1, "/\n", 2);
		else
			write(1, "\n", 1);
		temp = temp->next;
	}
}

void		print_list(t_ls *ls, t_file *file, t_flags *flags)
{
	int				length;

	length = count_list_length(ls->objs);
	if (!flags->longform)
		display(ls, file, flags);
	else if (flags->longform == 1)
		display_long(ls, file, flags);
}
