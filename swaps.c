/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swaps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 20:22:54 by itiievsk          #+#    #+#             */
/*   Updated: 2018/08/08 20:22:56 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_str_swap(char **a, char **b)
{
	char *z;

	z = *a;
	*a = *b;
	*b = z;
}

void		ft_stat_swap(struct stat *a, struct stat *b)
{
	struct stat z;

	z = *a;
	*a = *b;
	*b = z;
}

void		ft_time_swap(time_t *a, time_t *b)
{
	time_t z;

	z = *a;
	*a = *b;
	*b = z;
}
