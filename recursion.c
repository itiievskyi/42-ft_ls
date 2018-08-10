/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 18:01:21 by itiievsk          #+#    #+#             */
/*   Updated: 2018/08/10 18:01:23 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		recursion(t_ls *ls, t_flags *flags)
{
	if (flags && ls) {}
	DIR				*dir;
	t_file			*temp;
	t_file			*list;
	char			*cat;
	t_ls			*rec;

	list =
	rec = (t_ls*)malloc(sizeof(t_ls));
	temp = ls->objs;
	while (temp)
	{
		if ((dir = opendir(temp->name) )
		temp = temp->next;
	}
}
