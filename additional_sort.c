/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_sort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 16:31:43 by itiievsk          #+#    #+#             */
/*   Updated: 2018/08/14 16:31:45 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		size_sort(t_file *file)
{
	t_file	*temp;

	temp = file;
	while (temp && temp->next)
	{
		if (temp->stat.st_size < temp->next->stat.st_size)
		{
			swap_t_file(temp, temp->next);
			temp = file;
		}
		else
			temp = temp->next;
	}
}
