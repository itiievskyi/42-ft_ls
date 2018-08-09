/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_columns.c                                  :+:      :+:    :+:   */
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
	t_file			*file1;

	file1 = file;
	while (file1 && ls) {
//		ft_printf("%d\t", (file1->stat).st_mode);
		ft_printf("%s\n", file1->name);
//		ft_printf("%s\t", file1->path);
//		ft_printf("%s\t", file1->full);
//		ft_printf("%s", ctime(&(file1->stat).st_mtime));
		file1 = file1->next;
	}
}
