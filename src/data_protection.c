/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_protection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 17:46:56 by fkoehler          #+#    #+#             */
/*   Updated: 2017/09/21 21:14:11 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int			is_data_valid(void *data, t_data_type data_type)
{

	if (data_type == BLOCK && (!((t_block*)data)->canary
	|| ((t_block*)data)->canary != CANARY(((t_block*)data)->canary)))
		return (0);
	else if (data_type == ZONE && (!((t_zone*)data)->canary
	|| ((t_zone*)data)->canary != CANARY(((t_zone*)data)->canary)))
		return (0);
	return (1);
}
