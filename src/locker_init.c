/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locker_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 16:23:11 by fkoehler          #+#    #+#             */
/*   Updated: 2017/09/28 16:46:36 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	init_locker(void)
{
	if (pthread_mutex_init(&g_alloc.locker, NULL) == 0)
		g_alloc.locker_init = 1;
	else
		put_error(LOCKER_INIT_FAILED, NULL);
}
