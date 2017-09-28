/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 17:46:56 by fkoehler          #+#    #+#             */
/*   Updated: 2017/09/28 16:44:11 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void 			put_size_stderr(size_t size)
{
	if (size > 9)
		put_size_stderr(size / 10);
	ft_putchar_fd(size % 10 + 48, 2);
}

void			put_alloc_error(t_errnum errnum, size_t size)
{
	ft_putstr_fd("malloc error : ", 2);
	if (errnum == MAPPING_FAILED)
	{
		ft_putstr_fd("can't allocate zone of size ", 2);
		put_size_stderr(size);
		ft_putstr_fd(" bytes.\n", 2);
	}
	else if (errnum == ALLOC_OVERSIZED)
	{
		ft_putstr_fd("oversized allocation request (", 2);
		put_size_stderr(size);
		ft_putstr_fd(" bytes).\n", 2);
	}
}

void			put_error(t_errnum errnum, void *address)
{
	char	*str;

	str = ft_ltoa_base((long)address, 16);
	ft_putstr_fd("malloc error : ", 2);
	if (errnum == DATA_CORRUPT)
	{
		ft_putstr_fd("object at address 0x", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(" is corrupted (probably due to data overriding).\n", 2);
		abort();
	}
	else if (errnum == NOT_ALLOCATED)
	{
		ft_putstr_fd("pointer to address 0x", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(" was not allocated before freeing attempt\n", 2);
		abort();
	}
	else if (errnum == UNMAPPING_FAILED)
	{
		ft_putstr_fd("can't release zone at address 0x", 2);
		ft_putendl_fd(str, 2);
	}
	else if (errnum == LOCKER_INIT_FAILED)
		ft_putstr_fd("can't initialize the multi-thread locker\n", 2);
}

void			check_data_validity(void *data, t_data_type data_type)
{
	if (data_type == BLOCK && (!((t_block*)data)->canary
	|| ((t_block*)data)->canary != CANARY(((t_block*)data)->canary)))
		put_error(DATA_CORRUPT, data);
	else if (data_type == ZONE && (!((t_zone*)data)->canary
	|| ((t_zone*)data)->canary != CANARY(((t_zone*)data)->canary)))
		put_error(DATA_CORRUPT, data);
}
