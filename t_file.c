/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_file.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 16:33:24 by itiievsk          #+#    #+#             */
/*   Updated: 2018/08/08 16:33:26 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file		*t_file_new(char *name)
{
	t_file	*file;

	file = (t_file*)malloc(sizeof(t_file));
	file->name = ft_strdup(name);
	file->next = NULL;
	file->prev = NULL;
	stat(name, &file->stat);
	return (file);
}

int			t_file_pushback(t_file **begin, char *name)
{
	t_file *temp;

	temp = *begin;
	if (temp)
	{
		while (temp->next)
			temp = temp->next;
		temp->next = t_file_new(name);
		temp->next->prev = temp;
	}
	else if (name)
		*begin = t_file_new(name);
	else
		return (0);
	return (1);
}
