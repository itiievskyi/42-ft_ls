/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 17:45:42 by itiievsk          #+#    #+#             */
/*   Updated: 2018/08/09 17:45:43 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_errors(t_ls *ls)
{
	t_file	*temp;

	temp = ls->err;
	alpha_sort(temp);
	if (temp)
	{
		while (temp)
		{
			ft_printf("ft_ls: %s: %s\n", temp->name, temp->path);
			temp = temp->next;
		}
	}
}
