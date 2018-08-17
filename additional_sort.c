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

void		rev_sort(t_file **file)
{
	t_file *prev;
	t_file *current;
	t_file *next;

	prev = NULL;
	current = *file;
	next = NULL;
	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*file = prev;
}

t_file		*sorted_alpha_merge(t_file *a, t_file *b)
{
	t_file *result;

	result = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (ft_strcmp(a->name, b->name) < 0)
	{
		result = a;
		result->next = sorted_alpha_merge(a->next, b);
	}
	else
	{
		result = b;
		result->next = sorted_alpha_merge(a, b->next);
	}
	return(result);
}

t_file		*sorted_size_merge(t_file *a, t_file *b)
{
	t_file *result;

	result = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (a->stat.st_size >= b->stat.st_size)
	{
		result = a;
		result->next = sorted_size_merge(a->next, b);
	}
	else
	{
		result = b;
		result->next = sorted_size_merge(a, b->next);
	}
	return(result);
}

t_file		*sorted_time_merge(t_file *a, t_file *b)
{
	t_file *result;

	result = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (a->ftime > b->ftime)
	{
		result = a;
		result->next = sorted_time_merge(a->next, b);
	}
	else if (a->ftime == b->ftime && a->nsec >= b->nsec)
	{
		result = a;
		result->next = sorted_time_merge(a->next, b);
	}
	else
	{
		result = b;
		result->next = sorted_time_merge(a, b->next);
	}
	return(result);
}

t_file		*sorted_system_merge(t_file *a, t_file *b)
{
	t_file *result;

	result = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (a->sysnum <= b->sysnum)
	{
		result = a;
		result->next = sorted_system_merge(a->next, b);
	}
	else
	{
		result = b;
		result->next = sorted_system_merge(a, b->next);
	}
	return(result);
}
